/*
 * HUDServer.cpp
 *
 *  Created on: Mar 25, 2015
 *      Author: LAHS
 */

#include <Peripherals/HUD/HUDServer.h>

HUDServer::HUDServer(int portno, ArmModule* arm, ElevatorModule* elev) {
	// TODO Auto-generated constructor stub
	std::cout << "before";
	this->armInstance = arm;
	this->elevInstance = elev;
	std::cout << "Test";
	t = std::thread(send, this, portno);

}
void HUDServer::send(void* v, int port) {
	((HUDServer*) v)->callSend(port);

}

void HUDServer::callSend(int portno) {
	while (true) {
		int sockfd, newsockfd, n;
		std::cout << "initialized sockfd, new sockfd, n" << std::endl;
		socklen_t clilen;
		std::cout << "initialized clilen" << std::endl;
		struct sockaddr_in serv_addr, cli_addr;
		std::cout << "sockaddr" << std::endl;
		sockfd = socket(AF_INET, SOCK_STREAM, 0); //create socket
		std::cout << "create socket" << std::endl;
		if (sockfd < 0) //if any errors occur
			std::cout << "ERROR opening socket" << std::endl;
		serv_addr.sin_family = AF_INET; //setting the family of the socket
		std::cout << "setting family" << std::endl;
		serv_addr.sin_port = htons(portno); //setting the port number
		std::cout << "setting port number" << std::endl;
		serv_addr.sin_addr.s_addr = INADDR_ANY; //making it accept connections on any ip that points to it.
		if (!bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
			std::cout << "ERROR on binding" << std::endl;
		listen(sockfd, 5); //actually listening on the socket now

		std::cout << "listening" << std::endl;
		clilen = sizeof(cli_addr);
		newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen); //accept client connection
		std::cout << "listening" << std::endl;

		if (newsockfd < 0) //error checking
			std::cout << "ERROR on accept" << std::endl;
		std::cout << "listening" << std::endl;
		while (true) { //infinite loops :D
//			int err;
//			int sizeerr = sizeof(err);
//			int ret = getsockopt(sock, SOL_SOCKET, SO_ERROR, &err, &sizeerr);
//			if (ret) {
//				std::cout << "HUD disconnected\n";
//				break;
//			}

			elevcalibratestatus = elevInstance->hasCalibrated();
			armcalibratestatus = armInstance->hasCalibrated();
			if (armstatus == true) {
				armstring = "True";
			} else {
				armstring = "False";
			}
			if (elevatorstatus == true) {
				elevatorstring = "True";
			} else {
				elevatorstring = "False";
			}
			if (armcalibratestatus == true) {
				armcalibratestring = "True";
			} else {
				armcalibratestring = "False";
			}
			if (elevcalibratestatus == true) {
				elevcalibratestring = "True";
			} else {
				elevcalibratestring = "False";
			}
			std::string time= std::to_string(DriverStation::GetInstance()->GetMatchTime());
			std::string msg = armcalibratestring +" "+elevcalibratestring+ " " + time + " \n";
			n = write(newsockfd, msg.c_str(), msg.length()); //send needed data

			if(n < 0)
				break;

			Wait(1);
		}
		close(newsockfd);
		close(sockfd);
	}
}

void HUDServer::updateArm(bool armstat) {
	armstatus = armstat;
}

void HUDServer::updateElevator(bool elevatorstat) {
	elevatorstatus = elevatorstat;
}

HUDServer::~HUDServer() {
	// TODO Auto-generated destructor stub
}
