#include "WPILib.h"

class Robot: public IterativeRobot
{
private:
	LiveWindow *lw;
	Encoder* enc1;
	Victor* motor;
	float p = .02;
	float setPoint = 0;

	void RobotInit()
	{
		lw = LiveWindow::GetInstance();
		enc1 = new Encoder(0,1);
		motor = new Victor(1);
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
			float error = enc1->Get() - getSetPoint();
			motor->Set(error*p);
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
