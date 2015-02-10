#include "WPILib.h"
#include "Xbox.h"
#include <iostream>
using namespace std;


#define TOBY_MODE 1
#define MAX_SAFE_RIGHT 0.7
#define MAX_SAFE_LEFT 0.35


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

#if TOBY_MODE
		if(output < 0)
			output = -pow(-output, 1.0/5.0);
		else
			output = pow(output, 1.0/5.0);
#endif
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

	double Get(){
		return victor->Get();
	}


	void Disable(){
		victor->Disable();
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
	int counter = 0;
	bool pressedB = false;

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
		rightArm = new PIDController(.018/*.1*//*.41*/, 0, .012, rEncoder, rSafeMotor);
		rightArm->SetOutputRange(-MAX_SAFE_RIGHT, MAX_SAFE_RIGHT);
		//rightArm->Enable();
		lEncoder->SetDistancePerPulse(.001);
		rEncoder->SetDistancePerPulse(.001);
		lEncoder->SetReverseDirection(true);
	}

	void DisabledInit() {
		rightArm->Disable();
	}
	void AutonomousInit()
	{
		rightArm->Disable();
		rSafeMotor->Disable();
		lSafeMotor->Disable();
	}

	void AutonomousPeriodic()
	{   if(in % 60 == 0)
		std::cout << "left: " <<lEncoder->PIDGet() << " right: " <<  rEncoder->PIDGet() << " leftButton: " << lSafeMotor->getButton() << " rightButton: " << rSafeMotor->getButton() << " midButton: " << midButton->Get() <<std::endl;;
	in++;
	}

	void TeleopInit()
	{

	}

	void TeleopPeriodic()
	{
		if (midButton->Get()) {
			rSafeMotor->PIDWrite(controller->getRX()*MAX_SAFE_RIGHT);
			lSafeMotor->PIDWrite(-controller->getLX()*MAX_SAFE_LEFT);
			if (controller->getStart()) {
				calibrate();
			}
		} else {
			rSafeMotor->PIDWrite(0);
			lSafeMotor->PIDWrite(0);
		}

		if(in % 60 == 0)
			std::cout<< " Right Pos: "<< rEncoder->PIDGet() << " Left Pos: " << lEncoder->PIDGet() << " Left Pow: " << lSafeMotor->Get() << " Right Pow: " << rSafeMotor->Get() << " on target: " << rightArm->OnTarget() <<endl;
		in++;
	}

	void TestInit() {
		rightArm->Enable();
		rightArm->SetPercentTolerance(.10);
		calibrate();
	}

	void TestPeriodic()
	{
		if(controller->getB() != pressedB) {
			counter++;
		}
		pressedB = controller->getB();

		if(controller->getY()) {
			if(counter % 6 == 0)
				rightArm->SetPID(rightArm->GetP() + .002, rightArm->GetI(), rightArm->GetD());
			else if(counter % 4 == 0)
				rightArm->SetPID(rightArm->GetP(), rightArm->GetI() + .0001, rightArm->GetD());
			else if(counter % 2  == 0)
				rightArm->SetPID(rightArm->GetP(), rightArm->GetI(), rightArm->GetD() + .002);

		}
		else if(controller->getA()) {
			if(counter % 6 == 0)
				rightArm->SetPID(rightArm->GetP() - .002, rightArm->GetI(), rightArm->GetD());
			else if(counter % 4 == 0)
				rightArm->SetPID(rightArm->GetP(), rightArm->GetI() - .0001, rightArm->GetD());
			else if(counter % 2  == 0)
				rightArm->SetPID(rightArm->GetP(), rightArm->GetI(), rightArm->GetD() - .002);
		}
		if(controller->getX()) {
			rightArm->SetSetpoint(4);
		}
		else rightArm->SetSetpoint(8);
		if(in % 12 == 0)
			std::cout << " p: "  << rightArm->GetP() << " i: " << rightArm->GetI() << " d: " << rightArm->GetD() << " error: "  << rightArm->GetError() << " Position: " << rEncoder->PIDGet() << " Setpoint: " << rightArm->GetSetpoint() << " Right power: "  << rSafeMotor->Get() << std::endl;
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
				lSafeMotor->PIDWrite(.3);
			}
		}

		lEncoder->Reset();
		rEncoder->Reset();
	}
};

START_ROBOT_CLASS(Robot);
