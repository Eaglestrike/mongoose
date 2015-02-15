
#include <iostream>

#include "WPIlib.h"
#include "Modules/Modules.h"
#include "Settings.h"
#include "PrintQueue.h"

class Robot: public IterativeRobot
{
private:
	LiveWindow *lw;
	ElevatorModule* elevatorModule;
	DriveModule* driveModule;

	void RobotInit()
	{
		lw = LiveWindow::GetInstance();
		elevatorModule = new ElevatorModule(ELEVATOR_1, ELEVATOR_2, ELEVATOR_SAFTEY_BUTTON, ELEVATOR_ENCODER_A, ELEVATOR_ENCODER_B);
		driveModule = new DriveModule(DRIVE_LEFT_1, DRIVE_LEFT_2, DRIVE_RIGHT_1, DRIVE_RIGHT_2, DRIVE_ENCODER_A, DRIVE_ENCODER_B, DRIVE_GYRO);
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
