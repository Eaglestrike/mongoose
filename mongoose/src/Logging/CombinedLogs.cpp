/*
 * CombinedLogs.cpp
 *
 *  Created on: Feb 26, 2015
 *      Author: Nathan
 */

#include "CombinedLogs.h"
#if 1

CombinedLogs::CombinedLogs() {

	if(checkUSB())
		folderName = USB_DIRECTORY;
	else
		folderName = BACKUP_DIRECTORY;

	version = getVersion();
	std::string folderName = "log" + std::to_string(version);
	initializeFolder(folderName);
}

bool CombinedLogs::checkUSB(){
	struct stat info;
	return !(stat(USB_DIRECTORY, &info) != 0 || !(info.st_mode & S_IFDIR));
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
	versionLogRead.open("/media/sda1/version.txt");
	std::string stringNum;
	getline(versionLogRead, stringNum);
	if (stringNum == "") {
		version = 0;
	} else {
		version = stoi(stringNum); //Reads from the file to get version
	}

	versionLogWrite.open("version.txt");
	versionLogWrite << std::to_string(version + 1) << std::endl; //Writes the next version to the file
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

void CombinedLogs::start() {
	waitTime = .05;
	this->addHeaders();
	updateThread = std::thread(CombinedLogs::callUpdate, this);
}

void CombinedLogs::callUpdate(void* t) {
	while(true) {
		((CombinedLogs*)t)->update();
		Wait(((CombinedLogs*)t)->waitTime);
	}
}

#endif
