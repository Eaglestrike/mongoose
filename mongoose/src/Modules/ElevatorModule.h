/*
 * ElevatorModule.h
 *
 *  Created on: Feb 12, 2015
 *      Author: Team 114
 */

#ifndef ELEVATORMODULE_H_
#define ELEVATORMODULE_H_

#include <WPILib.h>
#include "Modules/RobotModule.h"
#include "Peripherals/SafeTalonSRX.h"
#include "Settings.h"

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
		//Cole wuz here
	}

	void Set(float power){
		m_Motor_1->Set(power);
		m_Motor_2->Set(power);
	}

	double Get(){
		return m_Motor_1->Get();
	}

private:
	SafeTalonSRX* m_Motor_1;
	SafeTalonSRX* m_Motor_2;
};

class ElevatorModule: public RobotModule {
public:
	ElevatorModule(int motorPort1, int motorPort2, int safetyButtonPort, int encoderA, int encoderB);
	~ElevatorModule();
	void enable();
	void disable();
	void reset();
	void checkError();
	void handleFatalError();
	void calibrate();
	void setPosition(double height);
	void setPower(double power);
	void setPID(double p, double i, double d);

	bool getButton();
	double Get();

private:
	SafeTalonSRX* m_Motor_1;
	SafeTalonSRX* m_Motor_2;
	DigitalInput* m_SafteyButton;
	DualMotor* m_Lifter;
	Encoder* m_Encoder;
	PIDController* m_PIDController;

};


#endif /* ELEVATORMODULE_H_ */
