/*
 * DistanceProfileManager.h
 *
 *  Created on: Jan 22, 2015
 *      Author: Team 114
 */
#include "DistanceProfile.h"
#include "WPILib.h"
#include <iostream>
#include <vector>

#ifndef DISTANCEPROFILEMANAGER_H_
#define DISTANCEPROFILEMANAGER_H_

class DistanceProfileManager {
public:
	DistanceProfileManager(std::vector<DistanceProfile*> dists, Encoder* lenc, Encoder* renc, Timer* time);
	virtual ~DistanceProfileManager();
	double getSetPoint();
	void reset();
	bool isDone = false;
private:
	std::vector<DistanceProfile*> profs;
	int currentProf = 0;
	Encoder* lenc;
	Encoder* renc;
	Timer* time;
};

#endif /* DISTANCEPROFILEMANAGER_H_ */
