#include <iostream>
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
