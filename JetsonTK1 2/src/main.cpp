

#include <iostream>
#include "opencv2/opencv.hpp"
#include "opencv2/gpu/gpu.hpp"
//#include "MJPEGServer.h"

using namespace cv;
using namespace std;

int main(){

	cout << "making classifier" << endl;

	VideoCapture vc(0);
	gpu::CascadeClassifier_GPU classifier;

	cout << "loading classifier" << endl;

	if(!classifier.load("cascade.xml")){
		cerr << "Error loading cascade classifier" << endl;
		return -1;
	}

	namedWindow("video", WINDOW_AUTOSIZE);

	Mat frame;
	Mat grey_frame;
	gpu::GpuMat gpu_frame;

	while(1){
		vc >> frame;

		if(frame.empty()){
			cout << "empty frame!" << endl;
			return -1;
		}

		cvtColor(frame, grey_frame, CV_BGR2GRAY);
		gpu_frame.upload(grey_frame);

		vector<Rect> detections;
		gpu::GpuMat faceBuf;
		int numDetections = 0;
// DO THE INTERVIEW NOWWWWW
		imshow("video", frame);

		if(waitKey(50) >= 0)
			break;
	}

	return 0;

}
