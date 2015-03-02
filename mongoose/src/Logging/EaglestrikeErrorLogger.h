/*
 * EaglestrikeErrorLogger.h
 *
 *  Created on: Mar 2, 2015
 *      Author: Ben Evans
 */

#ifndef LOGGING_EAGLESTRIKEERRORLOGGER_H_
#define LOGGING_EAGLESTRIKEERRORLOGGER_H_

#include "Error/EaglestrikeError.h"
#include "WPILib.h"
#include <fstream>

class EaglestrikeErrorLogger {
public:
	EaglestrikeErrorLogger(std::string filename);
	EaglestrikeErrorLogger(const char* filename);
	virtual ~EaglestrikeErrorLogger();
	void logError(EaglestrikeError& e);
private:
	std::ofstream file;
};

#endif /* LOGGING_EAGLESTRIKEERRORLOGGER_H_ */
