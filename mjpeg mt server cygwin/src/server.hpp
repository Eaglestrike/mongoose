/*
 * server.hpp
 *
 *  Created on: Mar 4, 2015
 *      Author: Ben
 */

#ifndef SRC_SERVER_HPP_
#define SRC_SERVER_HPP_

#define DEBUG 1

#include <vector>
#include <string>
#include <thread>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <opencv2/opencv.hpp>
#include <pthread.h>

class server{
public:
	server(int port, double delay = 0.1);
	void setImage(cv::Mat image);
	void join();
	int numClients();

	void setQuality(int);
	void setFrameRate(double d);
	void setDelay(double d);
	int getQuality();
	double getFrameRate();
	double getDelay();
private:
	double delay;
	std::vector<uchar> matToJpeg(const cv::Mat& image);

	std::string header;
	std::vector<uchar> image;
	std::vector<int> parameters;

	//server variables
	const char* ipaddr;
	int sockfd, newsockfd, portno, clilen, n;
	struct sockaddr_in serv_addr, cli_addr;
	pthread_t* thread;
	int numThreads;

	std::thread waitThread;

	void waitAndListen();
	void handleClient();
public:
	static void callWaitAndListen(void*);
	static void* callHandleClient(void*);

};


#endif /* SRC_SERVER_HPP_ */
