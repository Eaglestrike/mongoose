/*
 * DistanceProfileManager.h
 *
 *  Created on: Jan 22, 2015
 *      Author: Team 114
 */
#include "DistanceProfile.h"
#include <iostream>
#include <vector>

#ifndef DISTANCEPROFILEMANAGER_H_
#define DISTANCEPROFILEMANAGER_H_

class DistanceProfileManager {
public:
	DistanceProfileManager(std::vector<DistanceProfile> dists);
	virtual ~DistanceProfileManager();
	double getSetPoint(Timer &time, Encoder &enc);
	double getSetPoint(Timer &time, Encoder &enc1, Encoder &enc2);
	bool isDone = false;
private:
	std::vector<DistanceProfile> profs;
	int currentProf = 0;
};

#endif /* DISTANCEPROFILEMANAGER_H_ */
