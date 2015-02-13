/*
 * ElevatorModule.h
 *
 *  Created on: Feb 12, 2015
 *      Author: Team 114
 */

#ifndef ELEVATORMODULE_H_
#define ELEVATORMODULE_H_

#include <WPILib.h>

class DualMotor: public PIDOutput{
public:
	DualMotor(SafeTalonSRX* motor1, SafeTalonSRX* motor2){
		m_Motor_1 = motor1;
		m_Motor_2 = motor2;
	}
	virtual ~DualMotor(){}

	void PIDWrite(float output){
		m_Motor_1->PIDWrite(output);
		m_Motor_2->PIDWrite(output);
	}

private:
	SafeTalonSRX* m_Motor_1;
	SafeTalonSRX* m_Motor_2;
};

class ElevatorModule: public RobotModule{
public:
	ElevatorModule(int motorPort1, int motorPort2, int safetyButtonPort);
	~ElevatorModule();
	void enable();
	void disable();
	void reset();

	void calibrate();
	void setPosition(double height);

private:
	SafeTalonSRX* m_Motor_1;
	SafeTalonSRX* m_Motor_2;
	DigitalInput* m_SafteyButton;

};


#endif /* ELEVATORMODULE_H_ */
