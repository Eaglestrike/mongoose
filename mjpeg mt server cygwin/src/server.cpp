/*
 * server.cpp
 *
 *  Created on: Mar 4, 2015
 *      Author: Ben
 */

#include "server.hpp"


server::server(const char* ip, int port, double d):
	ipaddr(ip),
	portno(port),
	delay(d),
	header("HTTP/1.1 200 OK\r\nServer: MJPG/1.0\r\nAccept-Range: bytes\r\nConnection: close\r\nContent-Type: multipart/x-mixed-replace; boundary=mjpegstream\r\n\r\n")
{

#if DEBUG
	printf("server()\n");
#endif

	setQuality(1);

#if DEBUG
	printf("socket()\n");
#endif

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd < 0){
		printf("sockfd < 0\n");
		exit(-1);
	}


	printf("bzero()\n");
	bzero((char*) &serv_addr, sizeof(serv_addr));

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(portno);
//	serv_addr.sin_addr.s_addr = INADDR_ANY;
	inet_pton(AF_INET, ip, &serv_addr.sin_addr);

#if DEBUG
	printf("bind()\n");
#endif

	if(bind(sockfd, (struct sockaddr*) &serv_addr, sizeof(serv_addr)) < 0){
		printf("can't bind to: %s\n", ip);
		exit(-2);
	}

#if DEBUG
	printf("listen()\n");
#endif

	listen(sockfd, 5);

#if DEBUG
	printf("std::thread()\n");
#endif

	waitThread = std::thread(server::callWaitAndListen, this);

#if DEBUG
	printf("server() end\n");
#endif

//	waitThread.join();

}

void server::setQuality(int i){
	parameters.clear();
	parameters.push_back(CV_IMWRITE_JPEG_QUALITY);
	parameters.push_back(i);
}

void server::setFrameRate(double d){
	delay = 1/d;
}

void server::join(){
	waitThread.join();
}

void server::callWaitAndListen(void* t){
#if DEBUG
	printf("server::callWaitAndListen()\n");
#endif
	((server*)t)->waitAndListen();
}
void server::waitAndListen(){
#if DEBUG
	printf("server::waitAndListen()\n");
#endif
	while(true){
#if DEBUG
		printf("sizeof()\n");
#endif
		clilen = sizeof(cli_addr);
#if DEBUG
		printf("accept()\n");
#endif
		newsockfd = accept(sockfd, (struct sockaddr*) &cli_addr, &clilen);
		if(newsockfd < 0){
			printf("newsockfd < 0!\n");
			exit(-3);
		}

#if DEBUG
		printf("spwaing new trhead\n");
#endif
		thread = (pthread_t*)malloc(sizeof(pthread_t));
		pthread_create(thread, NULL, server::callHandleClient, this);
#if DEBUG
		printf("after pthread_create\n");
#endif
		numThreads++;
	}
}

void* server::callHandleClient(void* t){
#if DEBUG
	printf("server::callHandleClient()\n");
#endif
	((server*)t)->handleClient();
	return 0;
}

void server::handleClient(){
#if DEBUG
	printf("server::handleClient()\n");
#endif
	const int sock = newsockfd;
	const struct sockaddr_in client = cli_addr;
#if DEBUG
	printf("client connected: ");
	printf("%d.%d.%d.%d\n",
	  int(client.sin_addr.s_addr&0xFF),
	  int((client.sin_addr.s_addr&0xFF00)>>8),
	  int((client.sin_addr.s_addr&0xFF0000)>>16),
	  int((client.sin_addr.s_addr&0xFF000000)>>24));

	printf("sock_fd: %d\n", sock);
#endif
	write(sock, header.c_str(), header.size());

	while(true){

		int err;
		int sizeerr = sizeof(err);
		int ret = getsockopt(sock, SOL_SOCKET, SO_ERROR, &err, &sizeerr);

		if(ret){
			printf("client disconnected\n");
			break;
		}

		char delim_header[128];
		sprintf(delim_header, "--mjpegstream\r\nContent-Type: image/jpeg\r\nContent-Length: %d\r\n\r\n", image.size());
		write(sock, delim_header, strlen(delim_header));
		write(sock, &image[0], image.size());

		usleep((int)(delay * 1000000));
	}
}

std::vector<uchar> server::matToJpeg(const cv::Mat& image){
	std::vector<uchar> jpeg;
	cv::imencode(".jpg", image, jpeg, parameters);
	return jpeg;
}

void server::setImage(cv::Mat image){
	if(numThreads == 0)
		return;
	this->image = matToJpeg(image);
}

int server::numClients() {
	return numThreads;
}

int server::getQuality() {
	return parameters[1];
}

double server::getFrameRate() {
	return 1/delay;
}

void server::setDelay(double d) {
	delay = d;
}

double server::getDelay() {
	return delay;
}
