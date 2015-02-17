
#ifndef __DRIVE_MODULE_H
#define __DRIVE_MODULE_H

#include "WPILib.h"
#include "Modules/RobotModule.h"
#include <math.h>
#include <algorithm>
#include "Peripherals/ADXRS453Z.h"



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

class AustinFunction: public DriveFunction{
public:
	double transformThrottle(double goal_speed){
		const double deadband_value = 0.082;

		if (goal_speed > deadband_value)
			goal_speed -= deadband_value;
		else if (goal_speed < -deadband_value)
			goal_speed += deadband_value;
		else
			goal_speed = 0.0;
		goal_speed = goal_speed / (1.0 - deadband_value);

		double goal_speed2 = goal_speed * goal_speed;
		double goal_speed3 = goal_speed2 * goal_speed;
		double goal_speed4 = goal_speed3 * goal_speed;
		double goal_speed5 = goal_speed4 * goal_speed;
		double goal_speed6 = goal_speed5 * goal_speed;
		double goal_speed7 = goal_speed6 * goal_speed;

		// Original untweaked one.
		//double victor_fit_c		= -1.6429;
		//double victor_fit_d		= 4.58861e-08;
		//double victor_fit_e		= 0.547087;
		//double victor_fit_f		= -1.19447e-08;

		// Constants for the 5th order polynomial
		double victor_fit_e1		= 0.437239;
		double victor_fit_c1		= -1.56847;
		double victor_fit_a1		= (- (125.0 * victor_fit_e1  + 125.0 * victor_fit_c1 - 116.0) / 125.0);
		double answer_5th_order = (victor_fit_a1 * goal_speed5
			+ victor_fit_c1 * goal_speed3
			+ victor_fit_e1 * goal_speed);

		// Constants for the 7th order polynomial
		double victor_fit_c2 = -5.46889;
		double victor_fit_e2 = 2.24214;
		double victor_fit_g2 = -0.042375;
		double victor_fit_a2 = (- (125.0 * (victor_fit_c2 + victor_fit_e2 + victor_fit_g2) - 116.0) / 125.0);
		double answer_7th_order = (victor_fit_a2 * goal_speed7
			+ victor_fit_c2 * goal_speed5
			+ victor_fit_e2 * goal_speed3
			+ victor_fit_g2 * goal_speed);


		// Average the 5th and 7th order polynomials
		double answer =  0.85 * 0.5 * (answer_7th_order + answer_5th_order)
		+ .15 * goal_speed * (1.0 - deadband_value);

		if (answer > 0.001)
			answer += deadband_value;
		else if (answer < -0.001)
			answer -= deadband_value;

		return answer;
	}
};

class DriveModule : public RobotModule{

public:

	DriveModule(int lv1, int lv2, int rv1, int rv2, int l_EA, int l_EB, int gyroPort) ;
	~DriveModule();
	void drive(double throttle, double angle);
	void enable();
	void disable();
	void reset();
	double getPower();
	void resetEncoders();

	double getLeftPower();
	double getRightPower();

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

	void setPower(double left, double right);

};

#endif
