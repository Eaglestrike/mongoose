
#ifndef __ADXRS453Z
#define __ADXRS453Z

#include "WPILib.h"
#include <semaphore.h>

class ADXRS453Z: public SensorBase, public PIDSource{
public:
	ADXRS453Z(SPI::Port);
	ADXRS453Z(int);
	ADXRS453Z();
	~ADXRS453Z();
	double getAngle();
	double getAnglePerSecond();
	void accumulate();
	void reset();
	uint32_t query();

private:
	Notifier* accumulator;
	SPI* spi;
	Timer* timer;
	unsigned long lastTime;
	sem_t m_semaphore;
	double angle;

	static SPI::Port intToPort(int);
	static void callAccumulate(void*);
	void init(SPI::Port);
	uint32_t uint8_tTouint32_t(uint8_t*);
};



#endif

