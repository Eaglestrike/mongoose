#include "WPILib.h"


class Robot: public IterativeRobot
{
private:
	LiveWindow *lw;
	Victor* left1;
	Victor* left2;
	Victor* right1;
	Victor* right2;
	Joystick* leftJoy;
	Joystick* rightJoy;
	Compressor* comp;
	Solenoid* cole;

	void RobotInit()
	{
		lw = LiveWindow::GetInstance();
		std::cout << "GGG" << std::endl;
		left1 = new Victor(0);
		left2 = new Victor(1);
		right1 = new Victor(3);
		right2 = new Victor(2);
		leftJoy = new Joystick(0);
		rightJoy = new Joystick(1);
		comp = new Compressor(0);
		comp->SetClosedLoopControl(true);
		cole = new Solenoid(0);
	}

	void AutonomousInit()
	{

	}

	void AutonomousPeriodic()
	{

	}

	void TeleopInit()
	{

	}

	bool last;
	int counter = 0;

	bool driveLast;
	int driveCounter = 0;

	int printcounter = 0;

	void TeleopPeriodic()
	{

		if(printcounter % 10 == 0)
			std::cout << "counter: " << driveCounter << " counter % 4 == 0: " << (driveCounter % 4 == 0) << " right trigger: " << rightJoy->GetTrigger() << std::endl;

		if(last != rightJoy->GetRawButton(4))
			counter++;
		last = rightJoy->GetRawButton(4);

		if(counter % 4 == 0)
			cole->Set(true);
		else if(counter % 2 == 0)
			cole->Set(false);


		if(driveLast != rightJoy->GetTrigger())
			driveCounter++;
		driveLast = rightJoy->GetTrigger();

		drive(leftJoy->GetY(), -rightJoy->GetX(), 2, 1.8);

		printcounter++;
		Wait(0.05);

	}

	void drive(double throttle, double angle, double throttlePower, double anglePower) {

		double leftMotorOutput =  0;
		double rightMotorOutput = 0;


		if(angle > 0.0)
			angle  = pow(angle, anglePower);
		else
			angle = -pow(-angle, anglePower);

		if(driveCounter % 4 == 0){
			if(throttle > 0.0)
				throttle = pow(throttle, throttlePower);
			else
				throttle = -pow(-throttle, throttlePower);
		} else if(driveCounter % 2 == 0){
			throttle = victor_linearize(throttle);
		}

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
			}
			else {
				leftMotorOutput = throttle - angle;
				rightMotorOutput = -fmax(-throttle,-angle);
			}

		}
		left1->Set(leftMotorOutput);
		left2->Set(leftMotorOutput);
		right1->Set(-rightMotorOutput);
		right2->Set(-rightMotorOutput);
	}

	void TestPeriodic()
	{
		//std::cout << ": p[P  " << std::endl;
//		right1->Set(leftJoy->GetY());
//		right1->Set(rightJoy->GetY());
		lw->Run();
	}


	float victor_linearize(double goal_speed)
	{
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

START_ROBOT_CLASS(Robot);
