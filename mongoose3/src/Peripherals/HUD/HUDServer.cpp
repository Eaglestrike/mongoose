/*
 * HUDServer.cpp
 *
 *  Created on: Mar 25, 2015
 *      Author: LAHS
 */

#include <Peripherals/HUD/HUDServer.h>
bool armstatus = false, elevatorstatus = false;
std::string armstring, elevatorstring;

void HUDServer::send(void* v, int port) {
	((HUDServer*)v)->callSend(port);

}

void HUDServer::callSend(int portno) {
	int sockfd, newsockfd, n;
	std::cout << "initialized sockfd, new sockfd, n" << std::endl;
	socklen_t clilen;
	std::cout << "initialized clilen" << std::endl;
	struct sockaddr_in serv_addr, cli_addr;
	std::cout << "sockaddr" << std::endl;
	sockfd = socket(AF_INET, SOCK_STREAM, 0); //create socket
	std::cout << "create socket" << std::endl;
	if (sockfd < 0) //if any errors occur
		std::cout<<"ERROR opening socket"<<std::endl;
	serv_addr.sin_family = AF_INET; //setting the family of the socket
	std::cout << "setting family" << std::endl;
	serv_addr.sin_port = htons(portno); //setting the port number
	std::cout << "setting port number" << std::endl;
	serv_addr.sin_addr.s_addr = INADDR_ANY; //making it accept connections on any ip that points to it.
	if (!bind(sockfd, (struct sockaddr *) &serv_addr,                   sizeof(serv_addr)) < 0)
		std::cout<<"ERROR on binding"<<std::endl;
	listen(sockfd,5); //actually listening on the socket now

	std::cout << "listening" <<std::endl;
	clilen = sizeof(cli_addr);
	newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen); //accept client connection
	std::cout << "listening" <<std::endl;

	if (newsockfd < 0) //error checking
		std::cout<<"ERROR on accept"<<std::endl;
	std::cout << "listening" <<std::endl;
	while(true){ //infinite loops :D
		if(armstatus==true){
			armstring = "True";
		}
		else{
			armstring = "False";
		}
		if(elevatorstatus==true){
			elevatorstring = "True";
		}
		else{
			elevatorstring = "False";
		}
		std::string msg = armstring + " " + elevatorstring + " \n";
		n = write(newsockfd, msg.c_str(), msg.length()); //send needed data
		std::cout << msg << std::endl;
		Wait(1);
	}
}

void HUDServer::updateStatus(bool armstat, bool elevatorstat){
	armstatus = armstat;
	elevatorstatus = elevatorstat;
}

void HUDServer::updateArm(bool armstat)  {
	armstatus = armstat;
}

void HUDServer::updateElevator(bool elevatorstat) {
	elevatorstatus = elevatorstat;
}

/*
 * HUDServer.cpp
 *
 *  Created on: Mar 25, 2015
 *      Author: LAHS
 */

#include <Peripherals/HUD/HUDServer.h>
HUDServer::HUDServer(int portno) {
	// TODO Auto-generated constructor stub
	int sockfd, newsockfd, n;
	socklen_t clilen;
	struct sockaddr_in serv_addr, cli_addr;
	sockfd = socket(AF_INET, SOCK_STREAM, 0); //create socket
	if (sockfd < 0) //if any errors occur
	  std::cout<<"ERROR opening socket"<<std::endl;
	serv_addr.sin_family = AF_INET; //setting the family of the socket
	serv_addr.sin_port = htons(portno); //setting the port number
	serv_addr.sin_addr.s_addr = INADDR_ANY; //making it accept connections on any ip that points to it.
	if (bind(sockfd, (struct sockaddr *) &serv_addr,                   sizeof(serv_addr)) < 0)
	  std::cout<<"ERROR on binding"<<std::endl;
	listen(sockfd,5); //actually listening on the socket now

	clilen = sizeof(cli_addr);
	newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen); //accept client connection
	if (newsockfd < 0) //error checking
	  std::cout<<"ERROR on accept"<<std::endl;
	while(true){ //infinite loops :D

		n = write(newsockfd, armstatus + " " + elevatorstatus,18); //send needed data
	}


}

HUDServer::~HUDServer() {
	// TODO Auto-generated destructor stub
}

