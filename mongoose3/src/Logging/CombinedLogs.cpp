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

	struct stat info;
//	std::cout << stat(folderName.c_str() + '/logs/', &info) << std::endl;
//	if (stat(folderName.c_str() + '/logs/', &info) == -1) {
//		std::string command = "mkdir \"" + folderName + "/logs/" + "\"";
//			system(command.c_str());
//	}

	std::cout << "Getting Version" << std::endl;
	version = getVersion();
	std::cout << "Initializing Log Folder" << std::endl;
	logFolder = "log" + std::to_string(version);
	initializeFolder(folderName);
	std::cout << "Log Initialized" << std::endl;

}

bool CombinedLogs::checkUSB(){
	struct stat info;
	return !(stat(USB_DIRECTORY, &info) != 0 || !(info.st_mode & S_IFDIR));
}

void CombinedLogs::addModule(RobotModule* module) {
	std::string filePath = folderName + "/logs/" + logFolder + "/" + module->getModuleName() + ".csv";
	std::cout << filePath << std::endl;
	Logger log(filePath);
	logs.push_back(log);
	modules.push_back(module);
}

int CombinedLogs::getVersion() {
	std::ifstream versionLogRead;
	std::ofstream versionLogWrite;
	versionLogRead.open(folderName + "/logs" + logFolder +"/version.txt");
	std::string stringNum;
	getline(versionLogRead, stringNum);
	if (stringNum == "") {
		version = 0;
		std::cout << "Nothing in version.txt. Initializing as 0" << std::endl;
	} else {
		version = stoi(stringNum); //Reads from the file to get version
	}

	versionLogWrite.open(folderName + "/logs" + "/version.txt");
	versionLogWrite << std::to_string(version + 1) << std::endl; //Writes the next version to the file
	return version;
}

void CombinedLogs::initializeFolder(std::string folderName) {
	std::string command = "mkdir \"" + folderName + "/logs/" + logFolder + "\"";
	system(command.c_str());
}

void CombinedLogs::addHeaders() {
	std::cout << "Adding Headers" << std::endl;
	for (int i = 0; i < logs.size(); i++) {
		if (modules[i]->getLoggingHeader().empty()) {
			logs[i].writeHeader(modules[i]->getLoggingHeader());
		}
	}
	std::cout << "Added Headers" << std::endl;
}

void CombinedLogs::update() {
	for (int i = 0; i < logs.size(); i++) {
		if (modules[i]->getLoggingData().empty()) {
			logs[i].writeData(modules[i]->getLoggingData());
		}
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
