/*
 * ArmModule.cpp
 *
 *  Created on: Feb 13, 2015
 *      Author: Giggles Upanda
 */

#include "ArmModule.h"




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
	m_Left_Encoder->SetReverseDirection(true);
	m_Left_Encoder->SetDistancePerPulse(ARM_DISTANCE_PER_PULSE/4.0);
	m_Right_Encoder->SetDistancePerPulse(ARM_DISTANCE_PER_PULSE);
	m_Left_Output = new ArmOut();
	m_Right_Output = new ArmOut();
	m_Arm_Difference_Input = new ArmDifference(m_Right_Encoder, m_Left_Encoder);
	m_Diff_Output = new ArmOut();

	m_Manual = false;
	m_Calibrating = false;
	m_Has_Calibrated = false;

	m_Left_Arm_Controller = new PIDController(LEFT_ARM_2_KP, LEFT_ARM_2_KI ,LEFT_ARM_2_KD, m_Left_Encoder, m_Left_Output);/*LEFT_ARM_1_KP, LEFT_ARM_1_KI, LEFT_ARM_1_KD, m_Left_Encoder, m_Left_Output*/
	m_Right_Arm_Controller = new PIDController(RIGHT_ARM_2_KP, RIGHT_ARM_2_KI, RIGHT_ARM_2_KD,/*RIGHT_ARM_1_KP, RIGHT_ARM_1_KI , RIGHT_ARM_1_KD,*/ m_Right_Encoder, m_Right_Output);
	m_Difference_Controller = new PIDController(0, 0, 0, m_Arm_Difference_Input, m_Diff_Output);


}


void ArmModule::checkError(){

	return;
	std::cout << "ARM MODULE: checkError()" << std::endl;

	Timer leftTimer;
	Timer rightTimer;

	leftTimer.Start();
	rightTimer.Start();

	std::cout << "ARM MODULE: while(true) " << std::endl;

	while(true){

		if(m_Enabled && !m_Manual && m_Calibrating){

			//TODO possibly not do thread, have a periodic method that gets called every periodic
			//TODO add a timer. this will not work right now
			//TODO not sure how error throwing works with multiple threads
			//TODO joining error threads?


			if(abs(m_Left_Encoder->GetRate()) < 0.05 && abs(m_Left_Talon->Get()) > 0.7){

			}else{
				leftTimer.Reset();
			}

			if(abs(m_Right_Encoder->GetRate()) < 0.05 && abs(m_Right_Talon->Get()) > 0.7){

			}else{
				rightTimer.Reset();
			}

			std::cout << "LTime: " << leftTimer.Get() << " RTime: " << rightTimer.Get() << " lr: " << m_Left_Encoder->GetRate() << " rr: " << m_Right_Encoder->GetRate() << " lp: " << m_Left_Talon->Get() << " rp: " << m_Right_Talon->Get() << std::endl;

			if(leftTimer.Get() > 0.1){
				std::cout << "THROWING ERROR" << std::endl;
				throw MovementError(this, "ArmModule::checkError()", "Left encoder not moving at sufficient rate! (could be unplugged)", true);
			}
			if(rightTimer.Get() > 0.1){
				std::cout << "THROWING ERROR" << std::endl;
				throw MovementError(this, "ArmModule::checkError()", "Right encoder not moving at sufficient rate! (could be unplugged)", true);
			}
		}

		Wait(0.01);

	}
}

void ArmModule::handleFatalError(){
	disablePID();
	setManual(true);
}

void ArmModule::enable() {
	RobotModule::enable();

}

void ArmModule::enablePID(){

	if(!m_Has_Calibrated){
		disablePID();
		std::cout << "PID DISABLED" << std::endl;
		return;
	}

	m_Left_Arm_Controller->Enable();
	m_Right_Arm_Controller->Enable();
	m_Difference_Controller->Enable();
	setManual(false);
}

void ArmModule::disablePID(){
	m_Left_Arm_Controller->Disable();
	m_Right_Arm_Controller->Disable();
	m_Difference_Controller->Disable();
	setManual(true);
}

bool ArmModule::hasCalibrated(){
	return m_Has_Calibrated;
}

void ArmModule::setSetPoint(float setPoint) {
	if(m_Manual)
		return;

	if(m_Enabled){
		//std::cout << "IN SETSETPOINT" << std::endl;
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

	if(m_Manual || !m_Enabled) {
		return;
	}

	if(setpoint < 0)
		setpoint = 0;

	if(setpoint + m_Difference_Controller->GetSetpoint() > MAX_DELTA_X){
		setpoint = MAX_DELTA_X - m_Difference_Controller->GetSetpoint();
	}

	if(m_DeltaX != 0) {
		//		std::cout << "in Set Left arm; Delta != 0" << std::endl;
		setSetPoint(setpoint);
		//		std::cout << "SettingSetPoint" << std::endl;
	}
	else {
		m_Left_Arm_Controller->SetSetpoint(setpoint);
		m_Left_Talon->Set(m_Left_Output->getPower());
	}
}

void ArmModule::setRightArm(float setpoint) {

	if(m_Manual || !m_Enabled)
		return;

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

	//	std::cout << "setLeftPower: " << power << std::endl;

	if(!m_Enabled || !m_Manual)
		power = 0;
	if(m_Saftey_Button->Get() && power > 0)
		m_Left_Talon->Set(0);
	else
		m_Left_Talon->Set(power);
}

void ArmModule::setRightPower(float power){

	//	std::cout << "setRightPower: " << power << std::endl;

	if(!m_Enabled || !m_Manual)
		power = 0;

	if(m_Saftey_Button->Get() && power < 0)
		m_Right_Talon->Set(0);
	else
		m_Right_Talon->Set(power);
}

void ArmModule::setDeltaX(double deltaX) {
	if(m_Manual){
		return;
	}
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

void ArmModule::grab(double deltaX) {
	enablePID();
	Timer time;
	double left = (MAX_DELTA_X - deltaX + OPEN_LEFT_SETPOINT) / 2 ;
	while(time.Get() < 0.2) {
		if(endAllLoops) {
			break;
		}
		setDeltaX(deltaX);
		setLeftArm(left);
		if(abs(getDiffError()/ deltaX) < .08) { 
			time.Start();
		}
		else {
			time.Stop();
			time.Reset();
		}
	}
	disablePID();
	setRightPower(0);
	setLeftPower(0);
}

void ArmModule::open() { 
	enablePID();
	Timer time;
	while(time.Get() < .2) {
		setDeltaX(11.5);
		setDeltaX(11.0);

		setLeftArm(1);
		if(abs(getDiffError()/11.5) < .08) {
			time.Start();
		}
		else {
			time.Stop();
			time.Reset();
		}

	}
	disablePID();
	setRightPower(0);
	setLeftPower(0);

}

void ArmModule::disable() {
	RobotModule::disable();
	disableDeltaX();
	m_Right_Arm_Controller->Disable();
	m_Left_Arm_Controller->Disable();
	m_Left_Talon->Disable();
	m_Right_Talon->Disable();
}

bool ArmModule::calibrate() {

	m_Calibrating = true;

	Timer timeout;
	timeout.Start();

	if(!m_Enabled)
		return false;

	bool renablePid = false;

	if(m_Left_Arm_Controller->IsEnabled() || m_Right_Arm_Controller->IsEnabled()){
		disablePID();
		renablePid = true;
	}

	if(m_Right_Talon->getButton() && m_Left_Talon->getButton() && m_Saftey_Button->Get()){
		throw CalibrationError(this, "ArmModule::calibrate()", "All three buttons are pressed (wiring issue)");
	}
	while (!m_Right_Talon->getButton() || !m_Left_Talon->getButton()) {

		if(timeout.Get() > MAX_CALIBRATE_TIME_OUT){
			throw CalibrationError(this, "ArmModule::calibrate()", "calibration timed out");
		}


		if(m_Right_Talon->getButton()) {
			m_Right_Talon->Set(0);
		} else {
			m_Right_Talon->Set(MAX_CALIBRATE_RIGHT_POWER);
		}

		if(m_Left_Talon->getButton()) {
			m_Left_Talon->Set(0);
		} else {
			m_Left_Talon->Set(-MAX_CALIBRATE_LEFT_POWER);
		}

		Wait(0.005);
	}

	m_Left_Talon->Set(0);
	m_Right_Talon->Set(0);

	m_Right_Encoder->Reset();
	m_Left_Encoder->Reset();

	Timer* timeTaken = new Timer();
	timeTaken->Start();


	while(timeTaken->Get() < MAX_CALIBRATE_TIME_IN) {
		m_Right_Talon->Set(-.5);
		m_Left_Talon->Set(.5);

		Wait(0.005);
	}


	m_Left_Talon->Set(0);
	m_Right_Talon->Set(0);

	if(m_Right_Talon->getButton()) {
		throw CalibrationError(this, "ArmModule::calibrate()", "check Right button, it might be unplugged");
	}

	if(m_Left_Talon->getButton()) {
		throw CalibrationError(this, "ArmModule::calibrate()", "check Left button, it might be unplugged");
	}

	if(m_Right_Encoder->PIDGet() > MAX_DELTA_X - MIN_CALIBRATION_DISTANCE) {
		throw CalibrationError(this, "ArmModule::calibrate()", "Arm right encoder might be unplugged");
	}

	if(m_Left_Encoder->PIDGet() < MIN_CALIBRATION_DISTANCE) {
		throw CalibrationError(this, "ArmModule::calibrate()", "Arm left encoder might be unplugged");
	}

	timeTaken->Stop();

	m_Calibrating = false;
	m_Has_Calibrated = true;

	if(renablePid)
		enablePID();

	return true;
}

void ArmModule::syncCalibrate(){
	std::thread t(ArmModule::callSyncCalibrate, this);
}

void ArmModule::callSyncCalibrate(void* m){
	((ArmModule*)m)->calibrate();
}

void ArmModule::reset(){
	m_Left_Encoder->Reset();
	m_Right_Encoder->Reset();
	resetPersist();
}

void ArmModule::resetPersist(){
	m_Difference_Controller->Reset();
	m_Right_Arm_Controller->Reset();
	m_Left_Arm_Controller->Reset();
}

void ArmModule::setManual(bool man){
	m_Manual = man;
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

bool ArmModule::isManual(){
	return m_Manual;
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

std::vector<double> ArmModule::getLoggingData() {

	std::vector<double> data;
	data.push_back(m_Right_Arm_Controller->Get());
	data.push_back(m_Right_Arm_Controller->GetSetpoint());
	data.push_back(m_Right_Arm_Controller->GetError());
	data.push_back(m_Right_Arm_Controller->IsEnabled());

	data.push_back(m_Left_Arm_Controller->Get());
	data.push_back(m_Left_Arm_Controller->GetSetpoint());
	data.push_back(m_Left_Arm_Controller->GetError());
	data.push_back(m_Left_Arm_Controller->IsEnabled());

	return data;

}

std::vector<std::string> getLoggingHeader() {

	std::vector<std::string> headers;

	headers.push_back("r_get");
	headers.push_back("r_getSetpoint");
	headers.push_back("r_getError");
	headers.push_back("r_isEnabled");

	headers.push_back("l_get");
	headers.push_back("l_getSetpoint");
	headers.push_back("l_getError");
	headers.push_back("l_isEnabled");

	return headers;

}

void ArmModule::setLeftPID(double p, double i, double d) {
	m_Left_Arm_Controller->SetPID(p, i, d);
}

void ArmModule::setRightPID(double p, double i, double d) {
	m_Right_Arm_Controller->SetPID(p, i, d);
}

void ArmModule::setDiffPID(double p, double i, double d) {
	m_Difference_Controller->SetPID(p, i, d);
}

double ArmModule::getLeftP() {
	return m_Left_Arm_Controller->GetP();
}

double ArmModule::getLeftI() {
	return m_Left_Arm_Controller->GetI();
}

double ArmModule::getLeftD() {
	return m_Left_Arm_Controller->GetD();
}

double ArmModule::getRightP() {
	return m_Right_Arm_Controller->GetP();
}

double ArmModule::getRightI() {
	return m_Right_Arm_Controller->GetI();
}

double ArmModule::getRightD() {
	return m_Right_Arm_Controller->GetD();
}

double ArmModule::getDiffP() {
	return m_Difference_Controller->GetP();
}

double ArmModule::getDiffD() {
	return m_Difference_Controller->GetD();
}

double ArmModule::getDiffI() {
	return m_Difference_Controller->GetI();
}

std::vector<std::string> ArmModule::getLoggingHeader() {
}

void ArmModule::setOutputRange(float min, float max) {
	m_Difference_Controller->SetOutputRange(min, max);
	m_Right_Arm_Controller->SetOutputRange(min, max);
	m_Left_Arm_Controller->SetOutputRange(min, max);
}

void ArmModule::setRightOutputRange(float min, float max) {
	m_Right_Arm_Controller->SetOutputRange(min, max);
}
