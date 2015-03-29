/*
 * PIDOUT.h
 *
 *  Created on: Jan 31, 2015
 *      Author: LAHS
 */
#include "WPILib.h"

#ifndef SRC_PIDOUT_H_
#define SRC_PIDOUT_H_

class PIDOUT : public PIDOutput {

private:
	double a = 0;
	virtual ~PIDOUT();

public:
	PIDOUT();
	void PIDWrite(float output);

	double getA();
};

#endif /* SRC_PIDOUT_H_ */
