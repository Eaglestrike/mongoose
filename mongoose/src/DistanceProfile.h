/*
 * DistanceProfile.h
 *
 *  Created on: Jan 16, 2015
 *      Author: Ankith Uppunda
 */

#ifndef SRC_DISTANCEPROFILE_H_
#define SRC_DISTANCEPROFILE_H_

#include "LogisticFunction.h"

class DistanceProfile {
public:
	DistanceProfile(double start, double end, double totalTime);
	virtual ~DistanceProfile();

	double getSetPoint(double time);
	LogisticFunction getFunction();

private:
	float start;
	float end;
	float totalTime;

	LogisticFunction model;
};

#endif /* SRC_DISTANCEPROFILE_H_ */
