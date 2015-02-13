#include <assert.h>
#include <math.h>
#include "ScorpionModule.h"

ScorpionModule::ScorpionModule(int solenoid) :
RobotModule("Scorpion"),
m_solenoid(solenoid)
{
	/* Constructor */
}

void ScorpionModule::pistonRetract() {
	m_solenoid.Set(false);
}

void ScorpionModule::pistonExtend() {
	m_solenoid.Set(true);
}

void ScorpionModule::control() {
	
}

ScorpionModule::~ScorpionModule() {
	/* Destructor */
}

