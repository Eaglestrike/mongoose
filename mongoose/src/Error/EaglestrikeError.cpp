/*
 * EaglestrikeError.cpp
 *
 *  Created on: Feb 16, 2015
 *      Author: Team 114
 */

#include "EaglestrikeError.h"

EaglestrikeError::EaglestrikeError(RobotModule* c_module, std::string c_where, std::string c_what, bool c_fatal){
	std::cout << "EaglestrikeError" << std::endl;

	m_Module = c_module;
	m_Where = c_where;
	m_Error = c_what;
	m_Fatal = c_fatal;
}

std::string EaglestrikeError::what(){
	return m_Error;
}

std::string EaglestrikeError::where(){
	return m_Where;
}

RobotModule* EaglestrikeError::getModule(){
	return m_Module;
}

bool EaglestrikeError::shouldBeFatal(){
	return m_Fatal;
}

std::string EaglestrikeError::toString(){
	std::string ret;
	ret + "Error: " + what() + " Where: " + where();
	return ret;
}

EaglestrikeError::~EaglestrikeError() {

}

