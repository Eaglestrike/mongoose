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
using namespace std;

#if 0
string folderName;
vector<Logger> logs;
int version;

CombinedLogs::CombinedLogs() {
	version = getVersion();
	versionLog << to_string(version + 1);
	folderName = "log" + stringNum;
	initializeFolder(folderName);
}

void addModule(RobotModule module) {
	string filePath = folderName + "/" + module.getModuleName();
	Logger log = new Logger(filePath);
}

int getVersion() {
	ofstream versionLog;
	versionLog.open("version.txt");
	string stringNum >> getline(versionLog);
	version = stoi(versionLog);
	return version;
}

void initializeFolder(char* folderName) {
	char* command = 'mkdir\"' + folderName + '\"';
	system(command);
}


#endif
