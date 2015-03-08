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
	parameters.push_back(CV_IMWRITE_JPEG_QUALITY);
	parameters.push_back(100);

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd < 0)
		exit(-1);

	bzero((char*) &serv_addr, sizeof(serv_addr));

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(portno);
	serv_addr.sin_addr.s_addr = INADDR_ANY;

	if(bind(sockfd, (struct sockaddr*) &serv_addr, sizeof(serv_addr)) < 0)
		exit(-2);

	listen(sockfd, 5);

	waitThread = std::thread(server::callWaitAndListen, this);

}

void server::callWaitAndListen(void* t){
	((server*)t)->waitAndListen();
}
void server::waitAndListen(){
	while(true){
		clilen = sizeof(cli_addr);
		newsockfd = accept(sockfd, (struct sockaddr*) &cli_addr, &clilen);
		if(newsockfd < 0)
			exit(-3);
		printf("spwaing new trhead\n");
		pthread_create(&threads, NULL, server::callHandleClient, NULL);
		threads++;
	}
}

void* server::callHandleClient(void* t){
	((server*)t)->handleClient();
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



