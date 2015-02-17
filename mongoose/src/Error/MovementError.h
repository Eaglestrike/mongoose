/*
 * MovementError.h
 *
 *  Created on: Feb 17, 2015
 *      Author: Ben
 */

#ifndef SRC_ERROR_MOVEMENTERROR_H_
#define SRC_ERROR_MOVEMENTERROR_H_

#include "EaglestrikeError.h"

class MovementError: public EaglestrikeError {
public:
	MovementError(const char*, const char*, bool);
	virtual ~MovementError();
};

#endif /* SRC_ERROR_MOVEMENTERROR_H_ */
