

#include <opencv2/opencv.hpp>
#include <boost/asio.hpp>
#include <iostream>

using namespace cv;
using boost::asio::ip::tcp;

int main(){

	VideoCapture vc(0);
	Mat image;

	boost::asio::io_service io_service;
	tcp::acceptor acceptor(io_service, tcp::endpoint(tcp::v4(), 1000));

	for (;;){
		tcp::socket socket(io_service);
		acceptor.accept(socket);

		std::cout << "Accepted client!" << std::endl;

		boost::system::error_code error;

		std::cout << "Writing initial header... ";

		char* initheader = "HTTP/1.1 200 OK\r\nServer: MJPG/1.0\r\nAccept-Range: bytes\r\nConnection: close\r\nContent-Type: multipart/x-mixed-replace; boundary=mjpegstream\r\n\r\n";
		boost::asio::write(socket, boost::asio::buffer(std::string(initheader)), error);

		std::cout << "done" << std::endl;

		try{

			for (;;){
				
				if (!socket.is_open())
					break;


				std::cout << "Getting frame... ";

				vc >> image;

				putText(image, "hi cole --opencv", Point(50,50), FONT_HERSHEY_PLAIN, 1, Scalar(0,0,255));

				std::cout << "done\nConverting to jpg...";
				
				std::vector<uchar> outbuf;
				std::vector<int> params;
				params.push_back(CV_IMWRITE_JPEG_QUALITY);
				params.push_back(100);
				cv::imencode(".jpg", image, outbuf, params);

				std::cout << "done\nSending header... ";

				char header[128];
				sprintf(header, "--mjpegstream\r\nContent-Type: image/jpeg\r\nContent-Length: %lu\r\n\r\n", outbuf.size());
				boost::asio::write(socket, boost::asio::buffer(std::string(header)), error);

				std::cout << "done" << std::endl;

				std::cout << "Sending " << outbuf.size() << " bytes...";
				boost::asio::write(socket, boost::asio::buffer(outbuf), error);
				std::cout << "done" << std::endl;

			}

		} catch (std::exception& e){
			std::cerr << e.what() << std::endl;
			continue;
		}

	}

	return 0;

}


