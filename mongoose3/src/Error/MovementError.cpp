/*
 * MovementError.cpp
 *
 *  Created on: Feb 17, 2015
 *      Author: Ben
 */

#include "MovementError.h"

MovementError::MovementError(RobotModule* c_module, std::string c_where, std::string c_what, bool c_fatal): EaglestrikeError(c_module, c_where, c_what, c_fatal) {

}

MovementError::~MovementError() {
}

