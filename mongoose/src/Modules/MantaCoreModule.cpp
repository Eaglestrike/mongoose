/*
 * MantaCoreModule.cpp
 *
 *  Created on: Mar 8, 2015
 *      Author: Team 114
 */

#include <Modules/MantaCoreModule.h>

MantaCoreModule::MantaCoreModule(int relayPort, int solenoid) : RobotModule("Mantacore") {
	// TODO Auto-generated constructor stub
	m_Winch = new Relay(relayPort);
	m_Solenoid = new Solenoid(solenoid);
}

void MantaCoreModule::reset()  {
	RobotModule::reset();
}

void MantaCoreModule::disable() {
	RobotModule::disable();
}

void MantaCoreModule::enable() {
	RobotModule::enable();
}
void MantaCoreModule::on() {
	if(!m_Enabled) return;
	m_Winch->Set(Relay::kForward);
	//m_Winch->Set(Relay::kOn);
}

void MantaCoreModule::off() {
	if(!m_Enabled) return;

	m_Winch->Set(Relay::kOff);
}

void MantaCoreModule::reverse() {
	if(!m_Enabled) return;

	m_Winch->Set(Relay::kReverse);
	//m_Winch->Set(Relay::kOn);
}

void MantaCoreModule::setPneumatics(bool on) {
	m_Solenoid->Set(on);
}

MantaCoreModule::~MantaCoreModule() {
	// TODO Auto-generated destructor stub
}

