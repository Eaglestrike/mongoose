/*
 * MiddleButtonPressedError.h
 *
 *  Created on: Feb 16, 2015
 *      Author: LAHS
 */

#include "EagleStrikeError.h"

#ifndef SRC_ERROR_MIDDLEBUTTONPRESSEDERROR_H_
#define SRC_ERROR_MIDDLEBUTTONPRESSEDERROR_H_

class MiddleButtonPressedError : public EagleStrikeError {
public:
	MiddleButtonPressedError(const char* where, const char* what);
	virtual ~MiddleButtonPressedError();
};

#endif /* SRC_ERROR_MIDDLEBUTTONPRESSEDERROR_H_ */
