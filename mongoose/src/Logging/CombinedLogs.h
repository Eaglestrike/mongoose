#ifndef COMBINEDLOGS_H_
#define COMBINEDLOGS_H_

#if 1

#include <string>
#include <vector>
#include <iostream>
#include <stdio.h>
#include <fstream>
#include "Modules.h"
#include "Logger.h"


class CombinedLogs {
public:
	CombinedLogs();
	void addModule(RobotModule* module);
	int getVersion();
	void initializeFolder(std::string FolderName);
	void addHeaders();
	void update();
	void start();
	static void callUpdate(void *t);
private:
	std::string folderName;
	std::vector<Logger> logs;
	std::vector<RobotModule*> modules;
	int version;
	double waitTime;
	std::thread updateThread;

};

#endif


#endif /* COMBINEDLOGS_H_ */
