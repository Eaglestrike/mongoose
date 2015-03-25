/*
 * server.cpp
 *
 *  Created on: Mar 4, 2015
 *      Author: Ben
 */

#include "server.hpp"


server::server(int port):
	header("HTTP/1.1 200 OK\r\nServer: MJPG/1.0\r\nAccept-Range: bytes\r\nConnection: close\r\nContent-Type: multipart/x-mixed-replace; boundary=mjpegstream\r\n\r\n")
{
	parameters.push_back(CV_IMWRITE_JPEG_QUALITY);
	parameters.push_back(100);

}


std::vector<uchar> server::matToJpeg(const cv::Mat& image){
	std::vector<uchar> jpeg;
	cv::imencode(".jpg", image, jpeg, parameters);
	return jpeg;
}

void server::setImage(cv::Mat image){
	this->image = matToJpeg(image);
}



