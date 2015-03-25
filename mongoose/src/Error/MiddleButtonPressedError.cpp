/*
 * MiddleButtonPressedError.cpp
 *
 *  Created on: Feb 16, 2015
 *      Author: LAHS
 */

#include "MiddleButtonPressedError.h"

MiddleButtonPressedError::MiddleButtonPressedError(RobotModule* module, std::string where, std::string what) : EaglestrikeError(module, where, what, false){

}

MiddleButtonPressedError::~MiddleButtonPressedError() {
	// TODO Auto-generated destructor stub
}

