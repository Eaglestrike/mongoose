#include "WPILib.h"
#include "RobotModule.h"

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

	DriveModule(int lv1, int lv2, int rv1, int rv2, int l_EA, int l_EB, int r_EA, int r_EB) ;
	~DriveModule();
public:
	// void Enable();
	// void Disable();
	void resetEncoders();
	void setPower(double left, double right);
	void drive(double throttle, double angle);
	void Enable();
	void Disable();
	void Reset();
	//void setJoystickDrive();

	double getPower();



private:
	/*   Hardware Stuff    */
	Victor lVictor1;
	Victor lVictor2;
	Victor rVictor1;
	Victor rVictor2;
	Encoder lEncoder; 
	Encoder rEncoder;
	Gyro rob_Gyro;

	/* Pid Controller */
	// PIDController controller;
	// PIDReader angleReader;

	/*drive Functions */
	DriveFunction driveFunc;


};
