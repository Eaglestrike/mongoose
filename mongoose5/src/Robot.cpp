#include "Error/EaglestrikeError.h"
#include "Modules/RobotModule.h"

#include "WPILib.h"
#include <iostream>


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
	Timer* autoTimer;
	int toggleY = 0;
	bool previous;
	unsigned long printCounter = 0;
	std::thread t;

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
//		logs = new CombinedLogs();
//		logs->addModule(elevatorModule);
//		logs->addModule(driveModule);
//		logs->addModule(armModule);
//		logs->addModule(mantaCoreModule);
//		logs->addModule(intakeModule);
//		logs->addHeaders();
//		logs->start();

		timer = new Timer();
		autoTimer = new Timer();
		timer->Start();

		leftJoy = new Joystick(0);
		rightJoy = new Joystick(1);
		xbox = new Xbox(2);
		controller = new CustomController(3);

		printL("\tAutonomousCommandBase()");
		autonomousDriver = new AutonomousCommandBase(driveModule);
		updateSmartDashboard();

		printL("RobotInit() end");
	}

	void DisabledInit() {

		elevatorModule->disable();
		driveModule->disable();
		armModule->disable();
		armModule->disablePID();
		mantaCoreModule->enable();
		mantaCoreModule->off();
		mantaCoreModule->disable();

		elevatorModule->resetPersist();
		armModule->resetPersist();

		driveModule->reset();

		elevatorModule->setPosition(0);
		timer->Reset();

		finished = false;

		printCounter = 0;

		armModule->disablePID();
		updateSmartDashboard();
	}

	void DisabledPeriodic() {
		DisabledInit();
		//updatePID();

		Wait(0.05);
	}

	int autoState = AUTO_MANTA_CORE_WITHOUT_BACK;

	static void checkTime(void* v) {
		((Robot*)(v))->time();
	}
	void time() {
		while(true) {
			if(autoTimer->Get() >= 15) {
				printL("In the thread");
				armModule->endAllLoops = true;
				autonomousDriver->endAllLoops = true;
				break;
			}
		}
	}


	void AutonomousInit() {
		updateSmartDashboard();
		if(autoState == AUTO_GRAB_TOTE /*|| autoState == AUTO_GRAB_THREE_TOTE*/){
			armModule->enable();
			elevatorModule->enable();
			if(!armModule->hasCalibrated())
				calibrateArm();
			if(!elevatorModule->hasCalibrated())
				calibrateElevator();
		}
		autoTimer->Start();
		t = thread(checkTime, this);
		mantaCoreModule->enable();
		driveModule->enable();
		updateSmartDashboard();
		printL("AutonomousInit()");
	}

	void AutonomousPeriodic() {
		updateSmartDashboard();
		if(autoState == AUTO_MANTA_CORE && !finished) {
			mantaCoreModule->setPneumatics(true);
			autonomousDriver->setOutputRange(-.5, .5);
			autonomousDriver->setSetpoint(-3.3);
			Wait(1);
			autonomousDriver->setOutputRange(-1, 1);
			autonomousDriver->setSetpoint(12);
			Wait(0.15);
			mantaCoreModule->setPneumatics(false);
			Wait(2);
			mantaCoreModule->on();

			//mantaCoreModule->reverse();
			finished = true;
			//			autonomousDriver->syncMove(new DistanceProfile(3.3, 0, 2.0));
			//			Wait(1.5);
			//			mantaCoreModule->setPneumatics(true);
			//			autonomousDriver->join();
			//			autonomousDriver->syncMove(new DistanceProfile(0, 10.3, 3));
			//			Wait(3);
			//			mantaCoreModule->setPneumatics(false);
			//			autonomousDriver->join();
			//			finished = true;

			/*
			 * autonomousDriver->syncSetSetpoint(3.3);
			 * Wait(1.0);
			 * mantaCoreModule->setPneumatics(true);
			 * autonomousDriver->join();
			 * autonomousDriver->syncSetSetpoint(10.3);
			 * Wait(3);
			 * mantaCoreModule->setPneumatics(false);
			 * autonomousDriver->join();
			 * finished = true;
			 */
		} else if(autoState == AUTO_DRIVE_STRAIGHT && !finished) {
			autonomousDriver->move(new DistanceProfile(0, 10, 5));
			Wait(0.5);
			autonomousDriver->turnAngle(90);
			Wait(0.5);
			finished = true;
		} else if(autoState == AUTO_GRAB_TOTE && !finished) {
			/* Start By grabbing one tote */
			if(!finished) {
				elevatorModule->setPosition(0);
				Wait(0.5);
				armModule->grab(ARM_CLOSED_TOTE_DISTANCE);
				Wait(1);
				//autonomousDriver->move(new DistanceProfile(1.5 , 0, 2));
				//Wait(0.25);
				//				elevatorModule->setPosition(35);
				//				Wait(0.3);
				//				intakeModule->extend();
				//				Wait(2);
				//				intakeModule->intake(1, true);
				//				Wait(1.0);
				//				autonomousDriver->move(new DistanceProfile(0, 5, 4));
				//				Wait(1);
				//				autonomousDriver->turnAngle(0);
				//				Wait(.5);
				//				intakeModule->intake(1);
				//				autonomousDriver->move(new DistanceProfile(0, 2, 2));
				//				Wait(1);
				//				elevatorModule->setPosition(12.5);
				//				Wait(1);
				//armModule->open();
				//				Wait(0.25);
				//				intakeModule->intake(1);
				//				Wait(0.25);
				autonomousDriver->turnAngle(90);
				Wait(0.25);
				autonomousDriver->move(new DistanceProfile(0, 11.5, 6));
				Wait(0.25);
				autonomousDriver->turnAngle(90);
				Wait(0.25);
				armModule->open();
				//				elevatorModule->setPosition(0);
				//				Wait(.2);
				//				armModule->open();
				finished = true;
			}
		} else if(autoState == AUTO_MANTA_CORE_WITHOUT_BACK && !finished) {
			mantaCoreModule->setPneumatics(true);
			Wait(1);
			autonomousDriver->setSetpoint(10);
			Wait(0.15);
			mantaCoreModule->setPneumatics(false);
			mantaCoreModule->on();
			Wait(2);
			mantaCoreModule->off();
			finished = true;

		} else if(autoState == AUTO_GRAB_THREE_TOTE && !finished) {
//			elevatorModule->setPosition(0);
//			Wait(0.2);
//			armModule->grab(ARM_CLOSED_TOTE_DISTANCE);
//			Wait(0.2);
//			elevatorModule->setPosition(35);
//			intakeModule->intake(1, true);
//			Wait(0.1);
			autonomousDriver->setSetpoint(5);
			Wait(0.1);
//			elevatorModule->setPosition(ELEVATOR_LEVEL_1);
//			intakeModule->intake(1);
			autonomousDriver->setSetpoint(2);
//			Wait(0.15);
//			armModule->open();
//			Wait(.1);
//			elevatorModule->setPosition(ELEVATOR_LEVEL_0);
//			Wait(.1);
//			armModule->grab(ARM_CLOSED_TOTE_DISTANCE);
//			Wait(.1);
//			elevatorModule->setPosition(35);
//			Wait(.1);
//			intakeModule->intake(1, true);
			Wait(.1);
			autonomousDriver->setSetpoint(5);
//			Wait(.1);
//			intakeModule->intake(1);
			Wait(.1);
			autonomousDriver->setSetpoint(2);
			//			Wait(.1);
//			elevatorModule->setPosition(0);
//			Wait(.15);
//			armModule->open();
			Wait(.1);
			autonomousDriver->setOutputRange(-.5, .5);
			autonomousDriver->turnAngle(90);
			Wait(.1);
			autonomousDriver->setOutputRange(-1, 1);
			autonomousDriver->move(new DistanceProfile(0, 10.5, 4.0));
			finished = true;

		}
		else if(autoState == AUTO_DO_NOTHING) {

		}
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
//					<< SmartDashboard::GetNumber("DeltaX")
					<< endl;
		}
		//t.join();
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

		if(!armModule->hasCalibrated())
			calibrateArm();
		if(!elevatorModule->hasCalibrated())
			calibrateElevator();

		armModule->enablePID();
		leftSetpoint = OPEN_LEFT_SETPOINT;
		deltaX = MAX_DELTA_X;
		elevatorModule->setPosition(0);
		updateSmartDashboard();
	}

	void calibrateArm(){
		try {
			printL("Before cal");
			armModule->calibrate();
			printL("After cal");
			printL("Arm Module enabled");
		} catch (EaglestrikeError &e) {
			cerr << "EaglestrikeError: " << e.toString() << endl;
			eaglestrikeLogger->logError(e);
			if (e.shouldBeFatal())
				e.getModule()->handleFatalError();

		}
		armModule->enablePID();
	}

	void calibrateElevator(){
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
		elevatorModule->enablePID();
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
		updateSmartDashboard();

		driveModule->drive(-leftJoy->GetY(), -rightJoy->GetX());

		if(rightJoy->GetRawButton(11)){
			calibrateArm();
		}
		if(rightJoy->GetRawButton(10)){
			calibrateElevator();
		}
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
		} else if(rightJoy->GetTrigger()) {
			intakeModule->intake(1, true);
		}else if(leftJoy->GetTrigger()) {
			intakeModule->intake(-1, true);

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


		if (leftJoy->GetRawButton(3)) {
			mantaCoreModule->on();
		} else if (leftJoy->GetRawButton(2)) {
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
			armModule->open();
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
					<< elevatorModule->Get() << endl;
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
		if (controller->getLevel0()) {
			driveModule->setDrivePID(driveModule->getDriveP() - .01 / 10,
					driveModule->getDriveI(), driveModule->getDriveD());
		} else if (controller->getLevel1()) {
			driveModule->setDrivePID(driveModule->getDriveP() + .01 / 10,
					driveModule->getDriveI(), driveModule->getDriveD());
		} else if (controller->getLevel2()) {
			driveModule->setDrivePID(driveModule->getDriveP(),
					driveModule->getDriveI() - .001, driveModule->getDriveD());
		} else if (controller->getLevel3()) {
			driveModule->setDrivePID(driveModule->getDriveP(),
					driveModule->getDriveI() + .001, driveModule->getDriveD());
		} else if (controller->getLevel4()) {
			driveModule->setDrivePID(driveModule->getDriveP(),
					driveModule->getDriveI(), driveModule->getDriveD() - .01);
		} else if (controller->getLevel5()) {
			driveModule->setDrivePID(driveModule->getDriveP(),
					driveModule->getDriveI(), driveModule->getDriveD() + .001);
		}

		if (printCounter % 6 == 0) {
			cout << "p: " << driveModule->getDriveP() << " d: "
					<< driveModule->getDriveD() << " i: "
					<< driveModule->getDriveI() << " error: "
					<< driveModule->getDriveError()
					<< " Position: " << driveModule->getEncoderDistance()
					<< " setpoint: " << driveModule->getDriveSetpoint()
					<< endl;
		}

		printCounter++;

	}

	int testMode = 4;

	void TestInit() {
//Cole Was Here

		std::cout << "TestInit" << testMode << "()" << std::endl;
		if(testMode == 1)
			TestInit1();
		else if(testMode == 2)
			TestInit2();
		else if(testMode == 3) {
			TestInit3();
		}
		else if(testMode == 4) {
			TestInit4();
		}

		updateSmartDashboard();
	}
	void TestInit4() {
		//intakeModule->enable();
		armModule->enable();
		//mantaCoreModule->enable();
	}
	void TestInit1() {
		//		armModule->enable();
		//		try {
		//			armModule->calibrate();
		//			armModule->enablePID();
		//		} catch(EaglestrikeError &e) {
		//			if(e.shouldBeFatal()) {
		//				e.getModule()->handleFatalError();
		//			}
		//		}
		driveModule->enable();
		driveModule->enablePID();
	}
	void TestInit2() {
		DisabledInit();
	}

	void TestInit3(){
		armModule->enable();
		armModule->enablePID();
		calibrateArm();
	}

	void TestPeriodic1() {
		updatePID();
		if(controller->getRight3()) {
			driveModule->setDriveSetpoint(5);
		}
		else driveModule->setDriveSetpoint(0);
		driveModule->setPower(driveModule->getDriveOutput() + driveModule->getAngleOutput(), driveModule->getDriveOutput() -driveModule->getAngleOutput());
		Wait(.05);
	}

	int count = 0;
	bool finished = false;
	void TestPeriodic() {
		if(testMode == 1)
			TestPeriodic1();
		else if(testMode == 2)
			TestPeriodic2();
		else if(testMode == 3) {
			TestPeriodic3();
		}
		else if(testMode == 4) {
			TestPeriodic4();
		}
		updateSmartDashboard();
		Wait(0.05);
	}
	void TestPeriodic2() {
		//updatePID();

		//		if(xbox->getX()) {
		//			elevatorModule->setPosition(12.5);
		//		}
		//		else {
		//			elevatorModule->setPosition(0);
		//		}
		//DisabledInit();
		lw->Run();
		//
		if (printCounter % 12 == 0) {
			cout << "T: " << timer->Get() << " EB: "
					<< elevatorModule->getButton() << " ALB: "
					<< armModule->getLeftButton() << " AMB: "
					<< armModule->getMidButton() << " ARB: "
					<< armModule->getRightButton() << " RE: "
					<< armModule->getRightPosition() << " LE: "
					<< armModule->getLeftPosition() << endl << " DE: "
					<< driveModule->getEncoderDistance() << " angle: "
					<< driveModule->getAngle() << " EE: "
					<< elevatorModule->getEncoderDistance() << " EET: "
					<< elevatorModule->getEncoderTicks() << " EB: "
					<< elevatorModule->getButton() << endl <<"DeltaX: "
//					<< SmartDashboard::GetNumber("DeltaX") <<
					<<endl;
		}
		printCounter++;

		Wait(0.05);
	}

	double startTestDeltaX = 7;

	void TestPeriodic3()  {
		if(controller->grabTote()){
			armModule->setLeftArm(OPEN_LEFT_SETPOINT);
			armModule->setDeltaX(startTestDeltaX);
		}else{
			armModule->setLeftArm(OPEN_LEFT_SETPOINT);
			armModule->setDeltaX(MAX_DELTA_X);
		}

		if(controller->GetRawButton(9))
			startTestDeltaX += 0.1;
		else if(controller->GetRawButton(8))
			startTestDeltaX -= 0.1;

		Wait(0.05);
	}
	void TestPeriodic4() {
//		if(controller->getLevel0()) {
//			mantaCoreModule->on();
//		}
//		else if(controller->getLevel3()) {
//			mantaCoreModule->reverse();
//		}
//		else {
//			mantaCoreModule->off();
//		}
//
//		if(controller->getLevel1()) {
//			mantaCoreModule->setPneumatics(true);
//		}
//		else if(controller->getLevel2()) {
//			mantaCoreModule->setPneumatics(false);
//		}
//		if(controller->getLevel0()) {
//			intakeModule->intake(1);
//		}
//		else if(controller->getLevel1()) {
//			intakeModule->intake(-1);
//		}
//		else {
//			intakeModule->intake(0);
//		}
		armModule->setRightPower(controller->getRightX());
		armModule->setLeftPower(controller->getLeftX());
	}

	void printL(std::string message) {
		std::cout << message << endl;
		eaglestrikeLogger->log(message);
	}

	void updateSmartDashboard(){
		SmartDashboard::PutBoolean("Arm Calibrated", armModule->hasCalibrated());
		SmartDashboard::PutBoolean("Elevator Calibrated", elevatorModule->hasCalibrated());

		SmartDashboard::PutNumber("Elev Setpoint", elevatorModule->getSetpoint());
		SmartDashboard::PutNumber("Elev Position", elevatorModule->getEncoderDistance());
		SmartDashboard::PutNumber("LArm Setpoint", armModule->getLeftSetpoint());
		SmartDashboard::PutNumber("RArm Setpoint", armModule->getRightSetpoint());
		SmartDashboard::PutNumber("LArm Position", armModule->getLeftPosition());
		SmartDashboard::PutNumber("RArm Position", armModule->getRightPosition());
	}

};

START_ROBOT_CLASS(Robot)
