

#include <iostream>
#include "opencv2/opencv.hpp"
#include "opencv2/gpu/gpu.hpp"
#include "MJPEGServer.h"

using namespace cv;
using namespace std;

int main(){

//	VideoCapture vc(0);
//	Mat image;
//
//
//	gpu::GpuMat gpuImage;
//	gpu::GpuMat grey;
//
//	namedWindow("test");

	boost::asio::io_service io_Service;
	MJPEGServer server(io_Service, 5000);
	io_Service.run();

	return 0;

}
