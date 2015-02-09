#include "ArmModule.h"
#include <assert.h>
#include <math.h>

ScorpionModule::ScorpionModule(int solenoid, int motorA) :
RobotModule("ScorpionModule"),
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

