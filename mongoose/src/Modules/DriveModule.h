
#ifndef __DRIVE_MODULE_H
#define __DRIVE_MODULE_H

#include <WPILib.h>
#include "RobotModule.h"
#include "../Peripherals/ADXRS453Z.h"

/*   Linear Functions   */
class DriveFunction {  // methods in this are defaults
public:
	double transformThrottle(double throttle) {
		return throttle;
	}

	double transformAngle(double angle){ 
		return angle;
	}
}; 

class DriveModule : public RobotModule{

	DriveModule(int lv1, int lv2, int rv1, int rv2, int l_EA, int l_EB) ;
	~DriveModule();
public:
	// void Enable();
	// void Disable();
	void resetEncoders();
	void setPower(double left, double right);
	void drive(double throttle, double angle);
	void enable();
	void disable();
	void reset();
	//void setJoystickDrive();
	void setTargetVelocity(float vel);
	double getPower();



private:
	/*   Hardware Stuff    */
	Victor* m_Left_Victor_1;
	Victor* m_Left_Victor_2;
	Victor* m_Right_Victor_1;
	Victor* m_Right_Victor_2;
	Encoder* m_Left_Encoder;
	ADXRS453Z* m_Gyro;

	/* Pid Controller */
	// PIDController controller;
	// PIDReader angleReader;

	/*drive Functions */
	DriveFunction driveFunc;

	/*    */
	float targetVelocity;


};

#endif
