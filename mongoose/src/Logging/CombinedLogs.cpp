/*
 * CombinedLogs.cpp
 *
 *  Created on: Feb 26, 2015
 *      Author: Nathan
 */

#include "CombinedLogs.h"
#if 1

CombinedLogs::CombinedLogs() {
	version = getVersion();
	std::string folderName = "log" + std::to_string(version);
	initializeFolder(folderName);
}

void CombinedLogs::addModule(RobotModule* module) {
	std::string filePath = folderName + "/" + module->getModuleName();
	Logger log(filePath);
	logs.push_back(log);
	modules.push_back(module);
}

int CombinedLogs::getVersion() {
	std::ifstream versionLogRead;
	std::ofstream versionLogWrite;
	versionLogRead.open("version.txt");
	std::string stringNum;
	getline(versionLogRead, stringNum);
	version = stoi(stringNum); //Reads from the file to get version

	versionLogWrite.open("version.txt");
	versionLogWrite << std::to_string(version + 1); //Writes the next version to the file
	return version;
}

void CombinedLogs::initializeFolder(std::string folderName) {
	std::string command = "mkdir \"/home/lvuser/" + folderName + "\"";
	system(command.c_str());
}

void CombinedLogs::addHeaders() {
	for (int i = 0; i < logs.size(); i++) {
		logs[i].writeHeader(modules[i]->getLoggingHeader());
	}
}

void CombinedLogs::update() {
	for (int i = 0; i < logs.size(); i++) {
		logs[i].writeData(modules[i]->getLoggingData());
	}
}

#endif
