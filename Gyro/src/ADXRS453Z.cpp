/*
 * ADXRS453Z.cpp
 *
 *  Created on: Jan 31, 2015
 *      Author: Team 114
 */

#include "ADXRS453Z.h"


ADXRS453Z::ADXRS453Z(SPI::Port port){
	init(port);
}

ADXRS453Z::ADXRS453Z(int port){
	init(intToPort(port));
}

ADXRS453Z::ADXRS453Z() : ADXRS453Z(SPI::Port::kOnboardCS0){

}

ADXRS453Z::~ADXRS453Z(){
	delete accumulator;
	delete spi;
	delete timer;
}

void ADXRS453Z::init(SPI::Port port){

	spi = new SPI(port);
	accumulator = new Notifier(ADXRS453Z::callAccumulate, this);
	timer = new Timer();
	lastTime = 0;
	angle = 0;

	sem_init(&m_semaphore, 0, 1);

	timer->Start();

	spi->SetChipSelectActiveHigh();
	spi->SetClockRate(5);
	spi->SetChipSelectActiveLow();

	Wait(0.1);

	uint8_t send[] = {0x20, 0x00, 0x00, 0x03};
	uint8_t* recv = 0;
	spi->Transaction(send, recv, 4);

	accumulator->StartPeriodic(0.005);

}

uint32_t ADXRS453Z::query(){

	spi->SetChipSelectActiveLow();
	uint8_t send[] = {0x20, 0x00, 0x00, 0x00};
	uint8_t recv[4];
	spi->Transaction(send, recv, 4);


	return uint8_tTouint32_t(recv);
}

double ADXRS453Z::getAngle(){
	return angle;
}

double ADXRS453Z::PIDGet(){
	return getAngle();
}

double ADXRS453Z::getAnglePerSecond(){
	return ((signed short)((query() >> 10) & 0xFFFF))/80.0 + adjustment;
}

void ADXRS453Z::reset(){
	timer->Reset();
	lastTime = 0;
	angle = 0;
}


void ADXRS453Z::callAccumulate(void* adx){

	ADXRS453Z *a = (ADXRS453Z*)adx;
	a->accumulate();
}

void ADXRS453Z::accumulate(){

	sem_wait(&m_semaphore);

	double time = timer->Get();
	angle += (time - lastTime) * getAnglePerSecond();
	lastTime = time;

	sem_post(&m_semaphore);

}

SPI::Port ADXRS453Z::intToPort(int port){
	switch(port){
		case 0: return SPI::Port::kOnboardCS0;
		case 1: return SPI::Port::kOnboardCS1;
		case 2: return SPI::Port::kOnboardCS2;
		case 3: return SPI::Port::kOnboardCS3;
		default: return SPI::Port::kOnboardCS0;
	}
}

uint32_t ADXRS453Z::uint8_tTouint32_t(uint8_t bytes[]){

	uint32_t ret = bytes[0];
	ret = ret << 8;
	ret += bytes[1];
	ret = ret << 8;
	ret += bytes[2];
	ret = ret << 8;
	ret += bytes[3];

	return ret;
}
