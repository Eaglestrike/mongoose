/*
 * LoggingError.cpp
 *
 *  Created on: Mar 16, 2015
 *      Author: Team 114
 */

#include <Error/LoggingError.h>

LoggingError::LoggingError(RobotModule* c_module, std::string c_where, std::string c_what):
EaglestrikeError(c_module, c_where, c_what, false) {
	// TODO Auto-generated constructor stub

}

LoggingError::~LoggingError() {
	// TODO Auto-generated destructor stub
}

