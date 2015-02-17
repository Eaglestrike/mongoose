#include "WPILib.h"
#include "Xbox.h"
#include <iostream>
#include <math.h>
using namespace std;


#define TOBY_MODE 0
#define MAX_SAFE_RIGHT 1
#define MAX_SAFE_LEFT 1


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

class ArmOut : public PIDOutput {
private:
	double power;

public:
	ArmOut() {}
	void PIDWrite(float output) {
		power = output;
	}

	double getPower() {
		return power;
	}
};


class Robot: public IterativeRobot
{
private:
	LiveWindow *lw;
	Xbox* controller;
	Xbox* controller2;
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
	ArmOut* outPut;
	ArmOut* rightOut;
	ArmOut* leftOut;
	PIDController* diffController;
	Timer* timeOfController;
	int in = 0;
	float prevError = 0;
	int counter = 0;
	bool pressedB = false;

	void RobotInit()
	{
		lw = LiveWindow::GetInstance();
		controller = new Xbox(0);
		controller2 = new Xbox(1);
		lEncoder = new ModifiedEncoder(4,5,0);
		rEncoder = new ModifiedEncoder(6,7, 14 /*no*/);
		midButton = new DigitalInput(1);
		lSafeMotor = new SafeMotor(6,0,midButton, false);
		rSafeMotor = new SafeMotor(7,2,midButton, true);
		talon = new TalonSRX(2);
		armDiff = new ArmDifference(rEncoder, lEncoder);
		outPut = new ArmOut();
		rightOut = new ArmOut();
		leftOut = new ArmOut();
		diffController = new PIDController(0, 0, 0, armDiff, outPut);
		//diffController = new PIDController(0.02,0,0,armDiff, rSafeMotor);
		rightArm = new PIDController( 0.276498 , 0.0012 , 0.0262,/* Arm 1 -> .298/2, 0.0023 , .072,*/ rEncoder, rightOut);
		leftArm = new PIDController(.387998, 0.0012, 0.23875, /*Arm 1 -> 0.554/2 , .0016, .218, */lEncoder, leftOut);
		leftArm->SetOutputRange(-MAX_SAFE_LEFT, MAX_SAFE_LEFT);
		rightArm->SetOutputRange(-MAX_SAFE_RIGHT, MAX_SAFE_RIGHT);
		timeOfController = new Timer();
		//rightArm->Enable();
		lEncoder->SetDistancePerPulse(.001);
		rEncoder->SetDistancePerPulse(.001);
		rEncoder->SetReverseDirection(true);
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
	{   if(in % 3 == 0)
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

		if(in % 12 == 0)
			std::cout<< " Right Pos: "<< rEncoder->PIDGet() << " Left Pos: " << lEncoder->PIDGet() << " Left Pow: " << lSafeMotor->Get() << " Right Pow: " << rSafeMotor->Get() << " on target: " << rightArm->OnTarget() << " lsp: " << leftArm->GetSetpoint() << endl;
		in++;
	}

	void TestInit() {
		//rightArm->SetPercentTolerance(.10);
		calibrate();
		rightArm->Enable();
		leftArm->Enable();
		diffController->Enable();
		//leftArm->SetSetpoint(1);
	}

	double deltaX = 5.25;

	void TestPeriodic1(){
		if(controller->getB() != pressedB) {
			counter++;
		}
		pressedB = controller->getB();

		if(controller->getX()){
			deltaX = 10;
		}else{
			deltaX = 5.25;
		}



		if(controller->getY())
			diffController->SetPID(diffController->GetP() + .001, diffController->GetI(), diffController->GetD());
		else if(controller->getB())
			diffController->SetPID(diffController->GetP(), diffController->GetI() + .0001, diffController->GetD());
		else if(controller->getStart())
			diffController->SetPID(diffController->GetP(), diffController->GetI(), diffController->GetD() + .002);
		else if(controller->getA())
			diffController->SetPID(diffController->GetP() - .001, diffController->GetI(), diffController->GetD());
		else if(controller->getLB())
			diffController->SetPID(diffController->GetP(), diffController->GetI() - .0001, diffController->GetD());
		else if(controller->getBack())
			diffController->SetPID(diffController->GetP(), diffController->GetI(), diffController->GetD() - .002);

		double setpoint = leftArm->GetSetpoint()+controller->getLX()/5.0;
		if(controller->getL3()) {
			setpoint = 4;
		}
		else if(controller->getR3()) {
			setpoint = 8;
		}

		if(controller2->getX()) {
			diffController->Disable();
		}
		else if(controller2->GetY()) {
			diffController->Enable();
		}
		else setpoint = leftArm->GetSetpoint()+controller->getLX()/5.0;

		if(setpoint + deltaX > 14)
			setpoint = 14 - deltaX;
		else if(setpoint < 0)
			setpoint = 0;

		leftArm->SetSetpoint(setpoint);
		rightArm->SetSetpoint(setpoint+deltaX);
		diffController->SetSetpoint(deltaX);
		if(abs(leftArm->GetError()) < 0.1) {
			lSafeMotor->setWithinErrorRange(true);
		}else{
			lSafeMotor->setWithinErrorRange(false);
		}

		if(abs(diffController->GetError()) < 0.1){
			rSafeMotor->setWithinErrorRange(true);
		}else{
			rSafeMotor->setWithinErrorRange(false);
		}
		rSafeMotor->PIDWrite(rightOut->getPower() + outPut->getPower());
		lSafeMotor->PIDWrite(leftOut->getPower() + outPut->getPower());
		if(in % 3 == 0)
			cout << "p: " << diffController->GetP() << " i: " <<  diffController->GetI() << " d:" << diffController->GetD() << " deltaX: " << deltaX <<  " error: " << diffController->GetError() << " leftPos: "  << lEncoder->PIDGet() << " rightPos: " << rEncoder->PIDGet() << " diffPos: " << diffController->Get() << " lsp: " << leftArm->GetSetpoint() << " rsp: " << rightArm->GetSetpoint() << " dsp: " << diffController->GetSetpoint() << " left p: " << leftArm->GetP() << " left i:" << leftArm->GetI()<< " left d:" << leftArm->GetD() << " right p: " << rightArm->GetP() << " right i:" << rightArm->GetI() << " rightD: " << rightArm->GetD() <<endl;
		//			std::cout << " p: "  << leftArm->GetP() << " i: " << leftArm->GetI() << " d: " << leftArm->GetD() << " error: "  << leftArm->GetError() << " Position: " << lEncoder->PIDGet() << " Setpoint: " << leftArm->GetSetpoint() << " Left power: "  << lSafeMotor->Get() << " Right power: " << rSafeMotor->Get() << " leftButton"<<  lSafeMotor->getButton()<< std::endl;
		in++;

	}

	void TestPeriodic2() {
		if(controller->getB() != pressedB) {
			counter++;
		}
		pressedB = controller->getB();
		if(controller->getY())
			leftArm->SetPID(leftArm->GetP() + .001/10, leftArm->GetI(), leftArm->GetD());
		else if(controller->getB())
			leftArm->SetPID(leftArm->GetP(), leftArm->GetI() + .0001, leftArm->GetD());
		else if(controller->getStart())
			leftArm->SetPID(leftArm->GetP(), leftArm->GetI(), leftArm->GetD() + .002);
		else if(controller->getA())
			leftArm->SetPID(leftArm->GetP() - .001/10, leftArm->GetI(), leftArm->GetD());
		else if(controller->getLB())
			leftArm->SetPID(leftArm->GetP(), leftArm->GetI() - .0001, leftArm->GetD());
		else if(controller->getBack())
			leftArm->SetPID(leftArm->GetP(), leftArm->GetI(), leftArm->GetD() - .002);

		//		if(leftArm->GetError() >= prevError - .05 && leftArm->GetError() <= prevError + .05 ) {
		//			timeOfController->Start();
		//		}
		//		else {
		//			timeOfController->Stop();
		//			timeOfController->Reset();
		//		}
		//
		//		if(timeOfController->Get() > .5) leftArm->Disable();

		if(controller->getX()) {
			leftArm->SetSetpoint(6);
		}
		else leftArm->SetSetpoint(2);
		if(controller->getL3()) {
			leftArm->Disable();
		}
		else if(controller->getR3()) leftArm->Enable();
		if(abs(leftArm->GetError()) < 0.1){
			lSafeMotor->setWithinErrorRange(true);
		}else{
			lSafeMotor->setWithinErrorRange(false);
		}

		lSafeMotor->PIDWrite(leftOut->getPower());
		if(in % 6 == 0)
			std::cout << " p: "  << leftArm->GetP() << " i: " << leftArm->GetI() << " d: " << leftArm->GetD() << " error: "  << leftArm->GetError() << " Position: " << lEncoder->PIDGet() << " Setpoint: " << leftArm->GetSetpoint() << " Left power: "  << lSafeMotor->Get() << " Right power: " << rSafeMotor->Get() << " leftButton"<<  lSafeMotor->getButton()<< std::endl;
		in++;
	}

	void TestPeriodic3() {
		if(controller->getB() != pressedB) {
			counter++;
		}
		pressedB = controller->getB();
		if(controller->getY())
			rightArm->SetPID(rightArm->GetP() + .001/10, rightArm->GetI(), rightArm->GetD());
		else if(controller->getB())
			rightArm->SetPID(rightArm->GetP(), rightArm->GetI() + .0001/10, rightArm->GetD());
		else if(controller->getStart())
			rightArm->SetPID(rightArm->GetP(), rightArm->GetI(), rightArm->GetD() + .002/10);
		else if(controller->getA())
			rightArm->SetPID(rightArm->GetP() - .001/10, rightArm->GetI(), rightArm->GetD());
		else if(controller->getLB())
			rightArm->SetPID(rightArm->GetP(), rightArm->GetI() - .0001/10, rightArm->GetD());
		else if(controller->getBack())
			rightArm->SetPID(rightArm->GetP(), rightArm->GetI(), rightArm->GetD() - .002/10);

		if(controller->getX()) {
			rightArm->SetSetpoint(10);
		}
		else rightArm->SetSetpoint(6);

		if(controller->getL3()) {
			rightArm->Disable();
		}
		else if(controller->getR3()) rightArm->Enable();
		if(abs(rightArm->GetError()) < 0.1){
			rSafeMotor->setWithinErrorRange(true);
		}else{
			rSafeMotor->setWithinErrorRange(false);
		}
		rSafeMotor->PIDWrite(rightOut->getPower());
		if(in % 12 == 0) {
			std::cout << " p: "  << rightArm->GetP() << " i: " << rightArm->GetI() << " d: " << rightArm->GetD() << " error: "  << rightArm->GetError() << " Position: " << rEncoder->PIDGet() << " Setpoint: " << rightArm->GetSetpoint() << " Left power: "  << lSafeMotor->Get() << " Right power: " << rSafeMotor->Get() << " rightButton"<<  rSafeMotor->getButton()<< std::endl;
		}
	}

	void TestPeriodic()
	{

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

		TestPeriodic1();
		lw->Run();
		Wait(0.05);
	}

	void calibrate() {

		while (!rSafeMotor->getButton() || !lSafeMotor->getButton()) {
			if (rSafeMotor->getButton()) {
				rSafeMotor->PIDWrite(0);
				rEncoder->Reset();
			} else {
				rSafeMotor->PIDWrite(.75);
			}
			if (lSafeMotor->getButton()) {
				lSafeMotor->PIDWrite(0);
				lEncoder->Reset();
			} else {
				lSafeMotor->PIDWrite(-.75);
			}
			Wait(0.05);
		}

		lEncoder->Reset();
		rEncoder->Reset();
	}
};

START_ROBOT_CLASS(Robot);
