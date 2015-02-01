/*
 * AutonomousHelper.cpp
 *
 *  Created on: Jan 31, 2015
 *      Author: LAHS
 */

#include <AutonomousHelper.h>
#include <iostream>

AutonomousHelper::AutonomousHelper(PIDController* driveControl, PIDController* angleControl, PIDController* turnControl, PIDOUT* drive, PIDOUT* angle, PIDOUT* turn, Victor* r1, Victor* r2, Victor* l1, Victor* l2, Encoder* le, Encoder* re) {
	driveController = driveControl;
	angleController = angleControl;
	turnController = turnControl;
	//driveController->Enable();
	//angleController->Enable();
	right1 = r1;
	right2 = r2;
	left1 = l1;
	left2 = l2;
	driveOut = drive;
	angleOut = angle;
	turnOut = turn;
	renc = re;
	lenc = le;
}

void AutonomousHelper::right(/*DistanceProfile* prof*/ double angle) {
	renc->Reset();
	lenc->Reset();
	turnController->Enable();
	turnController->SetSetpoint(340*angle/180);
	Timer* time = new Timer();
	while(time->Get() < .2) {
		setPower(turnOut->getA(), -turnOut->getA());
		if(turnController->GetError() < 70) {
			time->Start();
		}
		else {
			time->Reset();
		}
	}
	turnController->Disable();
	setPower(0,0);
	renc->Reset();
	lenc->Reset();
//	driveController->Enable();
//	angleController->Enable();
//	Wait(.5);
//	runDistanceProfile(prof);
//	driveController->Disable();
//	angleController->Disable();
}

void AutonomousHelper::left(DistanceProfile* prof) {
	renc->Reset();
	lenc->Reset();
	turnController->Enable();
	turnController->SetSetpoint(-370/2);
	while(abs(turnController->GetError()) > 30) {
		setPower(turnOut->getA(), -turnOut->getA());
	}
	turnController->Disable();
	setPower(0,0);
	renc->Reset();
	lenc->Reset();
	driveController->Enable();
	angleController->Enable();
	Wait(.5);
	runDistanceProfile(prof);
	driveController->Disable();
	angleController->Disable();
}

//void AutonomousHelper::back(DistanceProfile* prof) {
//	renc->Reset();
//	lenc->Reset();
//	turnController->Enable();
//	turnController->SetSetpoint(330);
//	std::cout << turnController->GetError() << std::endl;
//	int in = 0;
//	//Timer  *timer = new Timer();
//	//timer->Start();
//	float prevError = 0;
//	while(abs(turnController->GetError()) > 60  || prevError != turnController->GetError()) {
//		setPower(turnOut->getA(), -turnOut->getA());
//		if(in % 100 == 0) {
//			std::cout<< "error " << turnController->GetError() << std::endl;
//		}
////		if(prevError == turnController->GetError()) {
////			break;
////		}
//		prevError = turnController->GetError();
//	}
//	//timer->Stop();
//	turnController->Disable();
//	setPower(0,0);
//	renc->Reset();
//	lenc->Reset();
//	driveController->Enable();
//	angleController->Enable();
//	Wait(300);
//	runDistanceProfile(prof);
//	driveController->Disable();
//	angleController->Disable();
//}
//
void AutonomousHelper::straight(DistanceProfile* prof) {
	renc->Reset();
	lenc->Reset();
	driveController->Enable();
	angleController->Enable();
	runDistanceProfile(prof);
	std::cout<< "PI" << std::endl;
}

void AutonomousHelper::runDistanceProfile(DistanceProfile* prof) {
	time->Start();
	std::cout<< "PI" << std::endl;
	while(!prof->isDone) {
		driveController->SetSetpoint(prof->getSetPoint(time->Get()));
		setPower(driveOut->getA() + angleOut->getA(), driveOut->getA() - angleOut->getA());
	}
	std::cout<< "PI" << std::endl;
	time->Reset();
	time->Stop();
	setPower(0,0);
}

void AutonomousHelper::setPower(double left, double right) {
	left1->Set(left);
	left2->Set(left);
	right1->Set(-right);
	right2->Set(-right);
}
AutonomousHelper::~AutonomousHelper() {
	// TODO Auto-generated destructor stub
}

