
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
		elevator = new ElevatorModule(ELEVATOR_1, ELEVATOR_2, ELEVATOR_SAFTEY_BUTTON, ELEVATOR_ENCODER_A, ELEVATOR_ENCODER_B);
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
