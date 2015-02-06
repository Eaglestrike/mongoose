#include "WPILib.h"
#include "Xbox.h"
#include <iostream>
using namespace std;

class SafeMotor: public PIDOutput {
private:
	float output;
	Victor* victor;
	DigitalInput* button;

public:
	SafeMotor(int victorPort, int digitalInputPort) {
		victor = new Victor(victorPort);
		button = new DigitalInput(digitalInputPort);
	}
	void PIDWrite(float output) {
		if (button->Get() && output < 0) {
			victor->Set(0);
		} else {
			victor->Set(output);
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
	Encoder* lEncoder;
	Encoder* rEncoder;
	SafeMotor* lSafeMotor;
	SafeMotor* rSafeMotor;
	DigitalInput* midButton;
	TalonSRX* talon;

	void RobotInit()
	{
		lw = LiveWindow::GetInstance();
		controller = new Xbox(0);
		lEncoder = new Encoder(0,1);
		rEncoder = new Encoder(2,3);
		lSafeMotor = new SafeMotor(0,4);
		rSafeMotor = new SafeMotor(1,5);
		midButton = new DigitalInput(6);
		talon = new TalonSRX(2);
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
		cout << midButton->Get() << endl;
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

	}

	void TestPeriodic()
	{
		lw->Run();
	}

	void calibrate() {
		while (!rSafeMotor->getButton() || !lSafeMotor->getButton()) {
			if (rSafeMotor->getButton()) {
				rSafeMotor->PIDWrite(0);
			} else {
				rSafeMotor->PIDWrite(-.5);
			}
			if (lSafeMotor->getButton()) {
				lSafeMotor->PIDWrite(0);
			} else {
				lSafeMotor->PIDWrite(-.5);
			}
		}
	}
};

START_ROBOT_CLASS(Robot);
