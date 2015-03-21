/*
 * AutonomousCommandBase.h
 *
 *  Created on: Feb 26, 2015
 *      Author: Giggles
 */

/*
 * This class was created for a drive module with one gyro and one encoder
 *
 *
 */

#include "../../Modules.h"
#include "DistanceProfile.h"
#include <thread>
#include <iostream>


#ifndef PERIPHERALS_AUTONOMOUSCODE_AUTONOMOUSCOMMANDBASE_H_
#define PERIPHERALS_AUTONOMOUSCODE_AUTONOMOUSCOMMANDBASE_H_

class AutonomousCommandBase {
public:
	AutonomousCommandBase(DriveModule* drive);
	virtual ~AutonomousCommandBase();
	void turnAngle(double angle);
	void move(DistanceProfile* path);
	void join();
	void move(double distance, double totalTime);
	static void callSyncMove(void* v, DistanceProfile* path);
	void syncMove(DistanceProfile* path);
	void setSetpoint(double distance);
	void syncSetSetpoint(double distance);
	void setOutputRange(double min, double max);
	static void callSyncSetpoint(void* v,double distance);

private:
	DriveModule* m_Drive;
	std::thread t;

	void runDistanceProf(DistanceProfile* path);
};

#endif /* PERIPHERALS_AUTONOMOUSCODE_AUTONOMOUSCOMMANDBASE_H_ */
