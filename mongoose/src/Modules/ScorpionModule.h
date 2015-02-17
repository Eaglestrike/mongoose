#include <WPILib.h>
#include "RobotModule.h"

class ScorpionModule : public RobotModule {
public:
	ScorpionModule(int solenoid);
	void Set(bool en);
	~ScorpionModule();
	
private:
	/* Hardware */
	Solenoid* m_solenoid;
	
};
