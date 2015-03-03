/*
 * EaglestrikeErrorLogger.cpp
 *
 *  Created on: Mar 2, 2015
 *      Author: Ben Evans
 */

#include "EaglestrikeErrorLogger.h"

EaglestrikeErrorLogger::EaglestrikeErrorLogger(std::string filename):
file(filename, std::ios_base::app)
{

}


EaglestrikeErrorLogger::~EaglestrikeErrorLogger() {
	file.close();
}

void EaglestrikeErrorLogger::logError(EaglestrikeError& e){
	file 	<< "Error in module: " << e.getModule()->getModuleName() << std::endl
			<< "\twhere() " << e.where() << std::endl
			<< "\twhat() " << e.what() << std::endl
			<< "\tshouldBeFatal() " << e.shouldBeFatal() << std::endl
			<< "\tTimer::GetMatchTime() " << Timer::GetFPGATimestamp() << std::endl << std::endl;
}

void EaglestrikeErrorLogger::log(std::string message){
	file << message << std::endl;
}
