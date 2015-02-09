#include "WPILib.h"
#include "ADXRS453Z.h"
#include <iostream>

class Robot: public IterativeRobot
{
private:
	LiveWindow *lw;
	ADXRS453Z* gyro;

	void RobotInit()
	{
		dp("RobotInit()");
		lw = LiveWindow::GetInstance();
		gyro = new ADXRS453Z(0);
	}

	void AutonomousInit()
	{

	}

	void AutonomousPeriodic()
	{

	}

	void TeleopInit()
	{
		gyro->reset();
	}

	int counter = 0;

	void TeleopPeriodic()
	{

		if(counter % 5 == 0)
			std::cout << gyro->getAngle() << std::endl;

		counter++;

		Wait(0.05);
	}

	void TestPeriodic()
	{
		lw->Run();
	}
};

START_ROBOT_CLASS(Robot);
