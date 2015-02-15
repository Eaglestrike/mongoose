
#include <iostream>

#include "WPIlib.h"
#include "Modules/Modules.h"
#include "Settings.h"
#include "PrintQueue.h"

class Robot: public IterativeRobot
{
private:
	LiveWindow *lw;
	ElevatorModule* module;
	ElevatorModule* elevator;
	PrintQueue* qu;

	void RobotInit()
	{
		lw = LiveWindow::GetInstance();
		elevator = new ElevatorModule(ELEVATOR_1, ELEVATOR_2, ELEVATOR_SAFTEY_BUTTON, ELEVATOR_ENCODER_A, ELEVATOR_ENCODER_B);
		qu = new PrintQueue(10);
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
		qu->add("piss");
	}

	void TestPeriodic()
	{
		lw->Run();
	}
};

START_ROBOT_CLASS(Robot);
