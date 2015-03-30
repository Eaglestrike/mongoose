/*
 * SafeVictor.h
 *
 *  Created on: Feb 12, 2015
 *      Author: Team 114
 */

#ifndef SAFEVICTOR_H_
#define SAFEVICTOR_H_

#include "WPILib.h"

class SafeVictor: public Victor{

public:
	SafeVictor(int victorPort, DigitalInput* button, bool reverse = false);
	~SafeVictor();
	void Set(float, uint8_t);
	bool getButton();
private:
	bool m_Reverse;
	DigitalInput* m_Safety_Button;
};


#endif /* SAFEVICTOR_H_ */
