/*
 * ErrorReporting.h
 *
 *  Created on: Mar 23, 2015
 *      Author: Cole Brinsfield
 */

#ifndef ERROR_ERRORREPORTING_H_
#define ERROR_ERRORREPORTING_H_

#include <WPILib.h>
#include "EaglestrikeError.h"


void reportError(EaglestrikeError* v){
	DriverStation::ReportError(v->toString());
	SmartDashboard::PutString("Error log",  v->toString() + "\n" + SmartDashboard::GetString("Error log"));

}


#endif /* ERROR_ERRORREPORTING_H_ */
