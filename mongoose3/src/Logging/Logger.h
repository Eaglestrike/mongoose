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
#include <stdio.h>
#include <fstream>
#include <cstdlib>
#include <exception>
#include <stdexcept>
#include <cstring>

#if 1

class Logger {
public:
	Logger(std::string);
	virtual ~Logger();
	void writeHeader(std::vector<std::string>);
	void writeData(std::vector<double>);
private:
	std::string filename;
	std::ofstream* writeFile;
	bool headed;
	int catagories;
};

#endif

#endif /* LOGGER_H_ */
