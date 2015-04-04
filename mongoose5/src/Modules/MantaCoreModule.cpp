/*
 * MantaCoreModule.cpp
 *
 *  Created on: Mar 8, 2015
 *      Author: Team 114
 */

#include <Modules/MantaCoreModule.h>

MantaCoreModule::MantaCoreModule(int relayPort, int solenoid) : RobotModule("Mantacore") {
	// TODO Auto-generated constructor stub
//	m_Winch = new Relay(relayPort, Relay::kBothDirections);
	m_Winch = new Victor(9);
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
	m_Winch->Set(1);
}

void MantaCoreModule::off() {
	if(!m_Enabled) return;
	m_Winch->Set(0);
}

void MantaCoreModule::reverse() {
	if(!m_Enabled) return;
	m_Winch->Set(-1);
	//m_Winch->Set(Relay::kOn);
}

void MantaCoreModule::setPneumatics(bool on) {
	if(!m_Enabled) return;

	m_Solenoid->Set(on);
}

MantaCoreModule::~MantaCoreModule() {
	// TODO Auto-generated destructor stub
}

std::vector<std::string> MantaCoreModule::getLoggingHeader() {

	std::vector<std::string> header;
	header.push_back("solenoid_get");
	header.push_back("winch_get");

	return header;
}

std::vector<double> MantaCoreModule::getLoggingData() {

	std::vector<double> data;
	data.push_back(m_Solenoid->Get());
	data.push_back(m_Winch->Get());

	return data;

}

