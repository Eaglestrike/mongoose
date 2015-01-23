#include "WPILib.h"
#include "DistanceProfile.h"
#include "DistanceProfileManager.h"
#include "Xbox.h"
#include <iostream>
#include <vector>

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
	DistanceProfile *prof1;
	DistanceProfileManager *manager;
	std::vector<DistanceProfile> profs;
	bool nextProf = false;
	bool notEnded = true;
	float p = .007;
	float i;
	float d;
	int in = 0;

	void RobotInit()
	{
		std::cout<< "PI" << std::endl;
		lw = LiveWindow::GetInstance();
		mot = new Victor(0);
		enc = new Encoder(0,1);
		control1 = new PIDController(.002, 0, 0, enc, mot);
		prof = new DistanceProfile(3000, 0, 5);
		prof1 = new DistanceProfile(0, 1500, 2);
		DistanceProfile profs1(3000,0,5);
		DistanceProfile profs2(0, 1500, 2);
		profs.push_back(profs1);
		profs.push_back(profs2);
		manager = new DistanceProfileManager(profs);
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
		control1->Enable();
		std::cout << "8==D" << std::endl;
	}

	void TeleopPeriodic()
	{
		if(!manager->isDone)
			control1->SetSetpoint((float)manager->getSetPoint(*time, *enc));
//		if(!prof->isDone)
//			control1->SetSetpoint(prof->getSetPoint(time->Get()));
//		if(time->Get() >= 6 && prof->isDone && !prof1->isDone) {
//			time->Reset();
//			enc->Reset();
//		}
//		if(prof->isDone && !prof1->isDone && time->Get() < 5) {
//			control1->SetSetpoint(prof1->getSetPoint(time->Get()));
//		}
		in++;
		if(in % 60 == 0) {
			std::cout << " P:"  << control1->GetP() << " I:" << i << " D:" << d << std::endl;
			std::cout << "enc" << enc->Get() << " GE " <<  control1->GetError() << " setPoint" << control1->GetSetpoint()<< " time: " << time->Get() <<std::endl;
		}
	}
	void DisabledPeriodic() {
		time->Reset();
		time->Stop();
		enc->Reset();
		//mot->Set(0);
	}
	void TestPeriodic()
	{
		std::cout << "GIT" << std::endl;
		lw->Run();
	}
	void queDistanceProfiles() {

	}

};

START_ROBOT_CLASS(Robot);
