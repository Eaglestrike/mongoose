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
	printf("main()\n");
	server s("localhost",80, 1);
	cv::VideoCapture vc(0);
	cv::Mat frame;

	while(true){
		vc >> frame;
		s.setImage(frame);
		usleep((int)(1 * 1000000));
	}
	s.join();
	printf("main() end\n");
}



