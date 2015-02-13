/*
 * ElevatorModule.cpp
 *
 *  Created on: Feb 12, 2015
 *      Author: Team 114
 */

#include "ElevatorModule.h"

ElevatorModule::ElevatorModule(int motorPort1, int motorPort2, int safteyButtonPort): RobotModule("Elevator"){
	m_SafteyButton = new DigitalInput(safteyButtonPort);
	m_Motor_1 = new SafeTalonSRX(motorPort1, m_SafteyButton);
	m_Motor_2 = new SafeTalonSRX(motorPort2, m_SafteyButton);
}
//Cole Was here

ElevatorModule::~ElevatorModule(){

}


void ElevatorModule::Enable(){
	RobotModule::enable();
}

void ElevatorModule::Disable(){
	RobotModule::disable();

	m_Motor_1->Disable();
	m_Motor_2->Disable();
}

void ElevatorModule::setPosition(double height){

}


