#include "WPILib.h"
#include <iostream>

class ElevatorMotor: public PIDOutput {
private:
	TalonSRX* talon1;
	TalonSRX* talon2;
	DigitalInput* button;

public:
	ElevatorMotor(int talon1Port, int talon2Port, int buttonPort) {
		talon1 = new TalonSRX(talon1Port);
		talon2 = new TalonSRX(talon2Port);
		button = new DigitalInput(buttonPort);
	}

	void PIDWrite(float output) {
		if ((button->Get() && output < 0)) {
			talon1->Set(0);
			talon2->Set(0);
		} else {
			talon1->Set(output);
			talon2->Set(output);
		}
	}

	bool getButton() {
		return button->Get();
	}

	double Get() {
		return talon1->Get();
	}

	void Disable() {
		talon1->Disable();
		talon2->Disable();
	}
};

class Robot: public IterativeRobot
{
private:
	LiveWindow *lw;

	void RobotInit()
	{
		lw = LiveWindow::GetInstance();
	}

	void AutonomousInit()
	{

	}

	void AutonomousPeriodic()
	{

	}

	void TeleopInit()
	{

	}

	void TeleopPeriodic()
	{

	}

	void TestPeriodic()
	{
		lw->Run();
	}
};

START_ROBOT_CLASS(Robot);
