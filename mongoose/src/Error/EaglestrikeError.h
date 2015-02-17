/*
 * EaglestrikeError.h
 *
 *  Created on: Feb 16, 2015
 *      Author: Team 114
 */

#ifndef EAGLESTRIKEERROR_H_
#define EAGLESTRIKEERROR_H_

#include <string>
#include <iostream>
//#include "Modules.h"

class RobotModule;

class EaglestrikeError {
public:
	explicit EaglestrikeError(/*RobotModule**/const char* where, const char* what, bool fatal = false);
	virtual ~EaglestrikeError();
	const char* what();
	/*RobotModule**/const char* where();
	const char* toString();
	bool shouldBeFatal();
private:
	const char* m_Error;
	/*RobotModule**/const char* m_Location;
	bool m_Fatal;
};

#endif /* EAGLESTRIKEERROR_H_ */
