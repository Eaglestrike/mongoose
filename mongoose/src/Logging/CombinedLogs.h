#ifndef COMBINEDLOGS_H_
#define COMBINEDLOGS_H_

class CombinedLogs {
public:
	CombinedLogs();
	void addModule(RobotModule* module);
	int getVersion();
	void initializeFolder(char* FolderName);
	void addHeaders();
	void update();
};


#endif /* COMBINEDLOGS_H_ */
