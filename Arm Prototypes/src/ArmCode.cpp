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
	control1(p_1, i_1, d_1, leftEnc, leftVic, period);
	control2(p_2, i_2, d_2, rightEnc, rightVic, period);
}

void ArmCode::open() {

}

void ArmCode::closed() {

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
}

void ArmCode::move(double x) {

}
void ArmCode::calibrate() {
	while(!rightButton.Get()) {

	}
	while(!leftButton.Get()) {

	}
	if(rightButton.Get() && leftButton.Get()) {
		reset();
	}
}
void ArmCode::reset() {
	leftEnc.Reset();
	rightEnc.Reset();
}

ArmCode::~ArmCode() {}

