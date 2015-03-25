/*
 * LogisticFunction.cpp
 *
 *  Created on: Jan 17, 2015
 *      Author: Ankith Uppunda
 */

#include "LogisticFunction.h"
#include <math.h>
#include <iostream>

LogisticFunction::LogisticFunction(double K, double A, double k, double h, double j_i) {
	// TODO Auto-generated constructor stub
	LogisticFunction::Ktop = K;
	LogisticFunction::Acons = A;
	LogisticFunction::ksm = k;
	h_u = h;
	j = j_i;

}

double LogisticFunction::applyFunction(double t) {
	return Ktop/(1 + Acons*exp(-ksm*(t - j))) + h_u;
}


LogisticFunction::~LogisticFunction() {
	// TODO Auto-generated destructor stub
}

