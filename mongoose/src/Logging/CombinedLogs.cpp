/*
 * CombinedLogs.cpp
 *
 *  Created on: Feb 26, 2015
 *      Author: Nathan
 */
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

#if 0
string folderName;
vector<Logger> logs;
int version;

CombinedLogs::CombinedLogs() {
	ofstream versionLog;
	versionLog.open("version.txt");
	string stringNum = versionLog.getline();
	//Parse Version

	string versionString = "log" + version;
	system("mkdir \"versionString\"");
}

void addModule(RobotModule module) {
	string filePath = folderName + "/" + module.getModuleName();
	Logger log = new Logger(filePath);
}

int getVersion() {

}

#endif
