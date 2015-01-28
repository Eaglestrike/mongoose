#include "WPILib.h"
#include "DistanceProfile.h"
#include <iostream>

class Robot: public IterativeRobot
{
private:
	LiveWindow *lw;
	DistanceProfile *prof;
	DistanceProfile *prof2;
	Timer *times;

	void RobotInit()
	{
		lw = LiveWindow::GetInstance();
		prof = new DistanceProfile(5, 20, 10);
		times = new Timer();
		prof2 = new DistanceProfile(13.7, .01, 13);
	}

	void AutonomousInit()
	{

	}

	void AutonomousPeriodic()
	{

	}

	void TeleopInit()
	{
		times->Start();
		while(times->Get() < 20) {
			//std::cout<<prof->getSetPoint(times->Get()) << " time : " << times->Get()<<std::endl;
			std::cout<<"second "<<prof2->getSetPoint(times->Get())<<" time : " << times->Get()<<std::endl;
			Wait(1);
		}
		times->Stop();
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
