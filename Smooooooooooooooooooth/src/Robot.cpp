#include "WPILib.h"
#include <math.h>
#include <thread>

class Robot: public IterativeRobot
{
private:
	LiveWindow *lw;
	Victor* rVictor1;
	Victor* rVictor2;
	Victor* lVictor1;
	Victor* lVictor2;
	Encoder* lEncoder;
	Encoder* rEncoder;
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
	int re1 = 0;
	int re2 = 0;
	int le1 = 0;
	int le2 = 0;


	/*    */
	float maxAcceleration = 6;
	double maxVelocity;
	int pressed = 1;
	float targetVelocity;

	void RobotInit()
	{
		lw = LiveWindow::GetInstance();
		rVictor1 = new Victor(rv1);
		rVictor2 = new Victor(rv2);
		lVictor1 = new Victor(lv1);
		lVictor2 = new Victor(lv2);
		lEncoder = new Encoder(1e1, 1e2);
		rEncoder = new Encoder(re1, re2);
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
		setTargetVelocity();
//		if(ljoy->getX() > maxPower(maxAcceleration)) {
//			setPower(maxPower(maxAcceleration), maxPower(maxAcceleration));
//		}
//		else {
//			setPower(ljoy->getX(), ljoy->getX());
//		}
//		maxAcceleration = sqrt(rom->getX()*rom->getX() + rom->getY()*rom->getY() + rom->getZ()*rom->getZ());

		std::thread calibrating;

		if(ljoy->GetRawButton(10)){
			pressed++;
		}
		if(pressed % 4 == 0) {
			calibrate();
		}
		setTargetVelocity();

	}

	void TestPeriodic()
	{
		lw->Run();
	}

	void calibrate(float targetVelocity) {
		float currentVelocity = (lEncoder->GetRate() + rEncoder->GetRate())/2;
		float error = currentVelocity - targetVelocity;
		float p = 0;
	    setPower(lVictor1->Get() - error*p, rVictor1->Get() - .01);

	}

	double maxPower(float acceleration) {
		return sqrt(acceleration/2);
	}

	void setPower(double left, double right) {
		lVictor1->Set(left);
		lVictor2->Set(left);
		rVictor1->Set(-right);
		rVictor2->Set(-right);
	}

	double getTargetVelocity(float throttle) {
		return throttle*maxVelocity;
	}

	void setTargetVelocity() {
		targetVelocity = getTargetVelocity(ljoy->GetY());
	}


};

START_ROBOT_CLASS(Robot);
