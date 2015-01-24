/*
 * Logger.cpp
 *
 *  Created on: Jan 22, 2015
 *      Author: Nathan
 */

#include "Logger.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
using namespace std;

char* filename;
ofstream writeFile;
bool headed;
int catagories;

Logger::Logger(char* file_name) {
	// TODO Auto-generated constructor stub
	filename = file_name;
	headed = false;
}

void Logger::writeHeader(string headers[], int length) {
	cout << length << endl;
	if (length == 0) { cout << "The array has no length" << endl; return; }
	if (!headed) {
		cout << "writing" << endl;
		writeFile.open(filename, std::ios_base::app);
		cout << "opened" << endl;
		for(int i = 0; i < length-1; i++)  {
			writeFile << headers[i] << ", ";
		}
		cout << "loop finished";
		writeFile << headers[length - 1] << "\n";
		writeFile.close();
	}
	headed = true;
	catagories = length;
}

void Logger::writeData(double data[], int length) {
	if (length == 0) { cout << "The array has no length" << endl; return; }
	if (length != catagories) { cout << "The array length is not compatible" << endl; return; }
	writeFile.open(filename, std::ios_base::app);
	cout << length << endl;
	for(int i = 0; i < length-1; i++)  {
		writeFile << data[i] << ", ";
	}
	writeFile << data[length - 1] << "\n";
	writeFile.close();
}

Logger::~Logger() {
	// TODO Auto-generated destructor stub
}

