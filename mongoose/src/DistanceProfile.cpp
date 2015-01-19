/*
 * DistanceProfile.cpp
 *
 *  Created on: Jan 16, 2015
 *      Author: Ankith Uppunda
 */

#include <DistanceProfile.h>
#include <math.h>
//#include <complex>

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
	if(end == start) return 0;
	return model.applyFunction(time);
}

LogisticFunction DistanceProfile::getFunction() {
	double K = end -start;
	double h = start;
	double j = 10;
	double k = log((end/(end - .5) - 1))/-(totalTime - j);
	double A = 1;
	LogisticFunction model(K, A, k, h, j);
	return model;
}
