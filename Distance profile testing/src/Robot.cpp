#include "WPILib.h"
#include "DistanceProfile.h"
#include "Xbox.h"
#include <iostream>

class Robot: public IterativeRobot
{
private:
	LiveWindow *lw;
	Victor *mot;
	Encoder *enc;
	DistanceProfile *prof;
	PIDController *control1;
	Timer *time;
	Xbox *controller;
	float p;
	float i;
	float d;
	int in = 0;

	void RobotInit()
	{
		p = 0;
		i = 0;
		d = 0;
		lw = LiveWindow::GetInstance();
		mot = new Victor(0);
		enc = new Encoder(0,1);
		control1 = new PIDController(p, i, d, enc, mot);
		prof = new DistanceProfile(0, 15, 5);
		time = new Timer();
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
		time->Start();
	}

	void TeleopPeriodic()
	{
		if(controller->getX()) p += .01;
		if(controller->getY()) i += .01;
		if(controller->getA()) d += .01;
		control1->SetPID(p, i ,d);
		control1->SetSetpoint(prof->getSetPoint(time->Get()));
		in++;
		if(in % 60 == 0) std::cout << " P:" << p << " D:" << d << " I:" << i << std::endl;
	}

	void DisabledPeriodic() {
		time->Stop();
	}
	void TestPeriodic()
	{
		std::cout << "GIT" << std::endl;
		lw->Run();
	}
};

START_ROBOT_CLASS(Robot);
