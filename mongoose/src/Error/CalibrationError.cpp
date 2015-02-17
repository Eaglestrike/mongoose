/*
 * CalibrationError.cpp
 *
 *  Created on: Feb 16, 2015
 *      Author: Team 114
 */

#include "CalibrationError.h"

CalibrationError::CalibrationError(const char* where, const char* what): EaglestrikeError(where, what, true) {

}

CalibrationError::~CalibrationError() {
	// TODO Auto-generated destructor stub
}

