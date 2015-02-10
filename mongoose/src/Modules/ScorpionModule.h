#include "WPILib.h"
#include "RobotModule.h"

class ScorpionModule : public RobotModule {
public:
	ScorpionModule(int solenoid);
	void enable(bool en = true);
	~ScorpionModule();
	
private:
	void control();
	void pistonRetract();
	void pistonExtend();
	/* Hardware */
	Solenoid m_solenoid;
	
};
