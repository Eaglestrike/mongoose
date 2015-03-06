/*
 * server.cpp
 *
 *  Created on: Mar 4, 2015
 *      Author: Ben
 */

#include "server.hpp"


server::server(int port):
	endpoint_(boost::asio::ip::tcp::v4(), port),
	acceptor_(io_service_),
	socket_(io_service_),
	header("HTTP/1.1 200 OK\r\nServer: MJPG/1.0\r\nAccept-Range: bytes\r\nConnection: close\r\nContent-Type: multipart/x-mixed-replace; boundary=mjpegstream\r\n\r\n")
{
	parameters.push_back(CV_IMWRITE_JPEG_QUALITY);
	parameters.push_back(100);

	acceptor_.open(endpoint_.protocol());
	acceptor_.set_option(boost::asio::ip::tcp::acceptor::reuse_address(true));
	acceptor_.bind(endpoint_);
	acceptor_.listen();
	acceptor_.async_accept(socket_, boost::bind(&server::handle_accept, this, boost::asio::placeholders::error));

}

void server::handle_write(const boost::system::error_code &e, std::size_t bytes){

}

void server::handle_accept(const boost::system::error_code& e){
	if(!e){
		acceptor_.async_accept(socket_, boost::bind(&server::handle_accept, this, boost::asio::placeholders::error));
		boost::asio::async_write(socket_, boost::asio::buffer(header), &server::handle_write);
		while(true){
			char header[128];
			sprintf(header, "--mjpegstream\r\nContent-Type: image/jpeg\r\nContent-Length: %lu\r\n\r\n", image.size());
			boost::asio::async_write(socket_, boost::asio::buffer(std::string(header)), &server::handle_write);
		}
	}
}

std::vector<uchar> server::matToJpeg(const cv::Mat& image){
	std::vector<uchar> jpeg;
	cv::imencode(".jpg", image, jpeg, parameters);
	return jpeg;
}

void server::setImage(cv::Mat image){
	this->image = matToJpeg(image);
}



