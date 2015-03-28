/*
 * CustomController.h
 *
 *  Created on: Mar 15, 2015
 *      Author: Team 114
 */

#ifndef CUSTOMCONTROLLER_H_
#define CUSTOMCONTROLLER_H_

#include "WPILib.h"

class CustomController : public Joystick {
public:
	CustomController(int port);
	virtual ~CustomController();

	bool getLevel0();
	bool getLevel1();
	bool getLevel2();
	bool getLevel3();
	bool getLevel4();
	bool getLevel5();
	bool getLevel6();
	bool grabTote();
	bool grabContainer();
	bool open();
	bool getMantaCorePneumatics();
	double getRightX();
	double getLeftX();
	double getRightY();
	double getLeftY();
	bool getRight3();
	bool getLeft3();
	bool toggleIntake();
	bool intake();
	bool extake();
	bool drop();
	bool raise();
	bool dropRelease();

};

#endif /* CUSTOMCONTROLLER_H_ */
