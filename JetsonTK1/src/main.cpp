

#include <iostream>
#include "opencv2/opencv.hpp"
#include "opencv2/gpu/gpu.hpp"
#include "MJPEGServer.h"

using namespace cv;
using namespace std;

int main(){

	VideoCapture vc(0);
	Mat image;


	gpu::GpuMat gpuImage;
	gpu::GpuMat grey;

	namedWindow("test");

	MJPEGServer server(1000);



	return 0;

}
