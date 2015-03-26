#include "DriveModule.h"


DriveModule::DriveModule(int lv1, int lv2, int rv1, int rv2, int l_EA, int l_EB, int gyroPort) :
	RobotModule(std::string("DriveModule"))
{

	m_Left_Victor_1 = new Victor(lv1);
	m_Left_Victor_2 = new Victor(lv2);
	m_Right_Victor_1 = new Victor(rv1);
	m_Right_Victor_2 = new Victor(rv2);
//Cole was here
	m_Encoder = new Encoder(l_EA, l_EB);
	m_Encoder->SetReverseDirection(false);
	m_Encoder->SetDistancePerPulse(FEET_PER_DRIVE_PULSE);

	m_Gyro = new ADXRS453Z(gyroPort);
	m_Gyro->reset();

	m_Drive_Output = new PIDOut();
	m_Angle_Output = new PIDOut();

	m_Drive_Controller = new PIDController(DRIVE_PRAC_P, DRIVE_PRAC_I, DRIVE_PRAC_D, m_Encoder, m_Drive_Output);
	m_Angle_Controller = new PIDController(ANGLE_PRAC_P, ANGLE_PRAC_I, ANGLE_PRAC_D, m_Gyro, m_Angle_Output);

}

void DriveModule::enable(){
	RobotModule::enable();
}

void DriveModule::disable() {
	reset();
	RobotModule::disable();
}

void DriveModule::reset() {
	m_Encoder->Reset();
	m_Gyro->reset();
}

void DriveModule::setPower(double left, double right) {
	if(!m_Enabled) return;

	if(left > 1)
		left = 1;
	else if(left < -1)
		left = -1;

	if(right > 1)
		right = 1;
	else if(right < -1)
		right = -1;

	m_Left_Victor_1->Set(left);
	m_Left_Victor_2->Set(left);
	m_Right_Victor_1->Set(-right);
	m_Right_Victor_2->Set(-right);

}


void DriveModule::drive(double throttle, double angle) {


	throttle = driveFunc.transformThrottle(throttle);
	angle = driveFunc.transformAngle(angle);

	double leftMotorOutput =  0;
	double rightMotorOutput = 0;

	if(throttle > 0.0) {
		angle = -angle;
		if(angle < 0.0) {
			leftMotorOutput = (throttle + angle);
			rightMotorOutput = fmax(throttle, -angle);
		}
		else {
			leftMotorOutput = fmax(throttle, angle);
			rightMotorOutput = (throttle - angle);
		}
	}
	else {
		if(angle > 0.0) {
			leftMotorOutput = -fmax(-throttle, angle);
			rightMotorOutput = throttle + angle;
			//std::cout << rightMotorOutput << std::endl;
		}
		else {
			leftMotorOutput = throttle - angle;
			rightMotorOutput = -fmax(-throttle,-angle);
		}

	}
	setPower(leftMotorOutput, rightMotorOutput);
}

void DriveModule::setAngleSetpoint(float setpoint) {
	m_Angle_Controller->SetSetpoint(setpoint);
}

double DriveModule::getAngleSetpoint(){
	return m_Angle_Controller->GetSetpoint();
}

void DriveModule::setDriveSetpoint(float setpoint) {
	m_Drive_Controller->SetSetpoint(setpoint);
}
double DriveModule::getLeftPower(){
	return m_Left_Victor_1->Get();
}

double DriveModule::getRightPower(){
	return m_Right_Victor_1->Get();
}

double DriveModule::getEncoderDistance(){
	return m_Encoder->PIDGet();
}

double DriveModule::getDriveP() {
	return m_Drive_Controller->GetP();
}

double DriveModule::getDriveI() {
	return m_Drive_Controller->GetI();
}

double DriveModule::getDriveD() {
	return m_Drive_Controller->GetD();
}

void DriveModule::setDrivePID(double p, double i, double d) {
	m_Drive_Controller->SetPID(p, i, d);
}

double DriveModule::getDriveError() {
	return m_Drive_Controller->GetError();
}
double DriveModule::getAngleP() {
	return m_Angle_Controller->GetP();
}

double DriveModule::getAngleI() {
	return m_Angle_Controller->GetI();
}

double DriveModule::getAngleD() {
	return m_Angle_Controller->GetD();
}

void DriveModule::setAnglePID(double p, double i, double d) {
	m_Angle_Controller->SetPID(p, i, d);
}

double DriveModule::getAngleError() {
	return m_Angle_Controller->GetError();
}

void DriveModule::disablePID() {
	m_Drive_Controller->Disable();
	m_Angle_Controller->Disable();
}

void DriveModule::enablePID() {
	m_Drive_Controller->Enable();
	m_Angle_Controller->Enable();
}

double DriveModule::getDriveOutput() {
	return m_Drive_Output->getOutput();
}

double DriveModule::getAngleOutput() {
	return m_Angle_Output->getOutput();
}

double DriveModule::getAngle() {
	return m_Gyro->getAngle();
}

DriveModule::~DriveModule() {

}

std::vector<std::string> DriveModule::getLoggingHeader() {
	std::vector<std::string> headers;
	headers.push_back("Gyro_angle");
	headers.push_back("Right_Victor1_Power");
	headers.push_back("Right_Victor2_Power");
	headers.push_back("Left_Victor1_Power");
	headers.push_back("Left_Victor2_Power");
	headers.push_back("Encoder_Value");
	return headers;
}
std::vector<double> DriveModule::getLoggingData() {
	std::vector<double> data;
	data.push_back(m_Gyro->getAngle());
	data.push_back(m_Right_Victor_1->Get());
	data.push_back(m_Right_Victor_2->Get());
	data.push_back(m_Left_Victor_1->Get());
	data.push_back(m_Left_Victor_2->Get());
	data.push_back(m_Encoder->Get());
	return data;
}

void DriveModule::setAngleOutputRange(double min, double max) {
	m_Angle_Controller->SetOutputRange(min, max);
}

void DriveModule::setDriveOutputRange(double min, double max) {
	m_Angle_Controller->SetOutputRange(min, max);
}
