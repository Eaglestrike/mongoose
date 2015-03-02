/*
 * EaglestrikeErrorLogger.cpp
 *
 *  Created on: Mar 2, 2015
 *      Author: Ben Evans
 */

#include "EaglestrikeErrorLogger.h"

EaglestrikeErrorLogger::EaglestrikeErrorLogger(const char* filename):
file(filename)
{

}

EaglestrikeErrorLogger::EaglestrikeErrorLogger(std::string filename):
file(filename)
{

}


EaglestrikeErrorLogger::~EaglestrikeErrorLogger() {
	file.close();
}

void EaglestrikeErrorLogger::logError(EaglestrikeError& e){
	file 	<< "Error in module: " << e.where() << std::endl
			<< "\twhat() " << e.what() << std::endl
			<< "\tshouldBeFatal() " << e.shouldBeFatal() << std::endl
			<< "\tTimer::GetMatchTime() " << Timer::GetMatchTime() << std::endl << std::endl;
}
