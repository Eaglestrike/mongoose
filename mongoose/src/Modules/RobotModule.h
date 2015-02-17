#ifndef __ROBOT_MODULE_H__
#define __ROBOT_MODULE_H__

#include <string>
#include <thread>
#include <iostream>

class RobotModule {
public:
	RobotModule(std::string);
	~RobotModule();

	void enable();
	void disable();
	void reset();
	double* getLoggingData();
protected:
	bool m_Enabled;
	std::string m_Module_Name;
	std::thread m_Error_Checking_Thread;

	void checkError();
	static void callCheckError(void*);

};

#endif
