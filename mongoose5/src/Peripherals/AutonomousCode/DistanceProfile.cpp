/*
 * DistanceProfile.cpp
 *
 *  Created on: Feb 27, 2015
 *      Author: Team 114
 */

#include "DistanceProfile.h"
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
	if(time > totalTime) isDone = true;
	return model.applyFunction(time);
}

void DistanceProfile::reset() {
	isDone = false;
}

LogisticFunction DistanceProfile::getFunction() {
	if(start < end) {
		double K = end -start;
		double h = 0;
		h = start;
		double exp1 = log((K - .10)/.10);
		double exp2 = log(K/(K-.10) - 1);
		double j = totalTime * exp1/(exp1 - exp2);
		double k = (-log((K/(K - .10) - 1)) + log((K - .10)/.10))/totalTime;
		double A = 1;
		LogisticFunction model(K, A, k, h, j);
		return model;
		/*
		 * double K = end -start;
		double h = 0;
		h = start;
		double exp1 = log((K - .5)/.5);
		double exp2 = log(K/(K-.5) - 1);
		double j = totalTime * exp1/(exp1 - exp2);
		double k = (-log((K/(K - .5) - 1)) + log((K - .5)/.5))/totalTime;
		double A = 1;
		LogisticFunction model(K, A, k, h, j);
		return model;
		 */
	}
	else {
		double K = -start + end;
		double h = 0;
		h = -end;
		double exp1 = log((K + .10)/-.10);
		double exp2 = log(K/(K+.10) - 1);
		double k = (exp1 - exp2)/totalTime;
		double j = exp1/k;
		double A = 1;
		LogisticFunction model(K, A, k, h, j);
		return model;

		/*
		 * double K = -start + end;
		double h = 0;
		h = -end;
		double exp1 = log((K + .5)/-.5);
		double exp2 = log(K/(K+.5) - 1);
		double k = (exp1 - exp2)/totalTime;
		double j = exp1/k;
		double A = 1;
		LogisticFunction model(K, A, k, h, j);
		return model;
		 */
	}
}
