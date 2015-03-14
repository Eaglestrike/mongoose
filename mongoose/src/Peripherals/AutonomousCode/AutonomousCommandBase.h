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
#include <iostream>


#ifndef PERIPHERALS_AUTONOMOUSCODE_AUTONOMOUSCOMMANDBASE_H_
#define PERIPHERALS_AUTONOMOUSCODE_AUTONOMOUSCOMMANDBASE_H_

class AutonomousCommandBase {
public:
	AutonomousCommandBase(DriveModule* drive);
	virtual ~AutonomousCommandBase();
	void turnAngle(double angle);
	void move(DistanceProfile* path);
	void move(double distance, double totalTime);

private:
	DriveModule* m_Drive;

	void runDistanceProf(DistanceProfile* path);
};

#endif /* PERIPHERALS_AUTONOMOUSCODE_AUTONOMOUSCOMMANDBASE_H_ */
