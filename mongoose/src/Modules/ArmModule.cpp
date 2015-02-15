/*
 * ArmModule.cpp
 *
 *  Created on: Feb 13, 2015
 *      Author: Giggles Upanda
 */

#include "ArmModule.h"
#include "../Settings.h"

#define MAX_LEFT 0.5
#define MAX_RIGHT 0.5

ArmModule::ArmModule(int rightTalonPort, int leftTalonPort, int rightButtonPort, int leftButtonPort, int rEncoderA, int rEncoderB, int lEncoderA, int lEncoderB)
: RobotModule("Arm")
{
	DigitalInput* rightButton = new DigitalInput(rightButtonPort);
	DigitalInput* leftButton = new DigitalInput(leftButtonPort);
	m_Right_Talon = new SafeTalonSRX(rightTalonPort, rightButton, true);
	m_Left_Talon = new SafeTalonSRX(leftTalonPort, leftButton, false);
	m_Right_Encoder = new ModifiedEncoder(rEncoderA, rEncoderB, MAX_DELTA_X);
	m_Left_Encoder = new ModifiedEncoder(lEncoderA, lEncoderB, 0);
	m_Right_Output = new ArmOut();
	m_Left_Output = new ArmOut();
	m_Arm_Difference_Input = new ArmDifference(m_Right_Encoder, m_Left_Encoder);
	m_Diff_Output = new ArmOut();

	m_Right_Arm_Controller = new PIDController(RIGHT_ARM_1_KP, RIGHT_ARM_1_KI , RIGHT_ARM_1_KD, m_Right_Encoder, m_Right_Output);
	m_Left_Arm_Controller = new PIDController(LEFT_ARM_1_KP, LEFT_ARM_1_KI, LEFT_ARM_1_KD, m_Left_Encoder, m_Left_Output);
	m_Difference_Controller = new PIDController(0, 0, 0, m_Arm_Difference_Input, m_Diff_Output);
}

void ArmModule::enable() {
	m_Right_Arm_Controller->Enable();
	m_Left_Arm_Controller->Enable();
}

void ArmModule::setSetPoint(float setPoint) {
	m_Right_Arm_Controller->SetSetpoint(m_DeltaX + setPoint);
	m_Left_Arm_Controller->SetSetpoint(setPoint);
	m_Right_Talon->Set(m_Right_Output->getPower() + m_Diff_Output->getPower());
	m_Left_Talon->Set(m_Left_Output->getPower() + m_Diff_Output->getPower());
}

void ArmModule::setLeftArm(float setpoint) {
	if(m_DeltaX != 0) {
		setSetPoint(setpoint);
	}
	else {
		m_Left_Arm_Controller->SetSetpoint(setpoint);
		m_Left_Talon->Set(m_Left_Output->getPower());
	}
}

void ArmModule::setRightArm(float setpoint) {
	if(m_DeltaX != 0) {
		setSetPoint(setpoint - m_DeltaX);
	}
	else {
		m_Right_Arm_Controller->SetSetpoint(setpoint);
		m_Right_Talon->Set(m_Right_Output->getPower());
	}
}

void ArmModule::setDeltaX(double deltaX) {
	m_Difference_Controller->Enable();
	m_Difference_Controller->SetSetpoint(deltaX);
	m_DeltaX = deltaX;
}

void ArmModule::disableDeltaX() {
	m_Difference_Controller->Disable();
	m_DeltaX = 0;
}

void ArmModule::disable() {
	disableDeltaX();
	m_Right_Arm_Controller->Disable();
	m_Left_Arm_Controller->Disable();
}
void ArmModule::calibrate() {

	while (!m_Right_Talon->getButton() || !m_Left_Talon->getButton()) {
		if(m_Right_Talon->getButton()) {
			m_Right_Talon->Set(0);
		}
		else {
			m_Right_Talon->Set(MAX_RIGHT);
		}
		if(m_Left_Talon->getButton()) {
			m_Left_Talon->Set(0);
		}
		else {
			m_Left_Talon->Set(-MAX_LEFT);
		}
	}

	m_Right_Encoder->Reset();
	m_Left_Encoder->Reset();
}

ArmModule::~ArmModule() {}
