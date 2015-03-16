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
	m_Drive->setAngleOutputRange(-.75, .75);
	m_Drive->reset();
	m_Drive->enablePID();
	m_Drive->setAngleSetpoint(angle);
	Timer* time = new Timer();
	int in = 0;
	while(time->Get() < .2) {
		m_Drive->setPower(m_Drive->getAngleOutput(), -m_Drive->getAngleOutput());
		if(in % 1000  == 0)
			std::cout<< "gyro angle: "<< m_Drive->getAngle() << std::endl;
		if(abs(m_Drive->getAngleError()) < 8.5) {
			time->Start();
		}
		else {
			time->Reset();
		}
		in++;
		Wait(0.01);
	}
	m_Drive->setPower(0,0);
	m_Drive->reset();
	m_Drive->disablePID();
	m_Drive->setAngleOutputRange(-1, 1);
}


void AutonomousCommandBase::move(DistanceProfile* path) {
	m_Drive->reset();
	m_Drive->enablePID();
	m_Drive->setAngleSetpoint(0);
	runDistanceProf(path);
	m_Drive->reset();
	m_Drive->disablePID();

}

void AutonomousCommandBase::move(double distance, double totalTime) {
	DistanceProfile* path;
	if(distance >= 0)
		path = new DistanceProfile(0, distance, totalTime);
	else {
		path = new DistanceProfile(-distance, 0, totalTime);
	}
	move(path);
}

void AutonomousCommandBase::runDistanceProf(DistanceProfile* path) {
	Timer* time = new Timer();
	time->Start();
	int i = 0;
	while(!path->isDone) {
		m_Drive->setDriveSetpoint(path->getSetPoint(time->Get()));
		m_Drive->setPower(m_Drive->getDriveOutput() + m_Drive->getAngleOutput(), m_Drive->getDriveOutput() - m_Drive->getAngleOutput());
//		if(i%50 == 0)
			std::cout << "time: " << time->Get() <<  " driveOutput: " << m_Drive->getDriveOutput() << " angelout: " << m_Drive->getAngleOutput() << " sp: " << path->getSetPoint(time->Get()) << std::endl;
		i++;
		Wait(0.01);
	}
	time->Stop();
	m_Drive->setPower(0,0);
}

AutonomousCommandBase::~AutonomousCommandBase() {
	// TODO Auto-generated destructor stub
}

void AutonomousCommandBase::callSyncMove(void* v, DistanceProfile* path) {
	((AutonomousCommandBase*)(v))->move(path);
}

void AutonomousCommandBase::syncMove(DistanceProfile* path) {
	std::thread t(AutonomousCommandBase::callSyncMove, path);
}
