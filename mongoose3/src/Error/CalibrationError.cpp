/*
 * CalibrationError.cpp
 *
 *  Created on: Feb 16, 2015
 *      Author: Team 114
 */

#include "CalibrationError.h"

CalibrationError::CalibrationError(RobotModule* module, std::string where, std::string what): EaglestrikeError(module, where, what, true) {

}

CalibrationError::~CalibrationError() {
	// TODO Auto-generated destructor stub
}

