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
	string headers[] = {"time", "motor", "encoder", "button", "test"};
	cout << "writing header" << endl;
	log.writeHeader(headers, 5);
	cout << "writing data" << endl;
	for (double i = 0; i < 10; i += .1) {
		time = i;
		cout << i << endl;
		motor = i*i;
		cout << "1" << endl;
		encoder = i/4;
		cout << "2" << endl;
		button = 1/(i+1);
		cout << "3" << endl;
		double data[] = {time, motor, encoder, button, 5.0};
		log.writeData(data, 5);
	}
	return 0;
}


