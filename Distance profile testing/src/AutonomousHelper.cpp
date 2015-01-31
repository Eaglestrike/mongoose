/*
 * AutonomousHelper.cpp
 *
 *  Created on: Jan 31, 2015
 *      Author: LAHS
 */

#include <AutonomousHelper.h>

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

void AutonomousHelper::right(DistanceProfile* prof) {
	renc->Reset();
	lenc->Reset();
	turnController->Enable();
	while(turnController->GetError() < 5) {
		turnController->SetSetpoint(370/2);
		setPower(driveOut->getA(), -driveOut->getA());
	}
	turnController->Disable();
	renc->Reset();
	lenc->Reset();
	driveController->Enable();
	angleController->Enable();
	Wait(.5);
	runDistanceProfile(prof);
	driveController->Disable();
	angleController->Disable();
}

void AutonomousHelper::left(DistanceProfile* prof) {
	renc->Reset();
	lenc->Reset();
	turnController->Enable();
	while(turnController->GetError() < 5) {
		turnController->SetSetpoint(-370/2);
		setPower(driveOut->getA(), -driveOut->getA());
	}
	turnController->Disable();
	renc->Reset();
	lenc->Reset();
	driveController->Enable();
	angleController->Enable();
	Wait(.5);
	runDistanceProfile(prof);
	driveController->Disable();
	angleController->Disable();
}

void AutonomousHelper::back(DistanceProfile* prof) {
	renc->Reset();
	lenc->Reset();
	turnController->Enable();
	while(turnController->GetError() < 5) {
		turnController->SetSetpoint(370);
		setPower(driveOut->getA(), -driveOut->getA());
	}
	turnController->Disable();
	renc->Reset();
	lenc->Reset();
	driveController->Enable();
	angleController->Enable();
	Wait(.5);
	runDistanceProfile(prof);
	driveController->Disable();
	angleController->Disable();
}

void AutonomousHelper::straight(DistanceProfile* prof) {
	runDistanceProfile(prof);

}

void AutonomousHelper::runDistanceProfile(DistanceProfile* prof) {
	time->Start();
	while(!prof->isDone) {
		driveController->SetSetpoint(prof->getSetPoint(time->Get()));
		setPower(driveOut->getA() + angleOut->getA(), driveOut->getA() - angleOut->getA());
	}
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

