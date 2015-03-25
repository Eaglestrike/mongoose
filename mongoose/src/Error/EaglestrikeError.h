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
#include "Modules/RobotModule.h"
#include "ErrorReporting.h"

class RobotModule;

class EaglestrikeError {
public:
	explicit EaglestrikeError(RobotModule* module, std::string where, std::string what, bool fatal = false);
	virtual ~EaglestrikeError();
	std::string what();
	RobotModule* getModule();
	std::string where();
	std::string toString();
	bool shouldBeFatal();
private:
	std::string m_Error;
	std::string m_Where;
	RobotModule * m_Module;
	bool m_Fatal;
};

#endif /* EAGLESTRIKEERROR_H_ */
