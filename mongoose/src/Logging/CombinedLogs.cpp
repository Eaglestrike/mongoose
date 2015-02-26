/*
 * CombinedLogs.cpp
 *
 *  Created on: Feb 26, 2015
 *      Author: Nathan
 */
#include <iostream>
#include <string>
#include <vector>
using namespace std;

string folderName;
vector<Logger> logs;

CombinedLogs::CombinedLogs() {

}

void addModule(RobotModule module) {
	string filePath = folderName + "/" + module.getModuleName();
	Logger log = new Logger(filePath);
}
