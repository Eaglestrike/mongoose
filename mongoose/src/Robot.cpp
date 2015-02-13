
#include <iostream>

#include "WPIlib.h"
#include "Modules/Modules.h"
#include "Settings.h"

class Robot: public IterativeRobot
{
private:
	LiveWindow *lw;
	ElevatorModule* module;
	ElevatorModule* elevator;

	void RobotInit()
	{
		lw = LiveWindow::GetInstance();
<<<<<<< HEAD
		elevator = new ElevatorModule(ELEVATOR_1, ELEVATOR_2, 1);
=======
		module = new ElevatorModule()

>>>>>>> 5f8019bc399807f6d6944f40e3aa916c02f2b84f
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
