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
	double data[3] = {time, motor, encoder};
	cout << sizeof(headers) << endl;
	log.writeHeader(headers, 5);
	log.writeData(data, 5);
	log.writeData(data, 3);
	return 0;
}


