
#include "MJPEGServer.h"


MJPEGServer::MJPEGServer(uint16_t port): m_port(port), m_IOService(), m_acceptor(m_IOService, boost::asio::ip::tcp::v4(), port){
	m_IOService.run();
}

MJPEGServer::~MJPEGServer(){

}
