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
	DistanceProfileManager(std::vector<DistanceProfile*> dists);
	virtual ~DistanceProfileManager();
	double getSetPoint(Timer &time, Encoder &enc);
<<<<<<< HEAD
	double getSetPoint(Timer &time, Encoder &enc1, Encoder &enc2);
=======
	void reset();
>>>>>>> 078537835c2e64d173015a8cd498f485c7f95fe9
	bool isDone = false;
private:
	std::vector<DistanceProfile*> profs;
	int currentProf = 0;
};

#endif /* DISTANCEPROFILEMANAGER_H_ */
