/*
 * ArmModule.cpp
 *
 *  Created on: Feb 13, 2015
 *      Author: Giggles Upanda
 */

#include "ArmModule.h"
#include "../Settings.h"
#include "../Error/CalibrationError.h"

#define MAX_LEFT 0.5
#define MAX_RIGHT 0.5

ArmModule::ArmModule(int rightTalonPort, int leftTalonPort, int rightButtonPort, int midButtonPort, int leftButtonPort, int rEncoderA, int rEncoderB, int lEncoderA, int lEncoderB)
: RobotModule("Arm")
{
	DigitalInput* rightButton = new DigitalInput(rightButtonPort);
	DigitalInput* leftButton = new DigitalInput(leftButtonPort);
	m_Saftey_Button = new DigitalInput(midButtonPort);
	m_Left_Talon = new SafeTalonSRX(leftTalonPort, leftButton, false);
	m_Right_Talon = new SafeTalonSRX(rightTalonPort, rightButton, true);
	m_Left_Encoder = new ModifiedEncoder(lEncoderA, lEncoderB, 0);
	m_Right_Encoder = new ModifiedEncoder(rEncoderA, rEncoderB, MAX_DELTA_X);
	m_Right_Encoder->SetReverseDirection(true);
	m_Left_Encoder->SetDistancePerPulse(.001);
	m_Right_Encoder->SetDistancePerPulse(.001);
	m_Left_Output = new ArmOut();
	m_Right_Output = new ArmOut();
	m_Arm_Difference_Input = new ArmDifference(m_Right_Encoder, m_Left_Encoder);
	m_Diff_Output = new ArmOut();

	m_Left_Arm_Controller = new PIDController(LEFT_ARM_1_KP, LEFT_ARM_1_KI, LEFT_ARM_1_KD, m_Left_Encoder, m_Left_Output);
	m_Right_Arm_Controller = new PIDController(RIGHT_ARM_1_KP, RIGHT_ARM_1_KI , RIGHT_ARM_1_KD, m_Right_Encoder, m_Right_Output);
	m_Difference_Controller = new PIDController(0, 0, 0, m_Arm_Difference_Input, m_Diff_Output);
}

void ArmModule::enable() {
	RobotModule::enable();
	m_Left_Arm_Controller->Enable();
	m_Right_Arm_Controller->Enable();
	m_Difference_Controller->Enable();
}

void ArmModule::enablePID(){
	m_Left_Arm_Controller->Enable();
	m_Right_Arm_Controller->Enable();
	m_Difference_Controller->Enable();
}

void ArmModule::disablePID(){
	m_Left_Arm_Controller->Disable();
	m_Right_Arm_Controller->Disable();
	m_Difference_Controller->Disable();
}

void ArmModule::setSetPoint(float setPoint) {
	if(m_Enabled){
		m_Left_Arm_Controller->SetSetpoint(setPoint);
		m_Right_Arm_Controller->SetSetpoint(m_DeltaX + setPoint);
		m_Right_Talon->Set(m_Right_Output->getPower() + m_Diff_Output->getPower());
		m_Left_Talon->Set(m_Left_Output->getPower() + m_Diff_Output->getPower());
	}else{
		m_Right_Talon->Set(0);
		m_Left_Talon->Set(0);
	}
}

void ArmModule::setLeftArm(float setpoint) {

	if(setpoint < 0)
		setpoint = 0;

	if(setpoint + m_Difference_Controller->GetSetpoint() > MAX_DELTA_X){
		setpoint = MAX_DELTA_X - m_Difference_Controller->GetSetpoint();
	}

	if(m_DeltaX != 0) {
		setSetPoint(setpoint);
	}
	else {
		m_Left_Arm_Controller->SetSetpoint(setpoint);
		m_Left_Talon->Set(m_Left_Output->getPower());
	}
}

void ArmModule::setRightArm(float setpoint) {

	if(setpoint > MAX_DELTA_X)
		setpoint = MAX_DELTA_X;

	if(setpoint < m_Difference_Controller->GetSetpoint())
		setpoint = m_Difference_Controller->GetSetpoint();

	if(m_DeltaX != 0) {
		setSetPoint(setpoint - m_DeltaX);
	}
	else {
		m_Right_Arm_Controller->SetSetpoint(setpoint);
		m_Right_Talon->Set(m_Right_Output->getPower());
	}
}

void ArmModule::setLeftPower(float power){
	if(!m_Enabled)
		power = 0;
	if(m_Saftey_Button->Get() && power > 0)
		m_Left_Talon->Set(0);
	else
		m_Left_Talon->Set(power);
}

void ArmModule::setRightPower(float power){
	if(!m_Enabled)
		power = 0;

	if(m_Saftey_Button->Get() && power < 0)
		m_Right_Talon->Set(0);
	else
		m_Right_Talon->Set(power);
}

void ArmModule::setDeltaX(double deltaX) {
	m_Difference_Controller->Enable();

	if(deltaX < 0)
		deltaX = 0;
	if(deltaX > MAX_DELTA_X)
		deltaX = MAX_DELTA_X;

	m_Difference_Controller->SetSetpoint(deltaX);
	m_DeltaX = deltaX;
}

void ArmModule::disableDeltaX() {
	m_Difference_Controller->Disable();
	m_DeltaX = 0;
}

void ArmModule::disable() {
	RobotModule::disable();
	disableDeltaX();
	m_Right_Arm_Controller->Disable();
	m_Left_Arm_Controller->Disable();
	m_Left_Talon->Disable();
	m_Right_Talon->Disable();
}

void ArmModule::calibrate() {

	Timer timeout;
	timeout.Start();

	if(!m_Enabled)
		return;

	bool renablePid = false;

	if(m_Left_Arm_Controller->IsEnabled() || m_Right_Arm_Controller->IsEnabled()){
		disablePID();
		renablePid = true;
	}

	while (!m_Right_Talon->getButton() || !m_Left_Talon->getButton()) {

		if(timeout.Get() > 3){
			throw CalibrationError("calibrate()", "calibration timed out");
		}


		if(m_Right_Talon->getButton()) {
			m_Right_Talon->Set(0);
		}
		else {
			m_Right_Talon->Set(MAX_RIGHT * 1);
		}
		if(m_Left_Talon->getButton()) {
			m_Left_Talon->Set(0);
		}
		else {
			m_Left_Talon->Set(-MAX_LEFT * 0.9);
		}
	}

	m_Right_Encoder->Reset();
	m_Left_Encoder->Reset();

	if(renablePid)
		enablePID();
}

void ArmModule::reset(){
	m_Left_Encoder->Reset();
	m_Right_Encoder->Reset();
}

ArmModule::~ArmModule() {}

bool ArmModule::getLeftButton(){
	return m_Left_Talon->getButton();
}

bool ArmModule::getMidButton(){
	return m_Saftey_Button->Get();
}

bool ArmModule::getRightButton(){
	return m_Right_Talon->getButton();
}

double ArmModule::getLeftPosition(){
	return m_Left_Encoder->PIDGet();
}

double ArmModule::getRightPosition(){
	return m_Right_Encoder->PIDGet();
}

double ArmModule::getLeftPower(){
	return m_Left_Talon->Get();
}

double ArmModule::getRightPower(){
	return m_Right_Talon->Get();
}

double ArmModule::getLeftSetpoint(){
	return m_Left_Arm_Controller->GetSetpoint();
}

double ArmModule::getDiffSetpoint(){
	return m_Difference_Controller->GetSetpoint();
}

double ArmModule::getRightSetpoint(){
	return m_Right_Arm_Controller->GetSetpoint();
}

double ArmModule::getRightError(){
	return m_Right_Arm_Controller->GetError();
}

double ArmModule::getDiffError(){
	return m_Difference_Controller->GetError();
}

double ArmModule::getLeftError(){
	return m_Left_Arm_Controller->GetError();
}
