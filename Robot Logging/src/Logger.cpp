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
#include <exception>
#include <stdexcept>
#include <cstring>
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
	try{
	cout << length << endl;
	if (length == 0) { throw length_error("zero"); }
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
	} catch (const length_error e) {
		if (strcmp(e.what(), "zero") == 0) {
			cerr << "There is no data passed in";
		}
		return;
	}
}

void Logger::writeData(double data[], int length) {
	try {
		if (length == 0) { throw length_error("zero"); }
		if (length != catagories) { throw length_error("matching"); }
		writeFile.open(filename, std::ios_base::app);
		cout << length << endl;
		for(int i = 0; i < length-1; i++)  {
			writeFile << data[i] << ", ";
		}
		writeFile << data[length - 1] << "\n";
		writeFile.close();
	} catch (const length_error e) {
		if (strcmp(e.what(), "matching") == 0) {
			cerr << "The number of arguments does not match the number of headers";
		}
		if (strcmp(e.what(), "zero") == 0) {
			cerr << "There is no data passed in";
		}
		return;
	}
}


Logger::~Logger() {
	// TODO Auto-generated destructor stub
}

