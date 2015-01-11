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
	Joystick* ljoy;
	Joystick* rjoy;

	/*Ports */
	int rv1 = 0;
	int rv2 = 0;
	int lv1 = 0;
	int lv2 = 0;
	int portr= 0;
	int portl = 0;


	/*    */
	float maxAcceleration;

	void RobotInit()
	{
		lw = LiveWindow::GetInstance();
		rVictor1 = new rVictor1(rv1);
		rVictor2 = new rVictor2(rv2);
		lVictor1 = new lVictor1(lv1);
		lVictor2 = new lVictor2(lv2);
		rom = new BuiltInAccelerometer;
		rjoy = new Joystick(portr);
		ljoy = new Joystick(portl);

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
		if(ljoy->getX() > maxPower(maxAcceleration)) {
			setPower(maxPower(maxAcceleration), maxPower(maxAcceleration));
		}
		else {
			setPower(ljoy->getX(), ljoy->getX());
		}
	}

	void TestPeriodic()
	{
		lw->Run();
	}

	void *calibrate(float targetVelocity) {
		float currentVelocity = (lEncoder.getRate() + rEncoder.getRate())/2;
		while(currentVelociy  != targetVelocity) {
			currentVelocity = (lEncoder.getRate() + rEncoder.getRate())/2;
			if(currentVelocity > targetVelocity) {
				setPower(lVictor1.Get() - .01, rVictor1.Get() - .01);
			}
			else {
				setPower(lVictor1.Get() + .01, rVictor1.Get() + .01);
			}
		}

	}
	double maxPower(float acceleration) {
		return acceleration;
	}
	void setPower(double left, double right) {
		lVictor1.Set(left);
		lVictor2.Set(left);
		rVictor1.Set(-right);
		rVictor2.Set(-right);
	}

};

START_ROBOT_CLASS(Robot);
