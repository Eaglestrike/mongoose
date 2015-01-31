
#ifndef __ADXRS453Z
#define __ADXRS453Z

#include "WPILib.h"

class ADXRS453Z: public SensorBase, public PIDSource{
public:
	ADXRS453Z(SPI::Port);
	ADXRS453Z(int);
	ADXRS453Z();
	~ADXRS453Z();
	double getAngle();
	double getAnglePerSecond();
	uint32_t getRawSPIData();
	void reset();
private:
	Notifier* accumulator;
	SPI* spi;
	Timer* timer;
	unsigned long lastTime;

	static void callAccumulate(void*);
	void accumulate();

	void init();
};



#endif

