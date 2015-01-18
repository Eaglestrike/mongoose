/*
 * DistanceProfile.cpp
 *
 *  Created on: Jan 16, 2015
 *      Author: Ankith Uppunda
 */

#include <DistanceProfile.h>
#include <math.h>

DistanceProfile::DistanceProfile(double start, double end, double totalTime) {
	// TODO Auto-generated constructor stub
	DistanceProfile::start = start;
	DistanceProfile::end = end;
	DistanceProfile::totalTime = totalTime;
	model = getFunction();

}

DistanceProfile::~DistanceProfile() {
	// TODO Auto-generated destructor stub
}

double DistanceProfile::getSetPoint(double time) {
	//use function to calculate setPoint
	return model.applyFunction(time);
}

LogisticFunction DistanceProfile::getFunction() {
	double K = end;
	double h = start;
	double j = 10;
	double k = log(K/(K - h) - 1)/totalTime;
	double A = 1;
	LogisticFunction model(K, A, k, h, j);
	return model;
}
