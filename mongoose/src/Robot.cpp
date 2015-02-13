#include "WPILib.h"
#include <iostream>

class Robot: public IterativeRobot
{
private:
	LiveWindow *lw;
	ElevatorModule* module;

	void RobotInit()
	{
		lw = LiveWindow::GetInstance();
		module = new ElevatorModule()

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
};

START_ROBOT_CLASS(Robot);
