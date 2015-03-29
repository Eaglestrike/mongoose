
#include "ScorpionModule.h"

ScorpionModule::ScorpionModule(int solenoid) :
RobotModule("Scorpion")
{
	m_solenoid = new Solenoid(solenoid);
	/* Constructor */
}

void ScorpionModule::Set(bool en){
	m_solenoid->Set(en);
}

ScorpionModule::~ScorpionModule() {
	/* Destructor */
}

