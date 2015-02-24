#include "DriveModule.h"


DriveModule::DriveModule(int lv1, int lv2, int rv1, int rv2, int l_EA, int l_EB, int gyroPort) :
	RobotModule(std::string("DriveModule"))
{

	m_Left_Victor_1 = new Victor(lv1);
	m_Left_Victor_2 = new Victor(lv2);
	m_Right_Victor_1 = new Victor(rv1);
	m_Right_Victor_2 = new Victor(rv2);

	m_Left_Encoder = new Encoder(l_EA, l_EB);

	m_Gyro = new ADXRS453Z(gyroPort);

	m_Left_Encoder->SetReverseDirection(true);

	/* PID */
	m_Drive_Controller = new PIDController(DRIVE_1_P, DRIVE_1_I, DRIVE_1_D, m_Left_Encoder, m_Drive_Output);
	m_Angle_Controller = new PIDController(ANGLE_1_P, ANGLE_1_I, ANGLE_1_D, m_Gyro, m_Angle_Output);
}

void DriveModule::enable(){
	RobotModule::enable();
}

void DriveModule::disable() {
	reset();
}

void DriveModule::reset() {
	m_Left_Encoder->Reset();
	m_Gyro->reset();
}

void DriveModule::setPower(double left, double right) {
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

double DriveModule::getLeftPower(){
	return m_Left_Victor_1->Get();
}

double DriveModule::getRightPower(){
	return m_Right_Victor_1->Get();
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


DriveModule::~DriveModule() {

}
