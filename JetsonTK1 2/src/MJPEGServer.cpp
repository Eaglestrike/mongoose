
#if 0

#include "MJPEGServer.h"


MJPEGServer::MJPEGServer(boost::asio::io_service& io_service, uint16_t port): 	m_port(port),
																				m_acceptor(io_service, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port)),
																				m_waitThread(&MJPEGServer::waitForUser, this),
																				m_io_service(io_service){
	std::cout << "MJPEGServer()" << std::endl;
	//m_waitThread.join();
	//m_waitThread.start_thread();
}

MJPEGServer::~MJPEGServer(){

}

void MJPEGServer::waitForUser(){
	while(1){
		boost::asio::ip::tcp::socket user_socket(m_io_service);
		m_acceptor.accept(user_socket);
		std::cout << "user accepted!" << std::endl;
		boost::thread userThread(boost::bind(&MJPEGServer::acceptUser, this, 5/* boost::ref(user_socket)*/));
	}
}

void MJPEGServer::acceptUser(int i/*sboost::asio::ip::tcp::socket socket*/){

	std::cout << "acceptUser()" << std::endl;
}

#endif
