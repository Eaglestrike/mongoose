/*
 * CombinedLogs.cpp
 *
 *  Created on: Feb 26, 2015
 *      Author: Nathan
 */
#include <iostream>
#include <stdio.h>
#include <fstream>
#include <string>
#include <vector>
#include "Modules.h"
using namespace std;

#if 1
string folderName;
vector<Logger> logs;
vector<RobotModule*> modules;
int version;

CombinedLogs::CombinedLogs() {
	version = getVersion();
	char* stringNum = std::to_string(version);
	char* folderName = 'log' + stringNum;
	initializeFolder(folderName);
}

void addModule(RobotModule* module) {
	string filePath = folderName + "/" + module->getModuleName();
	Logger log = new Logger(filePath);
	logs.push_back(log);
	modules.push_back(module);
}

int getVersion() {
	ifstream versionLogRead;
	ofstream versionLogWrite;
	versionLogRead.open("version.txt");
	string stringNum;
	getline(versionLogRead, stringNum);
	version = stoi(stringNum); //Reads from the file to get version

	versionLogWrite.open("version.txt");
	versionLogWrite << to_string(version + 1); //Writes the next version to the file
	return version;
}

void initializeFolder(char* folderName) {
	char* command = 'mkdir\"' + folderName + '\"';
	system(command);
}

void addHeaders() {
	for (int i = 0; i < logs.size(); i++) {
		logs[i].writeHeader(modules[i]->getLoggingHeader())
	}
}

void update() {
	for (int i = 0; i < logs.size(); i++) {
		logs[i].writeData(modules[i]->getLoggingData());
	}
}

#endif
