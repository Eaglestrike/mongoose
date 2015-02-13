#include "DriveModule.h"
#include <math.h> 
#include <algorithm>


DriveModule::DriveModule(int lv1, int lv2, int rv1, int rv2, int l_EA, int l_EB) :
	RobotModule(std::string("DriveModule"))
{

	m_Left_Victor_1 = new Victor(lv1);
	m_Left_Victor_2 = new Victor(lv2);
	m_Right_Victor_1 = new Victor(rv1);
	m_Right_Victor_2 = new Victor(rv2);

	m_Gyro = new ADXRS453Z(1);

	m_Left_Encoder->SetReverseDirection(true);

	/* PID */

}

void DriveModule::enable(){

}

void DriveModule::disable() {
	reset();
}

void DriveModule::reset() {
	m_Left_Encoder->Reset();
}

void DriveModule::setPower(double left, double right) {
	m_Left_Victor_1->Set(left);
	m_Left_Victor_2->Set(left);
	m_Right_Victor_1->Set(-right);
	m_Right_Victor_2->Set(-right);

}

void DriveModule::setTargetVelocity(float vel)  {
	targetVelocity = vel;
}

void DriveModule::drive(double throttle, double angle) {
	driveFunc.transformThrottle(throttle);
	driveFunc.transformAngle(angle);

	double leftMotorOutput =  0;
	double rightMotorOutput = 0;

			//std::cout << angle <<std::endl;
	//		if(angle < 0.0)
	//			angle = -(angle * angle);
	//		else
	//			angle = angle * angle;
	if(angle ==0) angle = 0;
	else if(angle < 0.0) {
		angle  = - pow(-angle, 1.842);
	}
	else angle = pow(angle, 1.842);

	if(throttle > 0.0)
		throttle = throttle * throttle;
	else
		throttle = - throttle * throttle;

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

DriveModule::~DriveModule() {

}
