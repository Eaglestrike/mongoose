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

	void TeleopPeriodic()
	{

		if(last != rightJoy->GetRawButton(4))
			counter++;
		last = rightJoy->GetRawButton(4);

		if(counter % 4 == 0)
			cole->Set(true);
		else if(counter % 2 == 0)
			cole->Set(false);

		std::cout << rightJoy->GetZ() << std::endl;

		drive(leftJoy->GetY(), -rightJoy->GetX(), 2, 1);

		Wait(0.05);

	}

	void drive(double throttle, double angle, double throttlePower, double anglePower) {

		double leftMotorOutput =  0;
		double rightMotorOutput = 0;

		if(angle > 0.0)
			angle  = pow(angle, anglePower);
		else
			angle = -pow(-angle, anglePower);

		if(throttle > 0.0)
			throttle = pow(throttle, throttlePower);
		else
			throttle = -pow(-throttle, throttlePower);

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
		lw->Run();
	}
};

START_ROBOT_CLASS(Robot);
