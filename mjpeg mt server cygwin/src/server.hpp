/*
 * server.hpp
 *
 *  Created on: Mar 4, 2015
 *      Author: Ben
 */

#ifndef SRC_SERVER_HPP_
#define SRC_SERVER_HPP_

#include <vector>
#include <string>
#include <thread>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <opencv2/opencv.hpp>
#include <pthread.h>

class server{
public:
	explicit server(int port);
	void setImage(cv::Mat image);

private:
	std::vector<uchar> matToJpeg(const cv::Mat& image);

	std::string header;
	std::vector<uchar> image;
	std::vector<int> parameters;

	//server variables
	int sockfd, newsockfd, portno, clilen, n;
	struct sockaddr_in serv_addr, cli_addr;
	pthread_t threads[20];
	int numThreads;

	std::thread waitThread;

	void waitAndListen();
	void handleClient();
public:
	static void callWaitAndListen(void*);
	static void* callHandleClient(void*);

};


#endif /* SRC_SERVER_HPP_ */
