/*
 * MantaCoreModule.h
 *
 *  Created on: Mar 8, 2015
 *      Author: Team 114
 */

#ifndef MANTACOREMODULE_H_
#define MANTACOREMODULE_H_

#include "WPILib.h"
#include "RobotModule.h"

class MantaCoreModule : public RobotModule {
public:
	MantaCoreModule(int relayPort, int solenoid);
	virtual ~MantaCoreModule();

	void on();
	void off();
	void reverse();
	void setPneumatics(bool on);

	void reset();
	void enable();
	void disable();

	std::vector<std::string> getLoggingHeader();
	std::vector<double> getLoggingData();

private:
	Victor* m_Winch;
	Solenoid* m_Solenoid;
};

#endif /* MANTACOREMODULE_H_ */
