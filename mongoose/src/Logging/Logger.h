/*
 * Logger.h
 *
 *  Created on: Jan 22, 2015
 *      Author: Nathan
 */

#ifndef LOGGER_H_
#define LOGGER_H_
#include <iostream>
#include <string>
using namespace std;

class Logger {
public:
	Logger(char*);
	virtual ~Logger();
	void writeHeader(string[], int);
	void writeData(double[], int);
};

#endif /* LOGGER_H_ */
