/*
 * AutonomousHelper.h
 *
 *  Created on: Jan 31, 2015
 *      Author: LAHS
 */
#include "WPILib.h"
#include "DistanceProfile.h"
#include "PIDOUT.h"

#ifndef SRC_AUTONOMOUSHELPER_H_
#define SRC_AUTONOMOUSHELPER_H_

class AutonomousHelper {
public:
	AutonomousHelper(PIDController* driveControl, PIDController* angleControl, PIDController* turnControl, PIDOUT* drive, PIDOUT* angle, PIDOUT* turn, Victor* r1, Victor* r2, Victor* l1, Victor* l2, Encoder* le, Encoder* re);
	virtual ~AutonomousHelper();
	void right(DistanceProfile* prof);
	void left(DistanceProfile* prof);
	void straight(DistanceProfile* prof);
	void back(DistanceProfile* prof);
    void setPower(double left, double right);
    void runDistanceProfile(DistanceProfile* prof);



private:
	PIDController* driveController;
	PIDController* angleController;
	PIDController* turnController;
	PIDOUT* driveOut;
	PIDOUT* angleOut;
	PIDOUT* turnOut;
	Victor* right1;
	Victor* left1;
	Victor* left2;
	Victor* right2;
	Encoder* lenc;
	Encoder* renc;
	Timer* time = new Timer();


};

#endif /* SRC_AUTONOMOUSHELPER_H_ */
