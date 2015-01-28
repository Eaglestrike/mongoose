#include "WPILib.h"
#include "DistanceProfile.h"
#include "Xbox.h"
#include <iostream>
#include <vector>

class AnglePIDIN : public PIDSource {
private:
	Encoder* enc1;
	Encoder* enc2;
public:
	AnglePIDIN(Encoder *encs1, Encoder *encs2) {
		enc1 = encs1;
		enc2 = encs2;
	}
	float PIDGet() {
		return enc1->Get() - enc2->Get();
	}
};

class DrivePIDIN : public PIDSource {
private:
	Encoder* enc1;
	Encoder* enc2;
public:
	DrivePIDIN(Encoder* encs1, Encoder* encs2) {
		enc1 = encs1;
		enc2 = encs2;
	}

	double PIDGet() {
		return (enc1->Get() + enc2->Get())/2;
	}

};

class PIDOUT : public PIDOutput {
private:
	double a = 0;
public:
	PIDOUT() {}

	void PIDWrite(float output) {
		a = output;
	}

	double getA() {
		return a;
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
	Encoder *renc;
	Encoder *lenc;
	AnglePIDIN* angSource;
	DrivePIDIN* driSource;
	DistanceProfile *prof;
	PIDController *angleControl;
	PIDController* driveControl;
	PIDOUT* driveOut;
	PIDOUT* angleOut;
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
		left1 = new Victor(0);
		left2 = new Victor(3);
		right1 = new Victor(1);
		right2 = new Victor(2);
		renc = new Encoder(0,1);
		lenc = new Encoder(2,3);
		driSource = new DrivePIDIN(renc, lenc);
		angSource = new AnglePIDIN(renc, lenc);
		driveOut = new PIDOUT();
		angleOut = new PIDOUT();
		angleControl = new PIDController(.002, 0, 0, angSource, angleOut);
		driveControl = new PIDController(0, 0, 0, driSource, driveOut);
		prof = new DistanceProfile(3000, 0, 5);
		prof1 = new DistanceProfile(0, 1500, 2);
		DistanceProfile profs1(3000,0,5);
		DistanceProfile profs2(0, 1500, 2);
		profs.push_back(profs1);
		profs.push_back(profs2);
		manager = new DistanceProfileManager(profs);
		time = new Timer();
		controller = new Xbox(0);
		angleControl->Enable();
		driveControl->Enable();
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
		angleControl->Enable();
		driveControl->Enable();

	}

	void TeleopPeriodic()
	{
		if(!manager->isDone)
			driveControl->SetSetpoint((float)manager->getSetPoint(*time, *renc, *lenc));
//		if(!prof->isDone)
//			control1->SetSetpoint(prof->getSetPoint(time->Get()));
//		if(time->Get() >= 6 && prof->isDone && !prof1->isDone) {
//			time->Reset();
//			enc->Reset();
//		}
//		if(prof->isDone && !prof1->isDone && time->Get() < 5) {
//			control1->SetSetpoint(prof1->getSetPoint(time->Get()));
//		}
		setPower(driveOut->getA() + angleOut->getA(), driveOut->getA() - angleOut->getA());
		in++;
		if(in % 60 == 0) {
			std::cout << " P:"  << angleControl->GetP() << " I:" << i << " D:" << d << std::endl;
			std::cout << "enc" << renc->Get() << " GE " <<  angleControl->GetError() << " setPoint" << control1->GetSetpoint()<< " time: " << time->Get() <<std::endl;
		}
	}
	void DisabledPeriodic() {
		time->Reset();
		time->Stop();
		renc->Reset();
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
