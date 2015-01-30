/*
 * DistanceProfileManager.cpp
 *
 *  Created on: Jan 22, 2015
 *      Author: Team 114
 */

#include <DistanceProfileManager.h>
#include "WPILib.h"
#include <iostream>

DistanceProfileManager::DistanceProfileManager(std::vector<DistanceProfile*> dists, Encoder* lenc, Encoder* renc, Timer* time) {
	// TODO Auto-generated constructor stub
	profs = dists;
	std::cout<< profs.size() << std::endl;
	DistanceProfileManager::lenc = lenc;
	DistanceProfileManager::renc = renc;
	DistanceProfileManager::time = time;
}

DistanceProfileManager::~DistanceProfileManager() {
	// TODO Auto-generated destructor stub
}

double DistanceProfileManager::getSetPoint() {
	if(currentProf == profs.size()) {
		isDone = true;
		return 0;
	}
	if(profs.at(currentProf)->isDone) {
		currentProf++;
		time->Reset();
		lenc->Reset();
		renc->Reset();
		std::cout<<"It reset" << std::endl;
	}
	if(currentProf != profs.size())
		return profs.at(currentProf)->getSetPoint(time->Get());
	return 0;
}
