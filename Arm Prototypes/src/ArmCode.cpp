/*
 * ArmCode.cpp
 *
 *  Created on: Jan 7, 2015
 *      Author: Ankith Uppunda
 */

#include "ArmCode.h"

ArmCode::ArmCode(int lV, int rV, int lE1, int lE2, int rE1, int rE2, int rB, int lB, float p_1, float i_1, float d_1, float p_2, float i_2, float d_2, float period) :
leftVic(lV), rightVic(rV),
leftEnc(lE1, lE2), rightEnc(rE1, rE2),
rightButton(rB), leftButton(lB)
{
	leftEnc.Reset();
	rightEnc.Reset();

	// PID Controller
	control1 =  new PIDController(p_1, i_1, d_1, &leftEnc, &leftVic);
	control2 = new PIDController(p_2, i_2, d_2, &rightEnc, &rightVic);

	calibrate();
}

void ArmCode::open() {


}

void ArmCode::closed(bool tote) {

}

void ArmCode::setVictors(double left, double right) {
	leftVic.Set(left);
	rightVic.Set(-right);
}

void ArmCode::setX(double x) {
	ArmCode::x = x;
}

void ArmCode::setDeltaX(double deltaX) {
	ArmCode::deltaX = deltaX;
}

void ArmCode::setDeltaAndX(double x, double deltaX) {
	ArmCode::deltaX = deltaX;
	ArmCode::x = x;
	setL(x);
	setR(x + deltaX);
}

void ArmCode::setL(double L) {
	control1->SetSetpoint(L);

}

void ArmCode::setR(double R) {
	control2->SetSetpoint(R);
}

void ArmCode::calibrate() {
	while(!rightButton.Get()) {
		rightVic.Set(-.2);
	}
	while(!leftButton.Get()) {
		leftVic.Set(.2);
	}
	if(rightButton.Get() && leftButton.Get()) {
		reset();
	}
	rightVic.Set(0);
	leftVic.Set(0);
}

void ArmCode::reset() {
	leftEnc.Reset();
	rightEnc.Reset();
}

ArmCode::~ArmCode() {}

