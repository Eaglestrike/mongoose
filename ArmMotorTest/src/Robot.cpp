#include "WPILib.h"
#include "Xbox.h"

class Robot: public IterativeRobot
{
private:
	LiveWindow *lw;
	Victor* rVictor;
	Victor* lVictor;
	Xbox* controller;

	void RobotInit()
	{
		lw = LiveWindow::GetInstance();
		rVictor = new Victor(1);
		lVictor = new Victor(0);
		controller = new Xbox(0);
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
		rVictor->Set(-controller->getRX());
		lVictor->Set(controller->getLX());
	}

	void TestPeriodic()
	{
		lw->Run();
	}
};

START_ROBOT_CLASS(Robot);
