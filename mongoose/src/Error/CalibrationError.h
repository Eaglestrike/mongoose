/*
 * CalibrationError.h
 *
 *  Created on: Feb 16, 2015
 *      Author: Team 114
 */

#ifndef CALIBRATIONERROR_H_
#define CALIBRATIONERROR_H_

#include "EaglestrikeError.h"


class CalibrationError: public EaglestrikeError {
public:
	CalibrationError(RobotModule*, const char*);
	virtual ~CalibrationError();
};

#endif /* CALIBRATIONERROR_H_ */
