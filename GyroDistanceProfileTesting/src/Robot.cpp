#include "WPILib.h"
#include "DistanceProfile.h"
#include "DistanceProfileManager.h"
#include "Xbox.h"
#include <iostream>
#include <vector>
#include "PIDOUT.h"
#include "AutonomousHelper.h"
#include "ADXRS453Z.h"

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

class GyroPIDIN : public PIDSource {

private:
	ADXRS453Z* gyro = new ADXRS453Z();

public:
	GyroPIDIN(ADXRS453Z* gyroSensor) {
		gyro = gyroSensor;
	}
	double PIDGet() {
		/* 1.889*/
		return gyro->getAngle() /* conversion to encoder ticks*/;
	}

};

class Robot: public IterativeRobot
{
private:
	std::vector<DistanceProfile*> nextProfs;
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
	GyroPIDIN* gyroIn;
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
	Timer* time1;
	AnglePIDIN *pin;
	std::vector<DistanceProfile*> profs;
	Joystick* ljoy;
	Joystick* rjoy;
	AutonomousHelper* commandLine;
	ADXRS453Z* gyro;
	bool nextProf = false;
	bool turnIsDone = false;
	bool hasTurned =false;
	bool notEnded = true;
	int count = 0;
	bool last;
	bool firstTurn = false;
	int in = 0;
	int reset = 0;

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
		//angleControl = new PIDController(.020, 0, 0, angSource, angleOut);
		driveControl = new PIDController(.00114, 0, 0, driSource, driveOut);
		//turns = new PIDController(.0100, 0 , 0, pin , turnsOut);
		prof = new DistanceProfile(0, 500, 10);
		prof1 = new DistanceProfile(0, 500, 10);
		DistanceProfile profs1(3000,0,5);
		DistanceProfile profs2(0, 1500, 2);
		profs.push_back(prof);
		//nextProfs.push_back(prof1);
		//profs1.push_back(prof1);
		//profs.push_back(prof1);
		gyro = new ADXRS453Z(0);
		time = new Timer();
		manager = new DistanceProfileManager(profs, lenc, renc, time);
		//manager1 = new DistanceProfileManager(nextProfs, lenc, renc, time);
		//time = new Timer();
		controller = new Xbox(2);
		//		angleControl->Enable();
		//		driveControl->Enable();
		//turns->Enable();
		comp = new Compressor(0);
		comp->SetClosedLoopControl(true);
		std::cout<<"Fs" << std::endl;
		ljoy = new Joystick(0);
		rjoy = new Joystick(1);
		gyroIn = new GyroPIDIN(gyro);
		angleControl = new PIDController(.027, 0, .02920, gyroIn, angleOut);
		turns = new PIDController(.027, .0292, 0, gyroIn, turnsOut);
		commandLine = new AutonomousHelper(driveControl, angleControl, turns, driveOut, angleOut, turnsOut, right1, right2, left1, left2, lenc, renc, gyro);

	}

	void AutonomousInit()
	{
//		commandLine->straightWithGyro(prof);
//		//Wait(10);
//		commandLine->rightWithGyro(180);
//		//Wait(10);
//		commandLine->straightWithGyro(prof1);
//		//prof1->isDone = false;
//		std::cout<<"help" << std::endl;
//		//commandLine->back(prof1);
	}

	void AutonomousPeriodic()
	{
		commandLine->straightWithGyro(prof);
		//Wait(10);
		if(!hasTurned)
			commandLine->rightWithGyro(180);
		//Wait(10);
		commandLine->straightWithGyro(prof1);
		hasTurned = true;
		//prof1->isDone = false;
		//std::cout<<"help" << std::endl;
		//commandLine->back(prof1);
		//prof->isDone = false;
	}
	void TeleopInit()
	{
		time->Start();
		angleControl->Enable();
		driveControl->Enable();
		turns->Enable();
	}

	void TeleopPeriodic()
	{
		//std::cout<< "PI" << std::endl;
		if(last != rjoy->GetRawButton(4))
			count++;
		last = rjoy->GetRawButton(4);
		if(count % 4 == 0) {
			if(!manager->isDone && (reset == 0 || reset == 1)) {
				//std::cout<< " PP 0" << std::endl;
				driveControl->SetSetpoint((float)manager->getSetPoint());
				angleControl->SetSetpoint(0);
				setPower(driveOut->getA() + angleOut->getA(), driveOut->getA() - angleOut->getA());
				in++;
			}
			else if(!turnIsDone) {
				if(!firstTurn) {
					renc->Reset();
					lenc->Reset();
				}
				turns->SetSetpoint(370);
				setPower(turnsOut->getA(), -turnsOut->getA());
				//std::cout<< turns->GetError();
				if(turns->GetError() < 30) {
					turnIsDone = true;
				}
				firstTurn = true;
			}
			else {
				//lenc->Reset();
				//renc->Reset();
				turns->Disable();
				manager->reset();
				//time->Reset();
				reset++;
			}
			if(reset == 2) {
				setPower(0,0);
			}
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
		gyro->reset();
		std::cout<< "pi " << std::endl;
		prof->isDone = false;
		prof1->isDone = false;
		hasTurned = true;
		//mot->Set(0);
	}
	void TestPeriodic()
	{
		angleControl->Enable();
		driveControl->Enable();
		if(controller->getY()) {
			angleControl->SetPID(angleControl->GetP() + .001/7, 0, angleControl->GetD());
		}
		else if(controller->getA()) {
			angleControl->SetPID(angleControl->GetP() - .001/7, 0, angleControl->GetD());
		}
		else if(controller->getX()) {
			driveControl->SetSetpoint(180);
		}
		else if(rjoy->GetRawButton(9)) {
			angleControl->SetPID(angleControl->GetP(), 0, angleControl->GetD() + .001/5);
		}
		else if(rjoy->GetRawButton(8)) {
			angleControl->SetPID(angleControl->GetP(), 0, angleControl->GetD() - .001/5);
		}
		else turns->SetSetpoint(0);
		//else turns->SetSetpoint(0);
		if(in % 60 == 0) {
			std::cout << "p " << angleControl->GetP() << " d:" << angleControl->GetD() <<" error " << angleControl->GetError() << " angle: "<< gyro->getAngle() <<  std::endl;
			//std::cout<<turns->GetP()<< "  Enc: " << renc->Get() << " , " << lenc->Get()<< std::endl;
		}
		double motorpower = 0;
		//angleControl->SetSetpoint(0);
		if(turnsOut->getA() > .5) {
			motorpower = .5;
		}
		else if(turnsOut->getA() < -.5) {
			motorpower = -.5;
		}
		else motorpower = turnsOut->getA();
		setPower(/*driveOut->getA() + angleOut->getA(), driveOut->getA() - angleOut->getA()*/motorpower, -motorpower);
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
