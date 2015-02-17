/*
 * EaglestrikeError.cpp
 *
 *  Created on: Feb 16, 2015
 *      Author: Team 114
 */

#include "Error/EaglestrikeError.h"

EaglestrikeError::EaglestrikeError(/*RobotModule**/const char* c_where, const char* c_what, bool c_fatal){
	std::cout << "EaglestrikeError" << std::endl;

	m_Location = c_where;
	m_Error = c_what;
	m_Fatal = c_fatal;
}

const char* EaglestrikeError::what(){
	return m_Error;
}

/*RobotModule**/const char* EaglestrikeError::where(){
	return m_Location;
}

bool EaglestrikeError::shouldBeFatal(){
	return m_Fatal;
}

const char* EaglestrikeError::toString(){
	char ret[256];
	sprintf(ret, "Error: %s  Where: %s", what(), where());
	return (const char*)ret;
}

EaglestrikeError::~EaglestrikeError() {

}

