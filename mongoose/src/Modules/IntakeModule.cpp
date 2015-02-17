/*
 * IntakeModule.cpp
 *
 *  Created on: Feb 13, 2015
 *      Author: Team 114
 */

#include "IntakeModule.h"

IntakeModule::IntakeModule(int solenoid1, int solenoid2, int motor1, int motor2):
RobotModule("Intake"){
	// TODO Auto-generated constructor stub
	m_Solenoid_1 = new Solenoid(solenoid1);
	m_Solenoid_2 = new Solenoid(solenoid2);
	m_Motor_1 = new TalonSRX(motor1);
	m_Motor_2 = new Victor(motor2);
}

IntakeModule::~IntakeModule() {
	// TODO Auto-generated destructor stub
}


void IntakeModule::extend(){
	m_Solenoid_1->Set(true);
	m_Solenoid_2->Set(true);
}

void IntakeModule::retract(){
	m_Solenoid_1->Set(false);
	m_Solenoid_2->Set(false);
}

void IntakeModule::intake(double power){
	m_Motor_1->Set(power);
	m_Motor_2->Set(-power);
}

void IntakeModule::enable(){
	RobotModule::enable();
}

void IntakeModule::disable(){
	RobotModule::disable();
	m_Motor_1->Disable();
	m_Motor_2->Disable();
}

void IntakeModule::reset(){
	RobotModule::reset();
}

