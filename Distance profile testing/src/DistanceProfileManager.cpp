/*
 * DistanceProfileManager.cpp
 *
 *  Created on: Jan 22, 2015
 *      Author: Team 114
 */

#include <DistanceProfileManager.h>
#include "WPILib.h"
#include <iostream>

DistanceProfileManager::DistanceProfileManager(std::vector<DistanceProfile*> dists) {
	// TODO Auto-generated constructor stub
	profs = dists;
	std::cout<< profs.size() << std::endl;
}

DistanceProfileManager::~DistanceProfileManager() {
	// TODO Auto-generated destructor stub
}

double DistanceProfileManager::getSetPoint(Timer &time, Encoder &enc) {
	if(currentProf == profs.size()) {
		isDone = true;
		return 0;
	}
	if(profs.at(currentProf)->isDone) {
		currentProf++;
		time.Reset();
		enc.Reset();
		std::cout<<"It reset" << std::endl;
	}
<<<<<<< HEAD
	if(currentProf != profs.size())
		return profs.at(currentProf).getSetPoint(time.Get());
	return 0;
}

double DistanceProfileManager::getSetPoint(Timer &time, Encoder &enc1, Encoder &enc2) {
	if(currentProf == profs.size()) {
		isDone = true;
		return 0;
	}
	if(profs.at(currentProf).isDone) {
		currentProf++;
		time.Reset();
		enc1.Reset();
		enc2.Reset();
	}
	if(currentProf != profs.size())
		return profs.at(currentProf).getSetPoint(time.Get());
	return 0;
=======
	//std::cout<<profs.at(currentProf)->getSetPoint(time.Get());
	return profs.at(currentProf)->getSetPoint(time.Get());
>>>>>>> 078537835c2e64d173015a8cd498f485c7f95fe9
}
