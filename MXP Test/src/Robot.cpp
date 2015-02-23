#include "WPILib.h"
#include <iostream>

class Robot: public IterativeRobot
{
private:
	LiveWindow *lw;
	DigitalInput* testButton;

	void RobotInit()
	{
		lw = LiveWindow::GetInstance();
		testButton = new DigitalInput(9);
	}

	void AutonomousInit()
	{

	}

	void AutonomousPeriodic()
	{
		std::cout << testButton->Get() << std::endl;
		Wait(0.1);
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
