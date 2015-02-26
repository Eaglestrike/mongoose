
#ifndef __ROBOT_MODULE_H__________
#define __ROBOT_MODULE_H__________

#include <string>
#include <thread>
#include <iostream>

#include "../Error/EaglestrikeError.h"

//class EaglestrikeError;

class RobotModule {
public:
	RobotModule(std::string);
	virtual ~RobotModule();

	void enable();
	void disable();
	void reset();
	double* getLoggingData();

	std::string getModuleName();
protected:
	std::string m_Module_Name;
	std::thread m_Error_Checking_Thread;
	bool m_Enabled;

	virtual void checkError();
	static void callCheckError(void*);
	virtual void handleFatalError();

};

#endif
