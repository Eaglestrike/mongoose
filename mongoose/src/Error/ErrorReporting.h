/*
 * ErrorReporting.h
 *
 *  Created on: Mar 23, 2015
 *      Author: LAHS
 */

#ifndef ERROR_ERRORREPORTING_H_
#define ERROR_ERRORREPORTING_H_


void reportError(EaglestrikeError* error){
	DriverStation::ReportError(error->toString());

}


#endif /* ERROR_ERRORREPORTING_H_ */
