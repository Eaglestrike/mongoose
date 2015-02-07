#include "WPILib.h"
#include "Xbox.h"
#include <iostream>
using namespace std;

class ArmEncoder: public PIDSource {
private:
	double addedDistancetoEncoder;
	Encoder* armEncoder;

public:
	ArmEncoder(double addedDistanceToEncoder, Encoder* aEnc) {
		ArmEncoder::addedDistancetoEncoder = addedDistanceToEncoder;
		armEncoder = aEnc;
	}

	double PIDGet() {
		return armEncoder->Get() + addedDistancetoEncoder;
	}

};

class ModifiedEncoder : public Encoder {
private:
	double addedDistance;
public:
	ModifiedEncoder(int portA, int portB, double addedDis) : Encoder(portA, portB){
		addedDistance = addedDis;
	}

	double PIDGet() {
		return Encoder::PIDGet() + addedDistance;
	}
};

class SafeMotor: public PIDOutput {
private:
	float output;
	Victor* victor;
	DigitalInput* button;
	DigitalInput* middleButton;
	bool emergencyStop = false;

public:
	SafeMotor(int victorPort, int digitalInputPort, DigitalInput* mB /* middle button*/) {
		victor = new Victor(victorPort);
		button = new DigitalInput(digitalInputPort);
		middleButton = mB;
	}

	void PIDWrite(float output) {

		output*=-1;

		if(!middleButton->Get() && !emergencyStop){
			emergencyStop = true;
			cerr << "****************MIDDLE BUTTON PRESSED! DISABLING!******************" << endl;
		}

		if(emergencyStop){
			victor->Set(0);
			return;
		}

		if ((button->Get() && output < 0)) {
			victor->Set(0);
		} else {
			victor->Set(output);
			//std::cout << victor->Get() << std::endl;
		}
	}

	bool getButton() {
		return button->Get();
	}
};

class Robot: public IterativeRobot
{
private:
	LiveWindow *lw;
	Xbox* controller;
	ModifiedEncoder* lEncoder;
	ModifiedEncoder* rEncoder;
	SafeMotor* lSafeMotor;
	SafeMotor* rSafeMotor;
	DigitalInput* midButton;
	TalonSRX* talon;
	ArmEncoder* armSource;
	PIDController* rightArm;
	PIDController* leftArm;
	int in = 0;

	void RobotInit()
	{
		lw = LiveWindow::GetInstance();
		controller = new Xbox(0);
		lEncoder = new ModifiedEncoder(0,1,0);
		rEncoder = new ModifiedEncoder(2,3, 13 /*change Later*/);
		midButton = new DigitalInput(6);
		lSafeMotor = new SafeMotor(0,4,midButton);
		rSafeMotor = new SafeMotor(1,5,midButton);
		talon = new TalonSRX(2);
		rightArm = new PIDController(0, 0, 0, rEncoder, rSafeMotor);
		rightArm->Enable();
		lEncoder->SetDistancePerPulse(.001);
		rEncoder->SetDistancePerPulse(.001);
		lEncoder->SetReverseDirection(true);

	}

	void AutonomousInit()
	{

	}

	void AutonomousPeriodic()
	{
		cout << "auto Period()" << endl;
		for(double d = -1; d < 1; d += 0.01){
			talon->Set(d);
			Wait(0.05);
		}

		for(double d = 1; d > -1; d -= 0.01){
			talon->Set(d);
			Wait(0.05);
		}
	}

	void TeleopInit()
	{

	}

	void TeleopPeriodic()
	{
		if (midButton->Get()) {
			rSafeMotor->PIDWrite(-controller->getRX());
			lSafeMotor->PIDWrite(controller->getLX());
			if (controller->getStart()) {
				calibrate();
			}
		} else {
			rSafeMotor->PIDWrite(0);
			lSafeMotor->PIDWrite(0);
		}

		if(in % 60 == 0)
			std::cout<< " Right: "<< rEncoder->PIDGet() << " Left: " << lEncoder->PIDGet() << endl;
		in++;
	}

	void TestInit() {
		rightArm->Enable();
		calibrate();
	}

	void TestPeriodic()
	{
		if(controller->getY()) {
			rightArm->SetPID(rightArm->GetP() + .002, 0, 0);
		}
		else if(controller->getA()) {
			rightArm->SetPID(rightArm->GetP() - .002, 0, 0);
		}
		if(controller->getX()) {
			rightArm->SetSetpoint(4);
		}
		else rightArm->SetSetpoint(8);
		if(in % 60 == 0)
			std::cout << " p: "  << rightArm->GetP() << " error: "  << rightArm->GetError() << " Position: " << rEncoder->PIDGet()<< std::endl;
		in++;
		lw->Run();
	}

	void calibrate() {

		while (!rSafeMotor->getButton() || !lSafeMotor->getButton()) {
			if (rSafeMotor->getButton()) {
				rSafeMotor->PIDWrite(0);
				rEncoder->Reset();
			} else {
				rSafeMotor->PIDWrite(.5);
			}
			if (lSafeMotor->getButton()) {
				lSafeMotor->PIDWrite(0);
				lEncoder->Reset();
			} else {
				lSafeMotor->PIDWrite(.5);
			}
		}

		lEncoder->Reset();
		rEncoder->Reset();
	}
};

START_ROBOT_CLASS(Robot);
