/*
 * MiddleButtonPressedError.h
 *
 *  Created on: Feb 16, 2015
 *      Author: LAHS
 */

#include "EagleStrikeError.h"

#ifndef SRC_ERROR_MIDDLEBUTTONPRESSEDERROR_H_
#define SRC_ERROR_MIDDLEBUTTONPRESSEDERROR_H_

class MiddleButtonPressedError : public EaglestrikeError {
public:
	MiddleButtonPressedError(RobotModule* module, std::string where, std::string what);
	virtual ~MiddleButtonPressedError();
};

#endif /* SRC_ERROR_MIDDLEBUTTONPRESSEDERROR_H_ */
