/*
 * server.cpp
 *
 *  Created on: Mar 4, 2015
 *      Author: Ben
 */

#include "server.hpp"


server::server(int port):
	portno(port),
	header("HTTP/1.1 200 OK\r\nServer: MJPG/1.0\r\nAccept-Range: bytes\r\nConnection: close\r\nContent-Type: multipart/x-mixed-replace; boundary=mjpegstream\r\n\r\n")
{

	printf("server()\n");

	parameters.push_back(CV_IMWRITE_JPEG_QUALITY);
	parameters.push_back(100);

	printf("socket()\n");

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd < 0){
		printf("sockfd < 0\n");
		exit(-1);
	}


	printf("bzero()\n");
	bzero((char*) &serv_addr, sizeof(serv_addr));

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(portno);
	serv_addr.sin_addr.s_addr = INADDR_ANY;

	printf("bind()\n");

	if(bind(sockfd, (struct sockaddr*) &serv_addr, sizeof(serv_addr)) < 0){
		printf("bind < 0\n");
		exit(-2);
	}

	printf("listen()\n");
	listen(sockfd, 5);

	printf("std::thread()\n");
	waitThread = std::thread(server::callWaitAndListen, this);

	printf("server() end\n");

	waitThread.join();

}

void server::callWaitAndListen(void* t){
	printf("server::callWaitAndListen()\n");
	((server*)t)->waitAndListen();
}
void server::waitAndListen(){
	printf("server::waitAndListen()\n");
	while(true){
		printf("sizeof()\n");
		clilen = sizeof(cli_addr);
		printf("accept()\n");
		newsockfd = accept(sockfd, (struct sockaddr*) &cli_addr, &clilen);
		if(newsockfd < 0){
			printf("newsockfd < 0!\n");
			exit(-3);
		}

		printf("spwaing new trhead\n");
		pthread_create(&threads[numThreads], NULL, server::callHandleClient, this);
		numThreads++;
	}
}

void* server::callHandleClient(void* t){
	printf("server::callHandleClient()\n");
	((server*)t)->handleClient();
	return 0;
}

void server::handleClient(){
	printf("asdfasdfasdf\n");
}

std::vector<uchar> server::matToJpeg(const cv::Mat& image){
	std::vector<uchar> jpeg;
//	cv::imencode(".jpg", image, jpeg, parameters);
	return jpeg;
}

void server::setImage(cv::Mat image){
	this->image = matToJpeg(image);
}



