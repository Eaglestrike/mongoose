#include "WPILib.h"
#include "DistanceProfile.h"
#include "DistanceProfileManager.h"
#include "Xbox.h"
#include <iostream>
#include <vector>


class PIDOut: public PIDOutput {
		float power = 0;
		void PIDWrite(float output) {
			power = output;
		}
		float getPower() {
			return power;
		}
};

class Robot: public IterativeRobot
{
private:
	LiveWindow *lw;
	Victor *right1;
	Victor *right2;
	Victor *left1;
	Victor *left2;
	PIDOut *output;
	Encoder *enc;
	DistanceProfile *prof;
	PIDController *control1;
	Timer *time;
	Xbox *controller;
	DistanceProfile *prof1;
	DistanceProfileManager *manager;
	std::vector<DistanceProfile*> profs;
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
		right1 = new Victor(3);
		right2 = new Victor(2);
		left1  = new Victor(0);
		left2 = new Victor(1);
		output = new PIDOut();
		enc = new Encoder(0,1);
		control1 = new PIDController(.002, 0, 0, enc, output);
		prof = new DistanceProfile(3000, 0, 5);
		prof1 = new DistanceProfile(0, 1500, 2);
		DistanceProfile profs1(3000,0,5);
		DistanceProfile profs2(0, 1500, 2);
		profs.push_back(prof);
		profs.push_back(prof1);
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

		setPower(control1->Get(), control1->Get());
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
	void setPower(double left, double right) {
		right1->Set(-right);
		right2->Set(-right);
		left1->Set(left);
		left2->Set(left);
	}


};

START_ROBOT_CLASS(Robot);
