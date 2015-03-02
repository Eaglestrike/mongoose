/*
 * InWrongModeError.h
 *
 *  Created on: Mar 1, 2015
 *      Author: Team 114
 */

#ifndef INWRONGMODEERROR_H_
#define INWRONGMODEERROR_H_

#include "EaglestrikeError.h"

class InWrongModeError : public EaglestrikeError {
public:
	InWrongModeError(const char* where, const char* what);
	virtual ~InWrongModeError();
};

#endif /* INWRONGMODEERROR_H_ */
