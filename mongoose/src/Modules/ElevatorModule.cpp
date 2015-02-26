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
	m_Manual = true;

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
	std::cout<<"ELEVATOR MODULE: CHECKING ERROR" << std::endl;
	Timer encoderTimeOut;

	encoderTimeOut.Start();

	while(true) {
		if(m_Enabled && !m_Manual) {
			if(abs(m_Encoder->GetRate()) < .05) { }
			else encoderTimeOut.Reset();

			if(encoderTimeOut.Get() > 0.1) {
				throw MovementError("ElevatorModule::checkError()" , "check if Encoder is plugged in");
			}
		}
	}
}

void ElevatorModule::handleFatalError(){
	calibrate();
	m_Manual = true;
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

void ElevatorModule::calibrate() {
	Timer timeOut;
	timeOut.Start();
	while(!getButton()) {
		if(timeOut.Get() > MAX_ELEVATOR_CALIBRATE_TIME_OUT) {
			throw CalibrationError("ElevatorModule::calibrate()" , "calibrate timed out");
		}
		setPower(CALIBRATE_ELEVATOR_DOWN);
	}
	setPower(0);
	timeOut.Stop();
	timeOut.Reset();
	timeOut.Start();

	m_Encoder->Reset();

	while(timeOut.Get() < MAX_ELEVATOR_CALIBRATE_TIME_IN) {
		setPower(CALIBRATE_ELEVATOR_UP);
		if(!getButton()) {
			if(m_Encoder->PIDGet() < MIN_ELEVATOR_DISTANCE_CALIBRATE) {
				throw CalibrationError("ElevatorModule::calibrate()" , "check your encoder");
			}
			break;
		}
	}
	setPower(0);
	if(getButton()) {
		throw CalibrationError("ElevatorModule::calibrate()" ,"check your button");
	}

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

double ElevatorModule::getP() {
	return m_PIDController->GetP();
}

double ElevatorModule::getI() {
	return m_PIDController->GetI();
}

double ElevatorModule::getD() {
	return m_PIDController->GetD();
}

void ElevatorModule::setP(double p) {
	m_PIDController->SetPID(p, getI(), getD());
}

void ElevatorModule::setI(double i) {
	m_PIDController->SetPID(getP(), i, getD());
}

void ElevatorModule::setD(double d) {
	m_PIDController->SetPID(getP(), getI(), d);
}

double ElevatorModule::getEncoderDistance(){
	return m_Encoder->PIDGet();
}

