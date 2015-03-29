/*
 * LogisticFunction.h
 *
 *  Created on: Jan 17, 2015
 *      Author: Ankith Uppunda
 */


#ifndef SRC_LOGISTICFUNCTION_H_
#define SRC_LOGISTICFUNCTION_H_

class LogisticFunction {
public:
	LogisticFunction(double K, double A, double k, double h, double j_i);
	virtual ~LogisticFunction();
	LogisticFunction(){};


	double applyFunction(double t);

private:
	double Ktop;
	double Acons;
	double ksm;
	double h_u;
	double j;
};

#endif /* SRC_LOGISTICFUNCTION_H_ */
