/*
 * TestLog.cpp
 *
 *  Created on: Jan 21, 2015
 *      Author: Nathan
 */

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include "Logger.h"
using namespace std;


ofstream testFile;

int main() {
	double time = .1;
	double motor = .67;
	double encoder = .01;
	int button = 0;
	Logger log("test.csv");
	testFile.open("test.csv");
	testFile.close();
	string headers[5] = {"time", "motor", "encoder", "button", "qqqq"};
	double data[4] = {time, motor, encoder, button};
	log.writeHeader(headers, 5);
	for (int i = 0; i < 10; i += .1) {
		data[0] = i;
		data[1] = i*i;
		data[2] = i/4;
		data[3] = 1/i;
		log.writeData(data, 4);
	}
	return 0;
}


