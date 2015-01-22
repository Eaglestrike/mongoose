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
using namespace std;


ofstream testFile;

void writeHeader(string headers[], char* filename) {
	int length;
	length = sizeof(headers);
	if (length == 0) { cout << "The array has no length" << endl; return; }
	testFile.open(filename, std::ios_base::app);
	cout << length << endl;
	for(int i = 0; i < length-1; i++)  {
		testFile << headers[i] << ", ";
	}
	testFile << headers[length - 1] << "\n";
	testFile.close();
}

void writeData(double data[], char* filename) {
	int length;
	length = sizeof(data);
	if (length == 0) { cout << "The array has no length" << endl; return; }
	testFile.open(filename, std::ios_base::app);
	cout << length << endl;
	for(int i = 0; i < length-1; i++)  {
		testFile << data[i] << ", ";
	}
	testFile << data[length - 1] << "\n";
	testFile.close();
}

int main() {
	double time = .1;
	double motor = .54;
	double encoder = .47;
	int button = 0;
	testFile.open("test.csv");
	testFile.close();
	string headers[4] = {"time", "motor", "encoder", "button"};
	double data[] = {time, motor, encoder, button};
	writeHeader(headers, "test.csv");
	writeData(data, "test.csv");
	return 0;
}


