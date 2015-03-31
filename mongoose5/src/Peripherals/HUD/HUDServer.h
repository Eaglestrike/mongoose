/*
 * HUDServer.h
 *
 *  Created on: Mar 25, 2015
 *      Author: LAHS
 */

#ifndef SRC_PERIPHERALS_HUD_HUDSERVER_H_
#define SRC_PERIPHERALS_HUD_HUDSERVER_H_
#include "Modules/ArmModule.h"
#include "Modules/ElevatorModule.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
#include "WPILib.h"
#include <thread>
#include <unistd.h>
#include "DriverStation.h"

class ArmModule;

class HUDServer {
public:
	HUDServer(int, ArmModule*, ElevatorModule*);
	virtual ~HUDServer();
	void updateElevator(bool);
	void updateArm(bool);
	void callSend(int);
	static void send(void*, int);
	static HUDServer* getInstance();
private:
	std::thread t;
	bool armstatus = false, elevatorstatus = false, elevcalibratestatus=false, armcalibratestatus=false;
	std::string armstring, elevatorstring, elevcalibratestring, armcalibratestring;
	ArmModule* armInstance;
	ElevatorModule* elevInstance;
	int matchtime = 0;

};

#endif /* SRC_PERIPHERALS_HUD_HUDSERVER_H_ */
