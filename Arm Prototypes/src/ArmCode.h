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
	ArmCode(int lV, int rV, int lE1, int lE2, int rE1, int rE2, int rB, int lB, float p_1, float i_1, float d_1, float p_2, float i_2, float d_2, float period);
	virtual ~ArmCode();
	void setVictors(double left, double right);
	void open();
	void closed();
	void reset();
	void setX(double x);
	void setDeltaX(double deltaX);
	void setDeltaAndX(double x, double deltaX);
	void move(double x);
	void calibrate();
	// Left is x, Right is deltaX

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

	/*variables */
	double x;
	double deltaX;
};

#endif /* ARMCODE_H_ */
