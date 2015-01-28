#include "WPILib.h"
#include <iostream>

class Robot: public IterativeRobot
{
private:
	LiveWindow *lw;
	Encoder* enc1;
	Victor* motor;
	float p = .02;
	float i = .005;
	float d = .01;
	Timer* time;
	float prevError = 0;
	float totalError = 0;
	float setPoint = 0;

	void RobotInit()
	{
		lw = LiveWindow::GetInstance();
		enc1 = new Encoder(0,1);
		motor = new Victor(1);
		time = new Timer();
	}
	void AutonomousInit()
	{

	}

	void AutonomousPeriodic()
	{

	}

	void TeleopInit()
	{
		setSetPoint(1000);
	}

	void TeleopPeriodic()
	{
		while(true) {
			time->Start();
			float error = enc1->Get() - getSetPoint();
			totalError +=error*time->Get();
			motor->Set(error*p + d*(error - prevError)/time->Get() + totalError*i);
			time->Stop();
			time->Reset();
			prevError = error;
		}
	}

	void TestPeriodic()
	{
		lw->Run();
	}

	double getSetPoint() {
		return setPoint;
	}

	void setSetPoint(double setpoint) {
		setPoint = setpoint;
	}
};

START_ROBOT_CLASS(Robot);
