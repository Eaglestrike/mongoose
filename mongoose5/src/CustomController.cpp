/*
 * CustomController.cpp
 *
 *  Created on: Mar 15, 2015
 *      Author: Team 114
 */

#include <CustomController.h>

CustomController::CustomController(int port) : Joystick(port) {
	// TODO Auto-generated constructor stub

}

CustomController::~CustomController() {
	// TODO Auto-generated destructor stub
}

bool CustomController::getLevel0() {
	return GetRawButton(1);
}

bool CustomController::getLevel1() {
	return GetRawButton(2);
}

bool CustomController::getLevel2() {
	return GetRawButton(3);
}

bool CustomController::getLevel3() {
	return GetRawButton(4);
}

bool CustomController::getLevel4() {
	return GetRawButton(5);
}

bool CustomController::getLevel5() {
	return GetRawButton(6);
}

bool CustomController::getLevel6() {
	return GetRawButton(7);
}


bool CustomController::grabTote() {
	return GetRawButton(10);
}

bool CustomController::grabContainer() {
	return GetRawButton(9);
}

bool CustomController::open() {
	return GetRawButton(8);
}

bool CustomController::getMantaCorePneumatics() {
	return GetRawButton(17);
}

double CustomController::getRightX() {
	return GetRawAxis(3);
}

double CustomController::getLeftX() {
	return GetX();
}

double CustomController::getRightY() {
	return GetRawAxis(2);
}

double CustomController::getLeftY() {
	return GetY();
}

bool CustomController::getRight3() {
	return GetRawButton(19);
}

bool CustomController::getLeft3() {
	return GetRawButton(18);
}

bool CustomController::toggleIntake() {
	return GetRawButton(16);
}

bool CustomController::intake() {
	return GetRawButton(14);
}

bool CustomController::extake() {
	return GetRawButton(15);
}

bool CustomController::drop() {
	return GetRawButton(13);
}

bool CustomController::raise() {
	return GetRawButton(12);
}

bool CustomController::dropRelease() {
	return GetRawButton(11);
}
