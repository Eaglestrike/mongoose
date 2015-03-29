#include "WPILib.h"
#include <iostream>

class Robot: public IterativeRobot
{
private:
	LiveWindow *lw;
	Encoder* leftArm;
	Encoder* drive;
	Encoder* rightArm;
	Encoder* elevator;
	DigitalInput* butt;

	void RobotInit()
	{
		lw = LiveWindow::GetInstance();
		elevator = new Encoder(10, 11);
		leftArm = new Encoder(4,5);
		rightArm = new Encoder(6,7);
		drive = new Encoder(8,9);
	}

	int i = 0;
	void AutonomousInit()
	{

	}

	void AutonomousPeriodic()
	{
		if(i % 15 == 0) {
			std::cout  << "right arm: " << rightArm->Get() << " leftArm: " << leftArm->Get() << " drive:" << drive->Get() << " elevator: " << elevator->Get() << "\n" ;

		}
		i++;
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
