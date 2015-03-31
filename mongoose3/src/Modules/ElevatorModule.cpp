/*
 * ElevatorModule.cpp
 *
 *  Created on: Feb 12, 2015
 *      Author: Team 114
 */

#include "ElevatorModule.h"

ElevatorModule::ElevatorModule(int motorPort1, int motorPort2, int safteyButtonPort, int encoderA, int encoderB):
RobotModule("Elevator"),
m_HUD_Error(0)
{
	m_SafteyButton = new DigitalInput(safteyButtonPort);
	m_Motor_1 = new SafeTalonSRX(motorPort1, m_SafteyButton);
	m_Motor_2 = new SafeTalonSRX(motorPort2, m_SafteyButton);
	m_Lifter = new DualMotor(m_Motor_1, m_Motor_2);
	m_Encoder = new Encoder(encoderA, encoderB);
	m_Encoder->SetDistancePerPulse(INCHES_PER_ELEVATOR_PULSE);
	m_PIDController = new PIDController(ELEVATOR_P, ELEVATOR_I, ELEVATOR_D, m_Encoder, m_Lifter);
	m_Manual = true;

	m_PIDController->SetOutputRange(MAX_ELEVATOR_DOWN, MAX_ELEVATOR_UP);
	m_PIDController->SetInputRange(MIN_ELEVATOR_INPUT, MAX_ELEVATOR_INPUT);
	m_Calibration_Is_Done = false;

}

ElevatorModule::~ElevatorModule(){

}

void ElevatorModule::enablePID() {
	if(!m_Calibration_Is_Done) {
		return;
	}
	m_PIDController->Enable();
	m_Manual = false;
}

void ElevatorModule::disablePID() {
	m_PIDController->Disable();
	RobotModule::enable();
	m_Manual = true;
}

void ElevatorModule::enable(){
	RobotModule::enable();
}

void ElevatorModule::disable(){
	RobotModule::disable();

	m_Motor_1->Disable();
	m_Motor_2->Disable();
	m_PIDController->Disable();
}

void ElevatorModule::reset(){
	resetPersist();
	m_Encoder->Reset();
}

void ElevatorModule::resetPersist(){
	m_PIDController->Reset();
}

void ElevatorModule::checkError(){
	return;
	std::cout<<"ELEVATOR MODULE: CHECKING ERROR" << std::endl;
	Timer encoderTimeOut;
	encoderTimeOut.Start();

	while(true) {
		m_HUD_Error = false;

		if(m_Enabled && !m_Manual && m_Calibration_Is_Done) {
			if(abs(m_Encoder->GetRate()) < .05) { }
			else encoderTimeOut.Reset();

			if(encoderTimeOut.Get() > 0.1) {
				m_HUD_Error = true;
			}
		}
	}
}

bool ElevatorModule::getHUDError(){
	return m_HUD_Error;
}


void ElevatorModule::handleFatalError(){
	disablePID();
	m_Manual = true;
}

void ElevatorModule::setPosition(double height){
	if(height > MAX_ELEVATOR_INPUT)
		height = MAX_ELEVATOR_INPUT;
	else if(height < MIN_ELEVATOR_INPUT) {
		height = MIN_ELEVATOR_INPUT;
	}
	if(m_Manual)
		return;
	m_PIDController->SetSetpoint(height);
}

void ElevatorModule::setPower(double power){
	std::cout << "*****POWER: " << power << " **Lifter button: " << m_SafteyButton->Get() << " ****** enabled: " << m_Enabled << " manual:  "  << m_Manual << " ***"<< std::endl;
	if(m_Enabled && m_Manual)
		m_Lifter->Set(power);
	else
		m_Lifter->Set(0);
}

void ElevatorModule::calibrate() {

	if(!m_Enabled)
		return;

	std::cout << "in calibrate" << std::endl;

	Timer timeOut, timeOut2;
	timeOut.Start();

	bool renablePID = false;

	disablePID();

	if(m_PIDController->IsEnabled()){
		renablePID = true;
	}

	while(!getButton()) {
		if(timeOut.Get() > MAX_ELEVATOR_CALIBRATE_TIME_DOWN) {
			throw CalibrationError(this, "ElevatorModule::calibrate()" , "calibrate timed out");
		}
		setPower(CALIBRATE_ELEVATOR_DOWN);
		Wait(0.005);
	}

	std::cout << "After first loop" << std::endl;
	setPower(0);
	m_Encoder->Reset();


	timeOut2.Start();

	while(timeOut2.Get() < MAX_ELEVATOR_CALIBRATE_TIME_UP) {
		setPower(CALIBRATE_ELEVATOR_UP);
		Wait(0.005);
	}

	std::cout << "after second" << std::endl;
	setPower(0);


	if(getButton()) {
		throw CalibrationError(this, "ElevatorModule::calibrate()" ,"check your button");
	}
	if(m_Encoder->PIDGet() < MIN_ELEVATOR_DISTANCE_CALIBRATE) {
		throw CalibrationError(this, "ElevatorModule::calibrate()" , "check your encoder");
	}

	if(renablePID)
		m_PIDController->Enable();

	m_Calibration_Is_Done = true;
	std::cout << "Done with Calibrate" << std::endl;
}

void ElevatorModule::syncCalibrate() {
	std::thread t(ElevatorModule::callSyncCalibrate, this);
}

void ElevatorModule::callSyncCalibrate(void* m) {
	((ElevatorModule*)m)->calibrate();
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

double ElevatorModule::getEncoderTicks() {
	return m_Encoder->Get();
}

double ElevatorModule::getError() {
	return m_PIDController->GetError();
}

double ElevatorModule::getSetpoint(){
	return m_PIDController->GetSetpoint();
}

bool ElevatorModule::hasCalibrated(){
	return m_Calibration_Is_Done;
}

std::vector<std::string> ElevatorModule::getLoggingHeader() {

	std::vector<std::string> headers;

	headers.push_back("get");
	headers.push_back("getSetpoint");
	headers.push_back("getError");
	headers.push_back("isEnabled");
	headers.push_back("encoder_get");

	return headers;
}
std::vector<double> ElevatorModule::getLoggingData() {

	std::vector<double> data;

	data.push_back(m_PIDController->Get());
	data.push_back(m_PIDController->GetSetpoint());
	data.push_back(m_PIDController->GetError());
	data.push_back(m_PIDController->IsEnabled());
	data.push_back(m_Encoder->Get());

	return data;

}


