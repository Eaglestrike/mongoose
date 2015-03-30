/*
 * SafeTalon.h
 *
 *  Created on: Feb 12, 2015
 *      Author: Team 114
 */

#ifndef SAFETALON_H_
#define SAFETALON_H_

#include "WPIlib.h"
#include <iostream>

class SafeTalonSRX: public TalonSRX{

public:
	SafeTalonSRX(int talonSRXPort, DigitalInput* button, bool reverse = false);
	~SafeTalonSRX();
	void Set(float, uint8_t syncGroup=0);
	bool getButton();
private:
	bool m_Reverse;
	DigitalInput* m_Safety_Button;
};




#endif /* SAFETALON_H_ */
