
#ifndef MJPEGSERVER_H_
#define MJPEGSERVER_H_

#include <opencv2/opencv.hpp>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>

class MJPEGServer{
public:
	MJPEGServer(uint16_t port);
	~MJPEGServer();
private:
	boost::asio::io_service m_IOService;
	boost::asio::ip::tcp::acceptor m_acceptor;
	uint16_t m_port;
};



#endif
