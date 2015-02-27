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

#ifndef PERIPHERALS_AUTONOMOUSCODE_AUTONOMOUSCOMMANDBASE_H_
#define PERIPHERALS_AUTONOMOUSCODE_AUTONOMOUSCOMMANDBASE_H_

#include "Modules.h"

class AutonomousCommandBase {
public:
	AutonomousCommandBase(DriveModule* drive);
	virtual ~AutonomousCommandBase();
	void turnAngle(double angle);
	void move(DistanceProfile* path);

private:
	DriveModule* m_Drive;

	void runDistanceProf(DistanceProfile* path);
};

#endif /* PERIPHERALS_AUTONOMOUSCODE_AUTONOMOUSCOMMANDBASE_H_ */
