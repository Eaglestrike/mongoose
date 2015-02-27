/*
 * DistanceProfile.cpp
 *
 *  Created on: Jan 16, 2015
 *      Author: Ankith Uppunda
 */

#include <DistanceProfile.h>
#include <math.h>
#include <iostream>
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
	if(time > totalTime + .5) isDone = true;
	return model.applyFunction(time);
}

LogisticFunction DistanceProfile::getFunction() {
	if(start < end) {
		double K = end -start;
		double h = 0;
		if(end < 15){
		  h = start;
		}
		else {
			h = start + 15;
			K = end - start - 15;
		}
		double exp1 = log((K - .5)/.5);
		double exp2 = log(K/(K-.5) - 1);
		double j = totalTime * exp1/(exp1 - exp2);
		double k = (-log((K/(K - .5) - 1)) + log((K - .5)/.5))/totalTime;
		double A = 1;
		LogisticFunction model(K, A, k, h, j);
		return model;
	}
	else {
		double K = -start + end;
		double h = 0;
		if(start > 15) {
			h = -end - 15;
			K = -start + end + 15;
		}
		else h = -end;
		double exp1 = log((K + .5)/-.5);
		double exp2 = log(K/(K+.5) - 1);
		double k = (exp1 - exp2)/totalTime;
		double j = exp1/k;
		double A = 1;
		LogisticFunction model(K, A, k, h, j);
		return model;
	}
}
