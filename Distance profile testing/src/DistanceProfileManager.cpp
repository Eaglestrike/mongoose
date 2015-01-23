/*
 * DistanceProfileManager.cpp
 *
 *  Created on: Jan 22, 2015
 *      Author: Team 114
 */

#include <DistanceProfileManager.h>
#include "WPILib.h"

DistanceProfileManager::DistanceProfileManager(std::vector<DistanceProfile> dists) {
	// TODO Auto-generated constructor stub
	profs = dists;

}

DistanceProfileManager::~DistanceProfileManager() {
	// TODO Auto-generated destructor stub
}

double DistanceProfileManager::getSetPoint(Timer &time, Encoder &enc) {
	if(currentProf == profs.size()) {
		isDone = true;
		return 0;
	}
	if(profs.at(currentProf).isDone) {
		currentProf++;
		time.Reset();
		enc.Reset();
	}
	return profs.at(currentProf).getSetPoint(time.Get());
}
