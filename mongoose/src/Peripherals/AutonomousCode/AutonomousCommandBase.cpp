/*
 * AutonomousCommandBase.cpp
 *
 *  Created on: Feb 26, 2015
 *      Author: Giggles
 */

#include "AutonomousCommandBase.h"

AutonomousCommandBase::AutonomousCommandBase(DriveModule* drive) {
	// TODO Auto-generated constructor stub
	m_Drive = drive;
	m_Drive->enable();
	m_Drive->reset();

}

void AutonomousCommandBase::turnAngle(double angle) {
	m_Drive->reset();
	m_Drive->enablePID();
	m_Drive->setAngleSetpoint(angle);
	Timer* time = new Timer();
	while(time->Get() < .2) {
		m_Drive->setPower(m_Drive->getAngleOutput(), -m_Drive->getAngleOutput());
		if(in % 100000  == 0)
			std::cout<< "gyro angle: "<< m_Drive->getAngle() << std::endl;
		if(abs(m_Drive->getAngleError()) < m_Drive->getAngleSetpoint()*5/360 ) {
			time->Start();
		}
		else {
			time->Reset();
		}
	}
	m_Drive->reset();
	m_Drive->disablePID();

}


void AutonomousCommandBase::move(DistanceProfile* path) {
	m_Drive->reset();
	m_Drive->enablePID();
	m_Drive->setAngleSetpoint(0);
	runDistanceProf(path);
	m_Drive->reset();
	m_Drive->disablePID();

}

void AutonomousCommandBase::runDistanceProf(DistanceProfile* path) {
	Timer* time = new Timer();
	time->Start();
	while(!prof->isDone) {
		m_Drive->setDriveSetpoint(prof->getSetPoint(time->Get()));
		m_Drive->setPower(m_Drive->getDriveOutput() + m_Drive->getAngleOutput(), m_Drive->getDriveOutput() - m_Drive->getAngleOutput());
		if(in % 100000 == 0)
			std::cout<< "renc: " << renc->Get() << " ;lenc:" << lenc->Get() << " ;gyro:" << gyro->getAngle() << " ;Setpoint: " << driveController->GetSetpoint() << std::endl;
		in++;
	}
	time->~Timer();
	m_Drive->setPower(0,0);
	if(in % 10 == 0)
		std::cout<< "renc: " << renc->Get() << " ;lenc:" << lenc->Get() << " ;gyro:" << gyro->getAngle() << " ;Setpoint: " << driveController->GetSetpoint() << std::endl;
	in++;
}

AutonomousCommandBase::~AutonomousCommandBase() {
	// TODO Auto-generated destructor stub
}


