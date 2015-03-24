/*
 * main.cpp
 *
 *  Created on: Mar 4, 2015
 *      Author: Ben
 */

#include "server.hpp"
#include <stdio.h>
#include <opencv2/opencv.hpp>

int main(int argc, char** argv){

	uint16_t port = 80;

	if(argc == 2){
		port = atoi(argv[1]);
	}


	printf("main()\n");
	double fps = 10.0;
	server s(port);
	s.setFrameRate(fps);
	s.setQuality(100);
	cv::VideoCapture vc(0);
	cv::Mat frame;
	cv::Mat resolution;

//	double factor = 0.1;
	while(true){
		vc >> frame;


//		resize(frame, resolution, cv::Size(), factor, factor, cv::INTER_NEAREST);
//		resize(resolution, frame, cv::Size(), 1/factor, 1/factor, cv::INTER_NEAREST);

		s.setImage(frame);
		usleep(s.getDelay() * 1000000);
	}
	printf("join()");
	s.join();
	printf("main() end\n");
}



