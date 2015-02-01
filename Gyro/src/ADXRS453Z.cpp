/*
 * ADXRS453Z.cpp
 *
 *  Created on: Jan 31, 2015
 *      Author: Team 114
 */

#include "ADXRS453Z.h"


ADXRS453Z::ADXRS453Z(SPI::Port port): lastTime(0){
	spi = new SPI(port);
	accumulator = new Notifier(ADXRS453Z::callAccumulate, this);
	timer = new Timer();

	spi->SetChipSelectActiveHigh();
	spi->SetClockRate(5);

}

void ADXRS453Z::init(){
	spi->SetChipSelectActiveLow();
	Wait(0.1);
	uint32_t spiResult;
	uint8_t send[] = {0x20, 0x00, 0x00, 0x03};
	uint8_t* recv;
	spi->Transaction(send, recv, 4);
}

void ADXRS453Z::callAccumulate(void* adx){
	ADXRS453Z *a = (ADXRS453Z*)adx;
	a->accumulate();
}

void ADXRS453Z::accumulate(){
	CRITICAL_REGION()
}


