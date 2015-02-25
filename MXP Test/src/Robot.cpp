#include "WPILib.h"
#include <iostream>

class Robot: public IterativeRobot
{
private:
	LiveWindow *lw;
	DigitalInput* testButton;
	TalonSRX* v;

	void RobotInit()
	{
		lw = LiveWindow::GetInstance();
		testButton = new DigitalInput(14);
		v = new Victor(10);
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
