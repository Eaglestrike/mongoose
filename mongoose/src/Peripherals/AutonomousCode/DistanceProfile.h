/*
 * DistanceProfile.h
 *
 *  Created on: Feb 27, 2015
 *      Author: Team 114
 */

#ifndef DISTANCEPROFILE_H_
#define DISTANCEPROFILE_H_

#include "LogisticFunction.h"

class DistanceProfile {
public:
	DistanceProfile(double start, double end, double totalTime);
	virtual ~DistanceProfile();

	double getSetPoint(double time);
	LogisticFunction getFunction();

	bool isDone;

private:
	float start;
	float end;
	float totalTime;

	LogisticFunction model;
};
#endif /* DISTANCEPROFILE_H_ */
