/*
 * AutonomousHelper.h
 *
 *  Created on: Jan 31, 2015
 *      Author: LAHS
 */
#include "WPILib.h"
#include "DistanceProfile.h"
#include "ADXRS453Z.h"
#include "PIDOUT.h"

#ifndef SRC_AUTONOMOUSHELPER_H_
#define SRC_AUTONOMOUSHELPER_H_

class AutonomousHelper {
public:
	AutonomousHelper(PIDController* driveControl, PIDController* angleControl, PIDController* turnControl, PIDOUT* drive, PIDOUT* angle, PIDOUT* turn, Victor* r1, Victor* r2, Victor* l1, Victor* l2, Encoder* le, Encoder* re, ADXRS453Z* gyro);
	AutonomousHelper(PIDController* gyroDrive, PIDController* gyroAngle, PIDController* gyroTurn, PIDOUT* gyroDOut, PIDOUT* gyroAOut, PIDOUT* gyroTOut, Victor* r1, Victor* r2, Victor* l1, Victor* l2, ADXRS453Z* gyro);
	virtual ~AutonomousHelper();
	void right(double angle);
	void left(DistanceProfile* prof);//delete this
	void straight(DistanceProfile* prof);
	void straightWithGyro(DistanceProfile* prof);
	void rightWithGyro(double angle);
	//void back(DistanceProfile* prof);
    void setPower(double left, double right);
    void runDistanceProfile(DistanceProfile* prof);

    // straight(500, 5)
    // msleep(10)
    // right(180)
    // straight(500, 5)


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
	ADXRS453Z* gyro;

	int in = 0;
};

#endif /* SRC_AUTONOMOUSHELPER_H_ */
