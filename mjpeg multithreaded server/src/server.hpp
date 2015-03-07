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
#include <sys/socket.h>
#include <opencv2/opencv.hpp>

class server{
public:
	explicit server(int port);
	void setImage(cv::Mat image);

private:
	std::vector<uchar> matToJpeg(const cv::Mat& image);

	std::string header;
	std::vector<uchar> image;
	std::vector<int> parameters;


};


#endif /* SRC_SERVER_HPP_ */
