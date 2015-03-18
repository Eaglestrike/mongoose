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
#include "Logging/EaglestrikeErrorLogger.h"
#include "Logging/CombinedLogs.h"
#include "CustomController.h"

using namespace std;

class Robot: public IterativeRobot {
private:
	LiveWindow *lw;
	ElevatorModule* elevatorModule;
	DriveModule* driveModule;
	ArmModule* armModule;
	//ScorpionModule* scorpionModule;
	MantaCoreModule* mantaCoreModule;
	IntakeModule* intakeModule;

	Timer* timer;
	EaglestrikeErrorLogger* eaglestrikeLogger;

	Joystick* leftJoy;
	Joystick* rightJoy;
	AutonomousCommandBase* autonomousDriver;
	Xbox* xbox;
	CustomController* controller;
	int toggleY = 0;
	bool previous;
	unsigned long printCounter = 0;

	int logCounter = 100; //How many milliseconds between logging entries
	CombinedLogs* logs;

	NamedSendable* sendable;

	void RobotInit() {

		eaglestrikeLogger = new EaglestrikeErrorLogger(
				"/home/lvuser/eaglestrike.log");
		printL("\nBooting up mongoose");
		printL("RobotInit()");

		lw = LiveWindow::GetInstance();

		printL("\tElevatorModule()");
		elevatorModule = new ElevatorModule(ELEVATOR_1, ELEVATOR_2,
				ELEVATOR_SAFTEY_BUTTON, ELEVATOR_ENCODER_A, ELEVATOR_ENCODER_B);
		printL("\tDriveModule()");
		driveModule = new DriveModule(DRIVE_LEFT_1, DRIVE_LEFT_2, DRIVE_RIGHT_1,
				DRIVE_RIGHT_2, DRIVE_ENCODER_A, DRIVE_ENCODER_B, DRIVE_GYRO);
		printL("\tArmModule()");
		armModule = new ArmModule(RIGHT_ARM_MOTOR, LEFT_ARM_MOTOR,
				RIGHT_ARM_BUTTON, MID_ARM_BUTTON, LEFT_ARM_BUTTON,
				RIGHT_ARM_ENCODER_A, RIGHT_ARM_ENCODER_B, LEFT_ARM_ENCODER_A,
				LEFT_ARM_ENCODER_B);
		printL("\tScorpionModule()");
		//scorpionModule = new ScorpionModule(SCORPION_PORT);
		printL("\tIntakeModule()");
		intakeModule = new IntakeModule(INTAKE_SOLENOID_1, INTAKE_SOLENOID_2,
				INTAKE_MOTOR_1, INTAKE_MOTOR_2);
		printL("\tMantacoreModule()");
		mantaCoreModule = new MantaCoreModule(MANTA_CORE_SPIKE_PORT,
				SCORPION_PORT);

		SmartDashboard::PutNumber("DeltaX", armModule->getDiffSetpoint());

		//				logs = new CombinedLogs();
		//				logs->addModule(elevatorModule);
		//
		//				logs->addModule(driveModule);
		//				logs->addModule(armModule);
		//				logs->addModule(mantaCoreModule);
		//				logs->addModule(intakeModule);
		//				logs->addHeaders();
		//				logs->start();

		timer = new Timer();
		timer->Start();

		leftJoy = new Joystick(0);
		rightJoy = new Joystick(1);
		xbox = new Xbox(2);
		controller = new CustomController(3);

		printL("\tAutonomousCommandBase()");
		autonomousDriver = new AutonomousCommandBase(driveModule);

		printL("RobotInit() end");
	}

	void DisabledInit() {

		elevatorModule->disable();
		driveModule->disable();
		armModule->disable();
		armModule->disablePID();

		elevatorModule->reset();
		driveModule->reset();
		armModule->reset();

		elevatorModule->setPosition(0);
		timer->Reset();

		finished = false;

		printCounter = 0;

		armModule->disablePID();
	}

	void DisabledPeriodic() {
		DisabledInit();
		//updatePID();
		Wait(0.05);
	}

	void AutonomousInit() {
		//		int autostate = 0;
		printL("AutonomousInit()");
		DisabledInit();
	}

	void AutonomousPeriodic() {
		if (printCounter % 50 == 0) {
			cout << "T: " << timer->Get() << " EB: "
					<< elevatorModule->getButton() << " ALB: "
					<< armModule->getLeftButton() << " AMB: "
					<< armModule->getMidButton() << " ARB: "
					<< armModule->getRightButton() << " RE: "
					<< armModule->getRightPosition() << " LE: "
					<< armModule->getLeftPosition() << endl << " DE: "
					<< driveModule->getEncoderDistance() << " EE: "
					<< elevatorModule->getEncoderDistance() << " EET: "
					<< elevatorModule->getEncoderTicks() << " EB: "
					<< elevatorModule->getButton() << endl << "DeltaX: "
					<< SmartDashboard::GetNumber("DeltaX") << endl;
		}

		printCounter++;

		Wait(0.01);
	}
	bool hasEnabled = true;
	void TeleopInit() {

		printL("TeleopInit()");

		elevatorModule->disable();
		printL("Elevator");
		driveModule->enable();
		printL("Drive");
		armModule->disable();
		printL("Arm");
		//scorpionModule->disable();
		intakeModule->enable();
		printL("Intake");
		mantaCoreModule->enable();
		printL("MantaCore");
		toggleY = 0;

		try {
			printL("Before cal");
			armModule->calibrate();
			printL("After cal");
			//			armModule->enablePID();
			printL("Arm Module enabled");
		} catch (EaglestrikeError &e) {
			cerr << "EaglestrikeError: " << e.toString() << endl;
			eaglestrikeLogger->logError(e);
			if (e.shouldBeFatal())
				e.getModule()->handleFatalError();

		}

		//		armModule->setRightPower(0);
		//		armModule->setLeftPower(0);

		try {
			printL("Before Elevator Module calibrate");
			elevatorModule->calibrate();
			printL("After Elevator Module calibrate");
			elevatorModule->enablePID();
			printL("elevator Pid enabled");
			elevatorModule->setPosition(0);

		} catch (EaglestrikeError &e) {
			cerr << "EaglestrikeError: " << e.toString() << endl;
			eaglestrikeLogger->logError(e);
			if (e.shouldBeFatal())
				e.getModule()->handleFatalError();

		}

		armModule->enablePID();
		leftSetpoint = OPEN_LEFT_SETPOINT;
		deltaX = MAX_DELTA_X;
		elevatorModule->setPosition(0);
	}

	double leftSetpoint = OPEN_LEFT_SETPOINT, deltaX = MAX_DELTA_X;
	double startDeltaX = ARM_CLOSED_TOTE_DISTANCE;

	bool hasLS = false;

	bool lastManta = true;
	int mantacounter = 0;
	int state = 0;

	bool lastArmManual = false;
	int armManualCounter = 0;

	bool lastElevatorManual = false;
	int elevatorManualCounter = 0;

	void TeleopPeriodic() {

		lw->Run();

		driveModule->drive(-leftJoy->GetY(), -rightJoy->GetX());
		//scorpionModule->Set(rightJoy->GetRawButton(4));

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

		if (!armModule->isManual()) {

			if (controller->grabTote()) {
				state = 1;
				//					deltaX = startDeltaX;		//2.5625 + 2.5;
				//					leftSetpoint = 4;

			} else if (controller->grabContainer()) {
				state = 2;
				//				deltaX = 5.8;
				//				leftSetpoint = 3;
				//				hasLS = true;
			} else if(controller->open()){
				state = 0;
				//				deltaX = MAX_DELTA_X;
				//				leftSetpoint = OPEN_LEFT_SETPOINT;
				//				hasLS = false;
			}

			if(state == 0) {
				deltaX = MAX_DELTA_X;
				leftSetpoint = OPEN_LEFT_SETPOINT;
				//				hasLS = false;
			} else if(state == 1)  {
				deltaX = startDeltaX;		//2.5625 + 2.5;
				leftSetpoint = 4;
				//				hasLS = true;
			} else if(state == 2) {
				deltaX = 5.8;
				leftSetpoint = 3;
				//				hasLS = true;
			}

			//			if (leftJoy->GetRawButton(4)) {
			//				leftSetpoint += .1;
			//			} else if (leftJoy->GetRawButton(5)) {
			//				leftSetpoint -= .1;
			//			} else if (leftJoy->GetRawButton(3)) {
			//				startDeltaX += .1;
			//			} else if (leftJoy->GetRawButton(2)) {
			//				startDeltaX -= .1;
			//			}

			//			leftSetpoint += xbox->getLX() / 10.0;
			//			deltaX += + xbox->getRY() / 10.0;

			armModule->setLeftArm(leftSetpoint);
			armModule->setDeltaX(deltaX);

		} else {
			armModule->setLeftPower(controller->getLeftX());
			armModule->setRightPower(controller->getRightX());
		}

		if (previous != controller->toggleIntake()) {
			toggleY++;
		}
		previous = controller->toggleIntake();

		if (toggleY % 4 == 0) {
			intakeModule->retract();
		} else if (toggleY % 2 == 0) {
			intakeModule->extend();
		}

		if (controller->intake()) {
			intakeModule->intake(1);
		} else if (controller->extake()) {
			intakeModule->intake(-1);
		} else {
			intakeModule->intake(0);
		}

		if (controller->getLevel0()) {
			elevatorModule->setPosition(0);
		} else if (controller->getLevel1()) {
			elevatorModule->setPosition(12.5);
		} else if (controller->getLevel2()) {
			elevatorModule->setPosition(25);
		} else if (controller->getLevel3()) {
			elevatorModule->setPosition(37);
		} else if (controller->getLevel4()) {
			elevatorModule->setPosition(52);
		} else if (controller->getLevel5()) {
			elevatorModule->setPosition(53);
			//		} else if (controller->getLevel6()){
			//			DriverStation::ReportError("ROBOT OVERLOAD!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
		} else {}


		if (leftJoy->GetRawButton(6)) {
			mantaCoreModule->on();
		} else if (leftJoy->GetRawButton(7)) {
			mantaCoreModule->reverse();
		} else
			mantaCoreModule->off();


		if(controller->getMantaCorePneumatics() != lastManta)
			mantacounter++;

		lastManta = controller->getMantaCorePneumatics();

		if(mantacounter % 4 == 0){
			mantaCoreModule->setPneumatics(true);
		}else if(mantacounter % 2 == 0){
			mantaCoreModule->setPneumatics(false);
		}

		if (controller->drop()) {
			elevatorModule->disablePID();
			elevatorModule->setPower(ELEVATOR_DROP_POWER);
			hasEnabled = false;
		} else if (controller->raise()) {
			elevatorModule->disablePID();
			elevatorModule->setPower(0.5);
			hasEnabled = false;
		} else if(controller->dropRelease()){
			elevatorModule->disablePID();
			elevatorModule->setPower(ELEVATOR_DROP_POWER);
			leftSetpoint = OPEN_LEFT_SETPOINT;
			deltaX = MAX_DELTA_X;
			hasEnabled = false;
		}else {
			elevatorModule->enablePID();
			if (!hasEnabled)
				elevatorModule->setPosition(
						elevatorModule->getEncoderDistance());
			hasEnabled = true;
		}

		if(lastArmManual != controller->getRight3())
			armManualCounter++;
		lastArmManual = controller->getRight3();

		if(armManualCounter % 4 == 0){
			if(armManualCounter != 0)
				armModule->enablePID();
		} else if(armManualCounter % 2 == 0){
			armModule->disablePID();
		}


		if(lastElevatorManual != controller->getLeft3())
			elevatorManualCounter++;
		lastElevatorManual = controller->getLeft3();

		if(elevatorManualCounter % 4 == 0){
			if(elevatorManualCounter != 0)
				elevatorModule->enablePID();
		} else if(elevatorManualCounter % 2 == 0){
			elevatorModule->disablePID();
		}

		armModule->setLeftArm(leftSetpoint);
		armModule->setDeltaX(deltaX);
		if (printCounter % 12 == 0) {
			cout << "lsp: " << armModule->getLeftSetpoint() << " rsp: "
					<< armModule->getRightSetpoint() << " DX: "
					<< armModule->getDiffSetpoint() << " LAE: "
					<< armModule->getLeftPosition() <<  " RAE: "
					<< armModule->getRightPosition() << " la: "
					<< armModule->getLeftPower() << " ra: "
					<< armModule->getRightPower() << endl;
			cout << "time: " << timer->Get() << " LD: "
					<< driveModule->getLeftPower() << " RD: "
					<< driveModule->getRightPower() << " LA: "
					<< armModule->getLeftPower() << " RA: "
					<< armModule->getRightPower() << " E: "
					<< elevatorModule->Get() << " xboxLX :" << xbox->getLX()
					<< " xboxRX: " << xbox->getRX() << endl;
			cout << "angle: " << driveModule->getAngle() << endl;
			cout << "POWER:::::::::: " << elevatorModule->Get() << " Encoder: "
					<< elevatorModule->getEncoderTicks() << " BUTTON: "
					<< elevatorModule->getButton() << endl;
			cout << "Elevator Setpoint: " << elevatorModule->getSetpoint()
																											<< " Elevator height: "
																											<< elevatorModule->getEncoderDistance() << endl;
		}

		printCounter++;
		Wait(0.01);
	}

	void updatePID() {
		if (xbox->getA()) {
			elevatorModule->setPID(elevatorModule->getP() - .01 / 10,
					elevatorModule->getI(), elevatorModule->getD());
		} else if (xbox->getY()) {
			elevatorModule->setPID(elevatorModule->getP() + .01 / 10,
					elevatorModule->getI(), elevatorModule->getD());
		} else if (xbox->getL3()) {
			elevatorModule->setPID(elevatorModule->getP(),
					elevatorModule->getI() - .0001 / 10,
					elevatorModule->getD());
		} else if (xbox->getR3()) {
			elevatorModule->setPID(elevatorModule->getP(),
					elevatorModule->getI() + .0001 / 10,
					elevatorModule->getD());
		} else if (xbox->getStart()) {
			elevatorModule->setPID(elevatorModule->getP(),
					elevatorModule->getI(), elevatorModule->getD() + .01 / 10);
		} else if (xbox->getBack()) {
			elevatorModule->setPID(elevatorModule->getP(),
					elevatorModule->getI(), elevatorModule->getD() - .01 / 10);
		}

		if (printCounter % 6 == 0) {
			cout << "p: " << elevatorModule->getP() << " d: "
					<< elevatorModule->getD() << " i: "
					<< elevatorModule->getI() << " error: "
					<< elevatorModule->getError() << " %error: "
					<< elevatorModule->getError()
					/ elevatorModule->getEncoderDistance() * 100
					<< " height: " << elevatorModule->getEncoderDistance()
					<< " setpoint: " << elevatorModule->getSetpoint()
					<< " Elevator Power: " << elevatorModule->Get() << endl;
		}

		printCounter++;

	}

	void TestInit() {

		armModule->disable();
		driveModule->enable();
		elevatorModule->disable();
		intakeModule->enable();
		mantaCoreModule->enable();

		try {
//			armModule->calibrate();
//			armModule->enablePID();
		} catch (EaglestrikeError &e) {
			cerr << "EaglestrikeError: " << e.toString() << endl;
			eaglestrikeLogger->logError(e);
			if (e.shouldBeFatal())
				exit(-1);

		}

		try {
//			elevatorModule->calibrate();
//			elevatorModule->enablePID();
//			elevatorModule->setPosition(0);

		} catch (EaglestrikeError &e) {
			cerr << "EaglestrikeError: " << e.toString() << endl;
			eaglestrikeLogger->logError(e);
			if (e.shouldBeFatal())
				exit(-1);
		}

		Wait(1);



	}

	int count = 0;
	int autoState = 2;
	bool finished = false;
	void TestPeriodic() {
		//updatePID();

		//		if(xbox->getX()) {
		//			elevatorModule->setPosition(12.5);
		//		}
		//		else {
		//			elevatorModule->setPosition(0);
		//		}

		if (autoState == 0 && !finished) {
			autonomousDriver->move(new DistanceProfile(0, 9.5, 6));
			Wait(0.5);
			autonomousDriver->turnAngle(90);
			Wait(0.5);
			finished = true;
		}
		else if (autoState == 1) {
			/* Start By grabbing one tote */
			if(!finished) {
				elevatorModule->setPosition(0);
				Wait(0.5);
				armModule->grab(ARM_CLOSED_TOTE_DISTANCE + 2.7);
				Wait(1);
				//autonomousDriver->move(new DistanceProfile(1.5 , 0, 2));
				//Wait(0.25);
				elevatorModule->setPosition(35);
				Wait(0.3);
				intakeModule->extend();
				Wait(2);
				intakeModule->intake(1, true);
				Wait(1.0);
				autonomousDriver->move(new DistanceProfile(0, 5, 4));
				Wait(1);
				autonomousDriver->turnAngle(0);
				Wait(.5);
				intakeModule->intake(1);
				autonomousDriver->move(new DistanceProfile(0, 2, 2));
				Wait(1);
				elevatorModule->setPosition(12.5);
				Wait(1);
				//armModule->open();
				//				Wait(0.25);
				//				intakeModule->intake(1);
				//				Wait(0.25);
				//				autonomousDriver->turnAngle(90);
				//				Wait(0.25);
				//				autonomousDriver->move(new DistanceProfile(0, 10.5, 6));
				//				Wait(0.25);
				//				autonomousDriver->turnAngle(90);
				//				Wait(0.25);
				//				armModule->open();
				//				elevatorModule->setPosition(0);
				//				Wait(.2);
				//				armModule->open();

			}
			finished = true;
			//elevatorModule->setPosition(0);
			armModule->disablePID();
			intakeModule->intake(0);


		} else if (autoState == 2 && !finished) {
			autonomousDriver->move(new DistanceProfile(3.3, 0, 3));
			Wait(.5);
			mantaCoreModule->setPneumatics(true);
			Wait(1);
			autonomousDriver->move(new DistanceProfile(0, 10.3, 5));
			Wait(.5);
			mantaCoreModule->setPneumatics(false);
			finished = true;
		} else if (autoState == 3) {

		}

		if(count % 2 == 0)
			std::cout <<" LE: " << armModule->getLeftError() << " RE: " << armModule->getRightError() << " DE: " << armModule->getDiffError() << " LPower: " << armModule->getLeftPower() << " RPower: "<<  armModule->getRightPower() << std::endl;
		count++;
		lw->Run();
		//

		Wait(0.05);
	}

	void printL(std::string message) {
		eaglestrikeLogger->log(message);
		std::cout << message << endl;
	}

};

START_ROBOT_CLASS(Robot);
