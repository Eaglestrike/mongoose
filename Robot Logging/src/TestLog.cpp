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
	double motor = .54;
	double encoder = .47;
	int button = 0;
	Logger log("test.csv");
	testFile.open("test.csv");
	testFile.close();
	string headers[4] = {"time", "motor", "encoder", "button"};
	double data[] = {time, motor, encoder, button};
	log.writeHeader(headers);
	log.writeData(data);
	return 0;
}


