/*
 * HUDServer.cpp
 *
 *  Created on: Mar 25, 2015
 *      Author: LAHS
 */

#include <Peripherals/HUD/HUDServer.h>
bool armstatus, elevatorstatus;
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
int HUDServer::updateStatus(bool armstat, bool elevatorstat){
	armstatus = armstat;
	elevatorstatus = elevatorstat;
	return 0;
}
HUDServer::~HUDServer() {
	// TODO Auto-generated destructor stub
}

