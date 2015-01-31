/*
 * PIDOUT.cpp
 *
 *  Created on: Jan 31, 2015
 *      Author: LAHS
 */

#include <PIDOUT.h>

PIDOUT::PIDOUT() {
	// TODO Auto-generated constructor stub

}

PIDOUT::~PIDOUT() {
	// TODO Auto-generated destructor stub
}

void PIDOUT::PIDWrite(float output) {
	a = output;
}

double PIDOUT::getA() {
		return a;
}
