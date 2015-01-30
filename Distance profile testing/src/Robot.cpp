#include "WPILib.h"
#include "DistanceProfile.h"
#include "DistanceProfileManager.h"
#include "Xbox.h"
#include <iostream>
#include <vector>
#include <String.h>

class AnglePIDIN : public PIDSource {
private:
	Encoder* enc1;
	Encoder* enc2;
public:
	AnglePIDIN(Encoder *encs1, Encoder *encs2) {
		enc1 = encs1;
		enc2 = encs2;
	}
	double PIDGet() {
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
	PIDController* turns;
	PIDOUT* driveOut;
	PIDOUT* angleOut;
	PIDOUT* turnsOut;
	Timer *time;
	Xbox* controller;
	Compressor* comp;
	DistanceProfile *prof1;
	DistanceProfileManager *manager;
	DistanceProfileManager *manager1;
	AnglePIDIN *pin;
	std::vector<DistanceProfile*> profs;
	std::vector<DistanceProfile*> profs1;
	Joystick* ljoy;
	Joystick* rjoy;
	bool nextProf = false;
	bool notEnded = true;
	int count = 0;
	bool last;
	int in = 0;

	void RobotInit()
	{
		std::cout<< "PI" << std::endl;
		lw = LiveWindow::GetInstance();
		left1 = new Victor(0);
		left2 = new Victor(1);
		right1 = new Victor(3);
		right2 = new Victor(2);
		renc = new Encoder(0,1);
		//renc->SetReverseDirection(true);
		lenc = new Encoder(2,3);
		driSource = new DrivePIDIN(renc, lenc);
		angSource = new AnglePIDIN(renc, lenc);
		pin = new AnglePIDIN(renc, lenc);
		driveOut = new PIDOUT();
		angleOut = new PIDOUT();
		turnsOut = new PIDOUT();
		angleControl = new PIDController(.020, 0, 0, angSource, angleOut);
		driveControl = new PIDController(.00114, 0, 0, driSource, driveOut);
		turns = new PIDController(.003, 0 , 0, pin , turnsOut);
		prof = new DistanceProfile(500, 0, 5);
		prof1 = new DistanceProfile(500, 0, 5);
		DistanceProfile profs1(3000,0,5);
		DistanceProfile profs2(0, 1500, 2);
		profs.push_back(prof);
		//profs1.push_back(prof1);
		//profs.push_back(prof1);

		manager = new DistanceProfileManager(profs, lenc, renc, time);
		time = new Timer();
		controller = new Xbox(2);
		angleControl->Enable();
		driveControl->Enable();
		comp = new Compressor(0);
		comp->SetClosedLoopControl(true);
		std::cout<<"Fs" << std::endl;
		ljoy = new Joystick(0);
		rjoy = new Joystick(1);
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
		if(last != rjoy->GetRawButton(4))
					count++;
		last = rjoy->GetRawButton(4);
		if(count % 4 == 0) {
			if(!manager->isDone) {
				driveControl->SetSetpoint((float)manager->getSetPoint());
				angleControl->SetSetpoint(0);
				setPower(driveOut->getA() + angleOut->getA(), driveOut->getA() - angleOut->getA());
				in++;
			}
			else {
				turns->SetSetpoint(100);

			}
		}
		else if(count % 2 ==0) {
			setPower(ljoy->GetY(), rjoy->GetY());
		}
		if(in % 60 == 0) {
			std::cout << " P:"  << angleControl->GetP() <<  std::endl;
			std::cout << "enc" << renc->Get()  << ", " << lenc->Get() << "Angle: "<< renc->Get() - lenc->Get()  << " Drive: " << renc->Get() + lenc->Get() <<" GE " <<  angleControl->GetError() << " setPoint" << driveControl->GetSetpoint()<< " time: " << time->Get() <<std::endl;
		}
	}
	void DisabledPeriodic() {
		time->Reset();
		time->Stop();
		renc->Reset();
		lenc->Reset();

		//mot->Set(0);
	}
	void TestPeriodic()
	{
		if(controller->getY()) {
			turns->SetPID(turns->GetP() + .001, 0, 0);
		}
		else if(controller->getA()) {
			turns->SetPID(turns->GetP() - .001, 0, 0);
		}
		else if(controller->getX()) {
			turns->SetSetpoint(500);
		}
		else turns->SetSetpoint(0);
		if(in % 60 == 0) {
			std::cout<<turns->GetP()<< "  Enc: " << renc->Get() << " , " << lenc->Get()<< std::endl;
		}

		//angleControl->SetSetpoint(0);

		setPower(/*driveOut->getA() + angleOut->getA(), driveOut->getA() - angleOut->getA()*/turnsOut->getA(), -turnsOut->getA());
		//std::cout << "GIT" << std::endl;
		lw->Run();
		in++;
	}
	void setPower(double left, double right) {
		right1->Set(-right);
		right2->Set(-right);
		left1->Set(left);
		left2->Set(left);
	}

};

START_ROBOT_CLASS(Robot);
