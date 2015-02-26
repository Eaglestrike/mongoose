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
#include <vector>
using namespace std;

class Logger {
public:
	Logger(char*);
	virtual ~Logger();
	void writeHeader(vector<string>);
	void writeData(vector<double>);
};

#endif /* LOGGER_H_ */
