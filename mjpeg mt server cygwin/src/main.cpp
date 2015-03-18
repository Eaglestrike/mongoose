/*
 * main.cpp
 *
 *  Created on: Mar 4, 2015
 *      Author: Ben
 */

#include "server.hpp"
#include <stdio.h>
#include <opencv2/opencv.hpp>

int main(){

	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);

	printf("main()\n");
	double fps = 10.0;
	server s("10.1.14.20" ,80);
	s.setFrameRate(fps);
	s.setQuality(0);
	cv::VideoCapture vc(0);
	cv::Mat frame;

	while(true){
		vc >> frame;
		s.setImage(frame);
		usleep(s.getDelay() * 1000000);
	}
	printf("join()");
	s.join();
	printf("main() end\n");
}



