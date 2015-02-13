#ifndef __ROBOT_MODULE_H__
#define __ROBOT_MODULE_H__

#include <string>

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

};

#endif
