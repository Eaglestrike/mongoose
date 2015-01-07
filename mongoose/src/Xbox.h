
#ifndef XBOX_H
#define XBOX_H

#include "WPIlib.h"

class Xbox: public Joystick{

public:

	Xbox(int port);
	~Xbox(){};

	bool GetA();
	bool GetB();
	bool GetX();
	bool GetY();

	bool GetRB();
	bool GetLB();

	bool GetStart();
	bool GetBack();

	bool GetR3();
	bool GetL3();

	float GetLT();
	float GetRT();

	float GetRX();
	float GetRY();
	float GetLX();
	float GetLY();
	float GetPX();

};


#endif
