#include "WPILib.h"
#include <iostream>
/*
 * ArmCode.h
 *
 *  Created on: Jan 7, 2015
 *      Author: Ankith Uppunda
 */

#ifndef ARMCODE_H_
#define ARMCODE_H_

#define DEBUG 1

class ArmCode {
public:
	ArmCode(int lV, int rV, int lE1, int lE2, int rE1, int rE2, int lB, int rB, float p_1, float i_1, float d_1, float p_2, float i_2, float d_2);
	virtual ~ArmCode();
	void setVictors(double left, double right);
	void open(double width);
	void closed(bool tote);
	void reset();
	void setX(double x);
	void setDeltaX(double deltaX);
	void setDeltaAndX(double x, double deltaX);
	void move();
	void calibrate();
	void setL(double l);
	void setR(double r);
	int getRTick();
	int getLTick();
	bool getRButton();
	bool getLButton();
	void setLVictor(float);
	void setRVictor(float);

	// Both are positive from their respective sides

private:
	/* Hardware */
	Victor leftVic;
	Victor rightVic;
	Encoder leftEnc;
	Encoder rightEnc;
	DigitalInput rightButton;
	DigitalInput leftButton;

	/*   PID Controllers   */
	PIDController* control1;
	PIDController* control2;

	/*variables */
	double x;
	double deltaX;
	double shortToteWidth;
	double containerWidth;
	double totalLength; //TODO: Find the length of the bar in encoder ticks
	double safeDistance; //TODO: Find the proper distance to set as the safe distance
	double maxPower = .1;

};

#endif /* ARMCODE_H_ */
