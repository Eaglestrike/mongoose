#include "WPILib.h"
/*
 * ArmCode.h
 *
 *  Created on: Jan 7, 2015
 *      Author: Ankith Uppunda
 */

#ifndef ARMCODE_H_
#define ARMCODE_H_

class ArmCode {
public:
	ArmCode(int lV, int rV, int lE1, int lE2, int rE1, int rE2, int rB, int lB);
	virtual ~ArmCode();
	void setVictors();
	void start();


private:
	/* Hardware */
	Victor leftVic;
	Victor rightVic;
	Encoder leftEnc;
	Encoder rightEnc;
	DigitalInput rightButton;
	DigitalInput leftButton;

	/*   PID Controllers   */
	PIDController control1;
	PIDController control2;

};

#endif /* ARMCODE_H_ */
