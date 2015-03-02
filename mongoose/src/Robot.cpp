
#include <iostream>


#include "Error/EaglestrikeError.h"
#include "Modules/RobotModule.h"

#include "WPIlib.h"
#include "Modules.h"
#include "Error/CalibrationError.h"
#include "Settings.h"
#include "Xbox.h"
#include "Peripherals/AutonomousCode/AutonomousCommandBase.h"
#include "Peripherals/AutonomousCode/DistanceProfile.h"

using namespace std;

class Robot: public IterativeRobot
{
private:
	LiveWindow *lw;
	ElevatorModule* elevatorModule;
	DriveModule* driveModule;
	ArmModule* armModule;
	ScorpionModule* scorpionModule;
	IntakeModule* intakeModule;
	Timer* timer;

	Joystick* leftJoy;
	Joystick* rightJoy;
	AutonomousCommandBase* autonomousDriver;
	Xbox* xbox;
	int toggleY = 0;
	bool previous;
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
		intakeModule = new IntakeModule(INTAKE_SOLENOID_1, INTAKE_SOLENOID_2, INTAKE_MOTOR_1, INTAKE_MOTOR_2);

		cout << "Timer()" << endl;
		timer = new Timer();

		timer->Start();

		cout << "Joystick()" << endl;
		leftJoy = new Joystick(0);
		rightJoy = new Joystick(1);
		xbox = new Xbox(2);

		autonomousDriver = new AutonomousCommandBase(driveModule);
		cout << "RobotInit() end" << endl;

	}

	void DisabledInit(){
		elevatorModule->disable();
		driveModule->disable();
		armModule->disable();

		elevatorModule->reset();
		driveModule->reset();
		armModule->reset();

		timer->Reset();

		printCounter = 0;

		armModule->disablePID();
	}

	void DisabledPeriodic(){
		DisabledInit();
		//updatePID();
		Wait(0.05);
	}

	void AutonomousInit()
	{
		DisabledInit();
	}

	void AutonomousPeriodic()
	{
		if(printCounter % 50 == 0){
			cout 	<< "T: " << timer->Get() << " EB: " << elevatorModule->getButton() << " ALB: " << armModule->getLeftButton() << " AMB: " << armModule->getMidButton() << " ARB: " << armModule->getRightButton()
													<< " RE: " << armModule->getRightPosition() << " LE: " << armModule->getLeftPosition() << endl
													<< " DE: " << driveModule->getEncoderDistance() << " EE: " << elevatorModule->getEncoderDistance()  << " EB: " << elevatorModule->getButton() << endl;
		}

		printCounter++;

		Wait(0.01);
	}

	void TeleopInit()
	{

		try{
			elevatorModule->enable();
			driveModule->enable();
			armModule->enable();
			scorpionModule->enable();
			armModule->calibrate();
			elevatorModule->calibrate();
			elevatorModule->enablePID();
			armModule->enablePID();
			intakeModule->enable();
			toggleY = 0;

		}catch(EaglestrikeError &e){
			cout << "EaglestrikeError" << endl;
			cerr << e.toString() << endl;
			if(e.shouldBeFatal())
				exit(1);

		}

		std::cout << "no error in calibrate" << std::endl;
	}

	double leftSetpoint = 0;

	void TeleopPeriodic()
	{


		driveModule->drive(-leftJoy->GetY(), -rightJoy->GetX());
		scorpionModule->Set(rightJoy->GetRawButton(4));

		//		double leftArmPower = xbox->getLX() * MAX_ARM_POWER;
		//		double rightArmPower = xbox->getRX() * MAX_ARM_POWER;
		//
		//		if(armModule->getLeftButton() && leftArmPower < 0)
		//			leftArmPower = 0;
		//
		//		if(armModule->getRightButton() && rightArmPower > 0)
		//			rightArmPower = 0;
		//
		//		if(armModule->getMidButton()){
		//			if(leftArmPower > 0)
		//				leftArmPower = 0;
		//			if(rightArmPower < 0)
		//				rightArmPower = 0;
		//		}
		//
		//		armModule->setLeftPower(leftArmPower);
		//		armModule->setRightPower(rightArmPower);

		//double elevatorPower = xbox->getLY();
//		double elevatorPower = xbox->getLY() * MAX_ELEVATOR_UP;
//		if(elevatorPower < MAX_ELEVATOR_DOWN)
//			elevatorPower = MAX_ELEVATOR_DOWN;
//
//		if(elevatorModule->getButton() && elevatorPower < 0)
//			elevatorPower = 0;
//
//		elevatorModule->setPower(elevatorPower);

		if(!armModule->isManual()){

			if(xbox->getX()){
				armModule->setDeltaX(3.5625 - .25);
				leftSetpoint = 4;
			}
			else if(xbox->getStart()) {
				armModule->setDeltaX(5.8);
				leftSetpoint = 4;
			}
			else{
				//			armModule->setDeltaX(13.5);
				armModule->setDeltaX(13.5);
				//armModule->setRightArm(armModule->getRightPosition() + xbox->getRX() / 20.0);
				leftSetpoint = 0;
			}

			leftSetpoint += xbox->getLX() / 20.0;

			armModule->setLeftArm(leftSetpoint);
		}else{
			armModule->setLeftPower(xbox->getLX());
			armModule->setRightPower(xbox->getRX());
		}

		if(previous != xbox->getY()) {
			toggleY++;
		}
		previous = xbox->getY();

		if(toggleY % 4 == 0) {
			intakeModule->retract();
		}
		else if(toggleY % 2 == 0) {
			intakeModule->extend();
		}

		if(xbox->getA()) {
			intakeModule->intake(1);
		}
		else if(xbox->getB()) {
			intakeModule->intake(-1);
		}
		else {
			intakeModule->intake(0);
		}

		if(rightJoy->GetRawButton(6)){
			elevatorModule->setPosition(0);
		}else if(rightJoy->GetRawButton(7)){
			elevatorModule->setPosition(12);
		}else if(rightJoy->GetRawButton(8)){
			elevatorModule->setPosition(24);
		}else if(rightJoy->GetRawButton(9)){
			elevatorModule->setPosition(36);
		}else if(rightJoy->GetRawButton(10)){
			elevatorModule->setPosition(48);
		}else if(rightJoy->GetRawButton(11)){
			elevatorModule->setPosition(5);
		}else{

		}

		if(printCounter % 20 == 0){
			cout << "lsp: " << armModule->getLeftSetpoint() << " rsp: " << armModule->getRightSetpoint() << " la: " << armModule->getLeftPower() << " ra: " << armModule->getRightPower() << endl;
			cout << "time: " << timer->Get() << " LD: " << driveModule->getLeftPower() << " RD: " << driveModule->getRightPower() << " LA: " << armModule->getLeftPower() << " RA: " << armModule->getRightPower() << " E: " << elevatorModule->Get() << " xboxLX :" << xbox->getLX() << " xboxRX: " << xbox->getRX() << endl;
			cout << "angle: " << driveModule->getAngle() << endl;
			cout << "POWER:::::::::: " << elevatorModule->Get() << " Encoder: " << elevatorModule->getEncoderTicks() << " BUTTON: "<<elevatorModule->getButton() << endl;
			cout << "Elevator Setpoint: " << elevatorModule->getSetpoint()  << " Elevator height: " << elevatorModule->getEncoderDistance() << endl;
		}

		printCounter++;
		Wait(0.01);
	}

	void TestInit(){

		try{

			armModule->disable();
			driveModule->disable();
			elevatorModule->enable();
			intakeModule->disable();

			elevatorModule->calibrate();
			elevatorModule->enablePID();
		}catch(EaglestrikeError &e){
			cerr << "EaglestrikeError" << endl;
			cerr << e.toString() << endl;
			if(e.shouldBeFatal()){
				Wait(0.05);
				exit(1);
			}
		}
	}

	void updatePID(){
		if(xbox->getA()) {
			elevatorModule->setPID(elevatorModule->getP() - .01/10, elevatorModule->getI(), elevatorModule->getD());
		}
		else if(xbox->getY()) {
			elevatorModule->setPID(elevatorModule->getP() + .01/10, elevatorModule->getI(), elevatorModule->getD());
		}
		else if(xbox->getL3()) {
			elevatorModule->setPID(elevatorModule->getP(), elevatorModule->getI() - .0001/10, elevatorModule->getD());
		}
		else if(xbox->getR3()) {
			elevatorModule->setPID(elevatorModule->getP(), elevatorModule->getI()  + .0001/10, elevatorModule->getD());
		}
		else if(xbox->getStart()) {
			elevatorModule->setPID(elevatorModule->getP(), elevatorModule->getI(), elevatorModule->getD()  + .01/10);
		}
		else if(xbox->getBack()) {
			elevatorModule->setPID(elevatorModule->getP(), elevatorModule->getI(), elevatorModule->getD()  - .01/10);
		}


		if(printCounter % 6 == 0){
			cout << "p: " << elevatorModule->getP() << " d: " << elevatorModule->getD() << " i: " <<elevatorModule->getI() << " error: " << elevatorModule->getError() << " %error: " << elevatorModule->getError() / elevatorModule->getEncoderDistance() * 100 << " height: " << elevatorModule->getEncoderDistance() << " setpoint: " << elevatorModule->getSetpoint()  << " Elevator Power: " << elevatorModule->Get() << endl;
		}

		printCounter++;

	}

	void TestPeriodic()
	{


		updatePID();

		if(xbox->getX()) {
			elevatorModule->setPosition(20);
		}
		else {
			elevatorModule->setPosition(10);
		}
		lw->Run();


		Wait(0.05);
	}
};

START_ROBOT_CLASS(Robot);
