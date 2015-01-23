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

Logger::Logger(char* file_name) {
	// TODO Auto-generated constructor stub
	filename = file_name;
}

void Logger::writeHeader(string headers[]) {
	int length;
		length = sizeof(headers);
		if (length == 0) { cout << "The array has no length" << endl; return; }
		writeFile.open(filename, std::ios_base::app);
		cout << length << endl;
		for(int i = 0; i < length-1; i++)  {
			writeFile << headers[i] << ", ";
		}
		writeFile << headers[length - 1] << "\n";
		writeFile.close();
}

void Logger::writeData(double data[]) {
	int length;
	length = sizeof(data);
	if (length == 0) { cout << "The array has no length" << endl; return; }
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

