#include "DriveModule.h"
#include <math.h> 


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

	if(throttle > 0.0) {
		if(angle < 0.0) {
			leftMotorOutput = throttle - angle;
			rightMotorOutput = fmin(throttle, angle);
		}
		else {
			leftMotorOutput = fmin(throttle, -angle);
			rightMotorOutput = throttle + angle;
		}
	}
	else {
	 	if(angle > 0.0) {
			leftMotorOutput = -fmin(-throttle, angle);
			rightMotorOutput = throttle + angle;
		}
		else {
			leftMotorOutput = throttle - angle;
			rightMotorOutput = -fmin(-throttle,-angle);
		}
	}
	if(throttle == 0 && angle == 0) {
		leftMotorOutput = 0;
		rightMotorOutput = 0;
	}
	if(angle == 0) {
		leftMotorOutput = throttle;
		rightMotorOutput = throttle;
	}
	setPower(leftMotorOutput, rightMotorOutput);
}

DriveModule::~DriveModule() {

}
