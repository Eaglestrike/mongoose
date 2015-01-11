#include "WPILib.h"

class Robot: public IterativeRobot
{
private:
	LiveWindow *lw;
	Victor* rVictor1;
	Victor* rVictor2;
	Victor* lVictor1;
	Victor* lVictor2;
	BuiltInAccelerometer* rom;

	/*Ports */
	int rv1 = 0;
	int rv2 = 0;
	int lv1 = 0;
	int lv2 = 0;

	void RobotInit()
	{
		lw = LiveWindow::GetInstance();
		rVictor1 = new rVictor1(rv1);
		rVictor2 = new rVictor2(rv2);
		lVictor1 = new lVictor1(lv1);
		lVictor2 = new lVictor2(lv2);
		rom = new BuiltInAccelerometer();

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

	void TeleopPeriodic()
	{

	}

	void TestPeriodic()
	{
		lw->Run();
	}

	void *calibrate() {
		float currentVelocity = (lEncoder.getRate() + rEncoder.getRate())/2;
		while(currentVelociy  != targetVelocity) {
			currentVelocity = (lEncoder.getRate() + rEncoder.getRate())/2;
			if(currentVelocity > targetVelocity) {

			}
			else {

			}
		}

	}
	void maxPower(float acceleration) {

	}
	void setPower() {

	}
};

START_ROBOT_CLASS(Robot);
