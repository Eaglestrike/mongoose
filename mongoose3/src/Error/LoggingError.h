/*
 * LoggingError.h
 *
 *  Created on: Mar 16, 2015
 *      Author: Team 114
 */

#ifndef LOGGINGERROR_H_
#define LOGGINGERROR_H_

#include <Error/EaglestrikeError.h>

class LoggingError: public EaglestrikeError {
public:
	LoggingError(RobotModule* c_module, std::string c_where, std::string c_what);
	virtual ~LoggingError();
};

#endif /* LOGGINGERROR_H_ */
