/*
 * ArmCode.cpp
 *
 *  Created on: Jan 7, 2015
 *      Author: Ankith Uppunda
 */

#include "ArmCode.h"

ArmCode::ArmCode(int lV, int rV, int lE1, int lE2, int rE1, int rE2, int rB, int lB, float p_1, float i_1, float d_1, float p_2, float i_2, float d_2) :
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

void ArmCode::open(double width) { //Opens arm to width
	setDeltaX(width);
}

void ArmCode::closed(bool tote) { //Closes arm to the distance of a short-wise tote (tote), or a container (!tote)
	if (tote) {
		setDeltaX(shortToteWidth);
	} else if (!tote) {
		setDeltaX(containerWidth);
	}
}

void ArmCode::setVictors(double left, double right) { //Sets victor speeds
	leftVic.Set(left);
	rightVic.Set(-right);
}

void ArmCode::setX(double x) { //Sets left arm to x, and right arm to the current deltax
	setDeltaAndX(x, deltaX);
}

void ArmCode::setDeltaX(double deltaX) { //changes the deltaX, and opens both arms
	bool expand = (deltaX > ArmCode::deltaX);
	double totalChange = std::abs((deltaX - ArmCode::deltaX)/2); //the amount the arm needs to expand/contract
	if (expand) {
		setDeltaAndX(x - totalChange , deltaX);
	} else if (!expand) {
		setDeltaAndX(x + totalChange, deltaX);
	}

}

void ArmCode::setDeltaAndX(double x, double deltaX) {
	ArmCode::deltaX = deltaX;
	ArmCode::x = x;
	if (deltaX >= totalLength) {
		setL(safeDistance);
		setR(-safeDistance);
		ArmCode::deltaX = totalLength - 2*safeDistance;
	} else {
		setL(x);
		setR(-totalLength + x + deltaX);
	}
	//TODO: make sure we're not on the edge
	//TODO: convert x and dx to setpoint. possibly in setL and setR methods

}

void ArmCode::setL(double L) {
	if (L < safeDistance) {
		control1->SetSetpoint(safeDistance);
		ArmCode::x = safeDistance;
	}
	control1->SetSetpoint(L);
}

void ArmCode::setR(double R) {
	if (R > -safeDistance) {
			control2->SetSetpoint(-safeDistance);
			ArmCode::deltaX = totalLength - x - safeDistance;
	}
	control2->SetSetpoint(R);
}

void ArmCode::calibrate() {
	if(!rightButton.Get()) {
		rightVic.Set(-.2);
	}
	if(!leftButton.Get()) {
		leftVic.Set(.2);
	}
	while(!rightButton.Get() && !leftButton.Get()) {
		if (rightButton.Get()) {
			rightVic.Set(0);
		}
		if (leftButton.Get()) {
			leftVic.Set(0);
		}
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

