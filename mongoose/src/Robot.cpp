
#include <iostream>

#include "WPIlib.h"
#include "Modules/Modules.h"
#include "Settings.h"
#include "Xbox.h"

using namespace std;

class Robot: public IterativeRobot
{
private:
	LiveWindow *lw;
	ElevatorModule* elevatorModule;
	DriveModule* driveModule;
	ArmModule* armModule;
	ScorpionModule* scorpionModule;
	Timer* timer;

	Joystick* leftJoy;
	Joystick* rightJoy;
	Xbox* xbox;

	unsigned long printCounter = 0;

	void RobotInit()
	{
		cout << "RobotInit()" << endl;
		lw = LiveWindow::GetInstance();
		cout << "ElevatorModule()" << endl;
		elevatorModule = new ElevatorModule(ELEVATOR_1, ELEVATOR_2, ELEVATOR_SAFTEY_BUTTON, ELEVATOR_ENCODER_A, ELEVATOR_ENCODER_B);
		cout << "DriveModule()" << endl;
		driveModule = new DriveModule(DRIVE_LEFT_1, DRIVE_LEFT_2, DRIVE_RIGHT_1, DRIVE_RIGHT_2, DRIVE_ENCODER_A, DRIVE_ENCODER_B, DRIVE_GYRO);
		cout << "ArmModule()" << endl;
		armModule = new ArmModule(RIGHT_ARM_MOTOR, LEFT_ARM_MOTOR, RIGHT_ARM_BUTTON, MID_ARM_BUTTON, LEFT_ARM_BUTTON, RIGHT_ARM_ENCODER_A, RIGHT_ARM_ENCODER_B, LEFT_ARM_ENCODER_A, LEFT_ARM_ENCODER_B);
		cout << "ScorpionModule()" << endl;
		scorpionModule = new ScorpionModule(SCORPION_PORT);

		cout << "Timer()" << endl;
		timer = new Timer();

		timer->Start();

		cout << "Joystick()" << endl;
		leftJoy = new Joystick(0);
		rightJoy = new Joystick(1);
		xbox = new Xbox(2);

		cout << "RobotInit() end" << endl;

	}

	void DisabledInit(){
		elevatorModule->disable();
		driveModule->disable();
		armModule->disable();

		elevatorModule->reset();
		driveModule->reset();
		armModule->reset();

		printCounter = 0;
	}

	void AutonomousInit()
	{

	}

	void AutonomousPeriodic()
	{
		if(printCounter % 50 == 0){
			cout 	<< "T: " << timer->Get() << " EB: " << elevatorModule->getButton() << " ALB: " << armModule->getLeftButton() << " AMB: " << armModule->getMidButton() << " ARB: " << armModule->getRightButton()
					<<	" RE: " << armModule->getRightPosition() << " LE: " << armModule->getLeftPosition() << endl;
		}

		printCounter++;

		Wait(0.01);
	}

	void TeleopInit()
	{
		elevatorModule->disable();
		driveModule->disable();
		armModule->enable();
	}


	void TeleopPeriodic()
	{


		driveModule->drive(-leftJoy->GetY(), -rightJoy->GetX());
		scorpionModule->Set(rightJoy->GetRawButton(4));

		double leftArmPower = xbox->getLX() * MAX_ARM_POWER;
		double rightArmPower = xbox->getRX() * MAX_ARM_POWER;

		if(armModule->getLeftButton() && leftArmPower < 0)
			leftArmPower = 0;

		if(armModule->getRightButton() && rightArmPower > 0)
			rightArmPower = 0;

		if(armModule->getMidButton()){
			if(leftArmPower > 0)
				leftArmPower = 0;
			if(rightArmPower < 0)
				rightArmPower = 0;
		}

		armModule->setLeftPower(leftArmPower);
		armModule->setRightPower(rightArmPower);

		double elevatorPower = xbox->getLY() * MAX_ELEVATOR_UP;
		if(elevatorPower < MAX_ELEVATOR_DOWN)
			elevatorPower = MAX_ELEVATOR_DOWN;

		if(elevatorModule->getButton() && elevatorPower < 0)
			elevatorPower = 0;

		elevatorModule->setPower(elevatorPower);

		if(printCounter % 50 == 0){
			cout << "time: " << timer->Get() << " LD: " << driveModule->getLeftPower() << " RD: " << driveModule->getRightPower() << " LA: " << armModule->getLeftPower() << " RA: " << armModule->getRightPower() << " E: " << elevatorModule->Get() << " xboxLX :" << xbox->getLX() << " xboxRX: " << xbox->getRX() << endl;
		}

		printCounter++;
		Wait(0.01);
	}

	void TestInit(){
		armModule->enable();
		armModule->disablePID();
		armModule->calibrate();
		armModule->enablePID();
	}

	void TestPeriodic()
	{


		if(xbox->getStart()){
			//armModule->setDeltaX(5);
			armModule->setLeftArm(4);
		}else{
			armModule->setDeltaX(13);
			armModule->setLeftArm(0.5);
		}

		if(printCounter % 12 == 0){
			cout << "lb: " << armModule->getLeftButton() << " mb: " << armModule->getMidButton() << " rb: " << armModule->getRightButton()  << " ds: " << armModule->getDiffSetpoint() << " rs: " << armModule->getRightSetpoint() << " de: " << armModule->getDiffError() << " re: " << armModule->getRightError() << endl;
		}

		printCounter++;
		lw->Run();
	}
};

START_ROBOT_CLASS(Robot);
