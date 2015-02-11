#include "WPILib.h"
#include "Xbox.h"
#include <iostream>
#include <math.h>
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
	bool withinErrorRange = false;
	bool right;

public:
	SafeMotor(int victorPort, int digitalInputPort, DigitalInput* mB /* middle button*/, bool isRight): right(isRight) {
		victor = new Victor(victorPort);
		button = new DigitalInput(digitalInputPort);
		middleButton = mB;
	}

	void PIDWrite(float output) {
		if(right)
			output*=-1;

		if(middleButton->Get() && !emergencyStop){
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
		if ((button->Get() && output < 0) || withinErrorRange) {
			victor->Set(0);
		} else {
			victor->Set(output);
			//std::cout << victor->Get() << std::endl;
		}
	}

	bool getButton() {
		return button->Get();
	}
	void setWithinErrorRange(bool istrue) {
		withinErrorRange = istrue;
	}

	double Get(){
		return victor->Get();
	}


	void Disable(){
		victor->Disable();
	}
};

class ArmDifference: public PIDSource {
private:
	ModifiedEncoder* right;
	ModifiedEncoder* left;

public:
	ArmDifference(ModifiedEncoder* rE, ModifiedEncoder* le) {
		right = rE;
		left = le;
	}
	double PIDGet() {
		return right->PIDGet() - left->PIDGet();
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
	ArmDifference* armDiff;
	PIDController* diffController;
	int in = 0;
	int counter = 0;
	bool pressedB = false;

	void RobotInit()
	{
		lw = LiveWindow::GetInstance();
		controller = new Xbox(0);
		lEncoder = new ModifiedEncoder(0,1,0);
		rEncoder = new ModifiedEncoder(2,3, 14 /*no*/);
		midButton = new DigitalInput(6);
		lSafeMotor = new SafeMotor(0,4,midButton, false);
		rSafeMotor = new SafeMotor(1,5,midButton, true);
		talon = new TalonSRX(2);
		armDiff = new ArmDifference(rEncoder, lEncoder);
		diffController = new PIDController(0.022,0,0,armDiff, rSafeMotor);
		rightArm = new PIDController(.029/*.018*/, 0 , .026 /* .012*/, rEncoder, rSafeMotor);
		leftArm = new PIDController(.03257, 0, 0, lEncoder, lSafeMotor);
		leftArm->SetOutputRange(-MAX_SAFE_LEFT, MAX_SAFE_LEFT);
		rightArm->SetOutputRange(-MAX_SAFE_RIGHT, MAX_SAFE_RIGHT);
		//rightArm->Enable();
		lEncoder->SetDistancePerPulse(.001);
		rEncoder->SetDistancePerPulse(.001);
		lEncoder->SetReverseDirection(true);
	}

	void DisabledInit() {
		rightArm->Disable();
		leftArm->Disable();
		diffController->Disable();
		diffController->Reset();
		leftArm->Reset();
		rightArm->Reset();
		rSafeMotor->setWithinErrorRange(false);
		lSafeMotor->setWithinErrorRange(false);
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
		if (!midButton->Get()) {
			rSafeMotor->PIDWrite(controller->getRX()*MAX_SAFE_RIGHT);
			lSafeMotor->PIDWrite(controller->getLX()*MAX_SAFE_LEFT);
			if (controller->getA()) {
				cout << "pressed Start" << endl;
				calibrate();
				cout << "after calibrate" << endl;
			}
		} else {
			rSafeMotor->PIDWrite(0);
			lSafeMotor->PIDWrite(0);
		}

		if(in % 60 == 0)
			std::cout<< " Right Pos: "<< rEncoder->PIDGet() << " Left Pos: " << lEncoder->PIDGet() << " Left Pow: " << lSafeMotor->Get() << " Right Pow: " << rSafeMotor->Get() << " on target: " << rightArm->OnTarget() << " lsp: " << leftArm->GetSetpoint() << endl;
		in++;
	}

	void TestInit() {
		//rightArm->SetPercentTolerance(.10);
		calibrate();
		leftArm->Enable();
		diffController->Enable();
		leftArm->SetSetpoint(1);
	}

	double deltaX = 5;

	void TestPeriodic()
	{

		if(controller->getX()){
			if(leftArm->GetSetpoint() + 8 > 14)
				leftArm->SetSetpoint(14 - 8);
			diffController->SetSetpoint(8);
		}else{
			if(leftArm->GetSetpoint() + 5 > 14)
				leftArm->SetSetpoint(14 - 5);
			diffController->SetSetpoint(5);
		}


		if(controller->getY())
			diffController->SetPID(diffController->GetP() + 0.0001, diffController->GetI(), diffController->GetD());
		else if(controller->getA() && diffController->GetP() > 0.0001)
			diffController->SetPID(diffController->GetP() - 0.0001, diffController->GetI(), diffController->GetD());

		double setpoint = leftArm->GetSetpoint()+controller->getLX()/5.0;

		if(setpoint + deltaX > 14)
			setpoint = 14 - deltaX;
		else if(setpoint < 0)
			setpoint = 0;

		leftArm->SetSetpoint(setpoint);


//		if(controller->getB() != pressedB) {
//			counter++;
//		}
//		pressedB = controller->getB();
//		if(controller->getY()) {
//			if(counter % 6 == 0)
//				leftArm->SetPID(leftArm->GetP() + .002/7, leftArm->GetI(), leftArm->GetD());
//			else if(counter % 4 == 0)
//				leftArm->SetPID(leftArm->GetP(), leftArm->GetI() + .0001, leftArm->GetD());
//			else if(counter % 2  == 0)
//				leftArm->SetPID(leftArm->GetP(), leftArm->GetI(), leftArm->GetD() + .002);
//
//		}
//		else if(controller->getA()) {
//			if(counter % 6 == 0)
//				leftArm->SetPID(leftArm->GetP() - .002/7, leftArm->GetI(), leftArm->GetD());
//			else if(counter % 4 == 0)
//				leftArm->SetPID(leftArm->GetP(), leftArm->GetI() - .0001, leftArm->GetD());
//			else if(counter % 2  == 0)
//				leftArm->SetPID(leftArm->GetP(), leftArm->GetI(), leftArm->GetD() - .002);
//		}
//		if(controller->getX()) {
//			leftArm->SetSetpoint(8);
//		}
//		else leftArm->SetSetpoint(4);
//
		if(abs(leftArm->GetError()) < 0.05) {
			lSafeMotor->setWithinErrorRange(true);
		}
		else lSafeMotor->setWithinErrorRange(false);

		if(abs(diffController->GetError()) < 0.05){
			rSafeMotor->setWithinErrorRange(true);
		}else{
			rSafeMotor->setWithinErrorRange(false);
		}

		if(in % 12 == 0)
			cout << "p: " << diffController->GetP() << " deltaX: " << deltaX <<  " error: " << diffController->GetError() << " leftPos: "  << lEncoder->PIDGet() << " rightPos: " << rEncoder->PIDGet() << " diffPos: " << diffController->Get() << " lsp: " << leftArm->GetSetpoint() << " rsp: " << rightArm->GetSetpoint() << " dsp: " << diffController->GetSetpoint() <<endl;
//			std::cout << " p: "  << leftArm->GetP() << " i: " << leftArm->GetI() << " d: " << leftArm->GetD() << " error: "  << leftArm->GetError() << " Position: " << lEncoder->PIDGet() << " Setpoint: " << leftArm->GetSetpoint() << " Left power: "  << lSafeMotor->Get() << " Right power: " << rSafeMotor->Get() << " leftButton"<<  lSafeMotor->getButton()<< std::endl;
		in++;
		lw->Run();
		Wait(0.05);
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
				lSafeMotor->PIDWrite(-.3);
			}
		}

		lEncoder->Reset();
		rEncoder->Reset();
	}
};

START_ROBOT_CLASS(Robot);
