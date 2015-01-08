/*
 * ArmCode.cpp
 *
 *  Created on: Jan 7, 2015
 *      Author: Ankith Uppunda
 */

#include "ArmCode.h"

ArmCode::ArmCode(int lV, int rV, int lE1, int lE2, int rE1, int rE2, int rB, int lB) :
leftVic(lV), rightVic(rV),
leftEnc(lE1, lE2), rightEnc(rE1, rE2),
rightButton(rB), leftButton(lB)
{
	leftEnc.Start();
	rightEnc.Start();

	// TODO Auto-generated constructor stub

}

void ArmCode::start() {


}

void ArmCode::setVictors() {

}

ArmCode::~ArmCode() {
	// TODO Auto-generated destructor stub
}

