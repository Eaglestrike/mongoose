/*
 * server.hpp
 *
 *  Created on: Mar 1, 2015
 *      Author: robotics
 */

#ifndef SERVER_HPP_
#define SERVER_HPP_

#include <boost/asio.hpp>
#include <vector>
#include <string>
#include <opencv2/opencv.hpp>

class server : private boost::noncopyable{
public:
	explicit server(int port);
	void setImage(cv::Mat image);

private:
	void handle_accept(const boost::system::error_code& e);
	void handle_write(const boost::system::error_code &e, std::size_t bytes);
	std::vector<uchar> matToJpeg(const cv::Mat& image);

	boost::asio::io_service io_service_;
	boost::asio::ip::tcp::endpoint endpoint_;
	boost::asio::ip::tcp::acceptor acceptor_;
	boost::asio::ip::tcp::socket socket_;
	std::string header;
	std::vector<uchar> image;
	std::vector<int> parameters;


};

#endif /* SERVER_HPP_ */
