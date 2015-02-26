
#ifndef __SCORPION_H
#define __SCORPION_H

#include "RobotModule.h"
#include <WPILib.h>

class ScorpionModule : public RobotModule {
public:
	ScorpionModule(int solenoid);
	void Set(bool en);
	~ScorpionModule();
	
private:
	/* Hardware */
	Solenoid* m_solenoid;
	
};

#endif
