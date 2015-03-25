

#include <iostream>
#include "opencv2/opencv.hpp"
#include "opencv2/gpu/gpu.hpp"
#include <ctime>
#include "server.hpp"

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

	Mat grey_frame;
	Mat gpu_download;
	Mat frame;
	gpu::GpuMat gpu_frame;
	gpu::GpuMat faceBuf;
	Rect largest;
	Rect* objects_ptr;
	int detections = 0;

	int frames = 0;
	clock_t start;
	double deltaTime = 0;

	while(1){

		start = clock();

		vector<Rect> objects;
		vc >> frame;

		if(frame.empty()){
			cout << "empty frame!" << endl;
			return -1;
		}

		cvtColor(frame, grey_frame, CV_BGR2GRAY);
		gpu_frame.upload(grey_frame);
		gpu::equalizeHist(gpu_frame, gpu_frame);

		detections = classifier.detectMultiScale(gpu_frame, faceBuf);
		faceBuf.colRange(0, detections).download(gpu_download);
		objects_ptr = gpu_download.ptr<Rect>();

		for(int i = 0; i < detections; i++){
			objects.push_back(objects_ptr[i]);
		}

		for(size_t i = 0; i < objects.size(); i++){
			if(i == 0)
				largest = objects[0];
			if(objects[i].width > largest.width)
				largest = objects[i];
			rectangle(frame, objects[i], Scalar(0,0,255), 6);
		}

		imshow("video", frame);

		deltaTime =  (clock() - start) / (double)CLOCKS_PER_SEC;

		if(frames % 10 == 0){
			cout << "frame: " << frames << " fps: " << 1/deltaTime << endl;
		}

		if(waitKey(50) >= 0)
			break;
		frames++;

	}

	return 0;

}
