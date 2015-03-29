/*
 * HUDServer.h
 *
 *  Created on: Mar 25, 2015
 *      Author: LAHS
 */

#ifndef SRC_PERIPHERALS_HUD_HUDSERVER_H_
#define SRC_PERIPHERALS_HUD_HUDSERVER_H_
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
#include <unistd.h>
#include <thread>
#include "WPILib.h"

class HUDServer {
public:
	HUDServer(int);
	virtual ~HUDServer();
	void updateStatus(bool, bool);
	void updateArm(bool);
	void updateElevator(bool);
	static void send(void*, int);
	void callSend(int);
	std::thread t;
};

#endif /* SRC_PERIPHERALS_HUD_HUDSERVER_H_ */
