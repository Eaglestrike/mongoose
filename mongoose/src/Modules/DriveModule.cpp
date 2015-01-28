#include "DriveModule.h"
#include <math.h> 
#include <algorithm>


DriveModule::DriveModule(int lv1, int lv2, int rv1, int rv2, int l_EA, int l_EB, int r_EA, int r_EB) : 
RobotModule(std::string("DriveModule")),
lVictor1(lv1), lVictor2(lv2), rVictor1(rv1), rVictor2(rv2),
lEncoder(l_EA, l_EB), rEncoder(r_EA, r_EB), rob_Gyro(1) // whatever ports
{

	Enable();

	/* PID */

}

void DriveModule::Enable(){
	lEncoder.SetReverseDirection(true);
	rEncoder.SetReverseDirection(false);
}

void DriveModule::Disable() {
	Reset();
}

void DriveModule::Reset() {
	lEncoder.Reset();
	rEncoder.Reset();
}

void DriveModule::setPower(double left, double right) {
	lVictor1.Set(left);
	lVictor2.Set(left);
	rVictor1.Set(-right);
	rVictor2.Set(-right);

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
