


#if 0

#ifndef MJPEGSERVER_H_
#define MJPEGSERVER_H_

#include <opencv2/opencv.hpp>
#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <boost/bind/bind.hpp>
#include <boost/bind.hpp>
#include <boost/ref.hpp>


class MJPEGServer{
public:
	MJPEGServer(boost::asio::io_service&, uint16_t);
	~MJPEGServer();
private:

	void waitForUser();
	void acceptUser(int/*boost::asio::ip::tcp::socket*/);

	boost::thread m_waitThread;
	boost::asio::io_service m_io_service;
	boost::asio::ip::tcp::acceptor m_acceptor;
	uint16_t m_port;
};



#endif
#endif
