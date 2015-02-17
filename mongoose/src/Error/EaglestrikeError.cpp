/*
 * EaglestrikeError.cpp
 *
 *  Created on: Feb 16, 2015
 *      Author: Team 114
 */

#include "EaglestrikeError.h"

EaglestrikeError::EaglestrikeError(const char* c_where, const char* c_what, bool c_fatal){
	m_Location = c_where;
	m_Error = c_what;
	m_Fatal = c_fatal;
}

const char* EaglestrikeError::what(){
	return m_Error;
}

const char* EaglestrikeError::where(){
	return m_Location;
}

bool EaglestrikeError::shouldBeFatal(){
	return m_Fatal;
}

EaglestrikeError::~EaglestrikeError() {

}

