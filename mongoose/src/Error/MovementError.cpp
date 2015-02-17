/*
 * MovementError.cpp
 *
 *  Created on: Feb 17, 2015
 *      Author: Ben
 */

#include "MovementError.h"

MovementError::MovementError(const char* c_where, const char* c_what, bool c_fatal): EaglestrikeError(c_where, c_what, c_fatal) {

}

MovementError::~MovementError() {
}

