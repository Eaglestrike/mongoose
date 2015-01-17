/*
 * DistanceProfile.cpp
 *
 *  Created on: Jan 16, 2015
 *      Author: Ankith Uppunda
 */

#include <DistanceProfile.h>

DistanceProfile::DistanceProfile(float start, float end, float totalTime) {
	// TODO Auto-generated constructor stub
	DistanceProfile::start = start;
	DistanceProfile::end = end;
	DistanceProfile::totalTime = totalTime;
	DistanceProfile::model = DistanceProfile::getFunction();

}

DistanceProfile::~DistanceProfile() {
	// TODO Auto-generated destructor stub
}

double DistanceProfile::getSetPoint(double time) {
	//use function to calculate setPoint
	return 0.0;
}

LogisticFunction DistanceProfile::getFunction() {

}
