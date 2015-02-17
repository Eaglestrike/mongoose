/*
 * IntakeModule.h
 *
 *  Created on: Feb 13, 2015
 *      Author: Team 114
 */

#ifndef INTAKEMODULE_H_
#define INTAKEMODULE_H_

#include "WPILib.h"
#include "RobotModule.h"

class IntakeModule: public RobotModule {
private:
	Solenoid* m_Solenoid_1;
	Solenoid* m_Solenoid_2;
	TalonSRX* m_Motor_1;
	Victor* m_Motor_2;

public:
	IntakeModule(int, int, int, int);
	virtual ~IntakeModule();
	void extend();
	void retract();
	void intake(double power);

	void enable();
	void disable();
	void reset();

};

#endif /* INTAKEMODULE_H_ */
