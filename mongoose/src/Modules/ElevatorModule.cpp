/*
 * ElevatorModule.cpp
 *
 *  Created on: Feb 12, 2015
 *      Author: Team 114
 */

#include "ElevatorModule.h"

ElevatorModule::ElevatorModule(int motorPort1, int motorPort2, int safteyButtonPort, int encoderA, int encoderB): RobotModule("Elevator"){
	m_SafteyButton = new DigitalInput(safteyButtonPort);
	m_Motor_1 = new SafeTalonSRX(motorPort1, m_SafteyButton);
	m_Motor_2 = new SafeTalonSRX(motorPort2, m_SafteyButton);
	m_Lifter = new DualMotor(m_Motor_1, m_Motor_2);
	m_Encoder = new Encoder(encoderA, encoderB);
	m_PIDController = new PIDController(0, 0, 0, m_Encoder, m_Lifter);

	m_PIDController->SetOutputRange(MAX_ELEVATOR_DOWN, MAX_ELEVATOR_UP);

}
//Cole Was here

ElevatorModule::~ElevatorModule(){

}


void ElevatorModule::enable(){
	RobotModule::enable();
	m_PIDController->Enable();
}

void ElevatorModule::disable(){
	RobotModule::disable();

	m_Motor_1->Disable();
	m_Motor_2->Disable();
	m_PIDController->Disable();
}

void ElevatorModule::reset(){
	m_PIDController->Reset();
	m_Encoder->Reset();
}

void ElevatorModule::checkError(){

}

void ElevatorModule::handleFatalError(){

}

void ElevatorModule::setPosition(double height){
	m_PIDController->SetSetpoint(height);
}

void ElevatorModule::setPower(double power){
	if(m_Enabled)
		m_Lifter->Set(power);
	else
		m_Lifter->Set(0);
}

void ElevatorModule::setPID(double p, double i, double d){
	m_PIDController->SetPID(p, i, d);
}

bool ElevatorModule::getButton(){
	return m_SafteyButton->Get();
}

double ElevatorModule::Get(){
	return m_Lifter->Get();
}
