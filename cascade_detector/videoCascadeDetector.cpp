

#define USE_GPU 0

#include "opencv2/opencv.hpp"

#if USE_GPU
#include "opencv2/gpu/gpu.hpp"
#endif

#include <iostream>
#include <stdio.h>
#include <ctime>


using namespace std;


int main(int argc, char** argv){


	if (argc != 2){
		cout << "usage: " << argv[0] << " <cascade.xml>" << endl;
		return -1;
	}
	
	cv::VideoCapture vc = cv::VideoCapture(0);	
	vc.set(CV_CAP_PROP_FRAME_WIDTH, 1280);
	vc.set(CV_CAP_PROP_FRAME_HEIGHT, 720);

	char* cascade = argv[1];

#if USE_GPU
	cv::gpu::CascadeClassifier_GPU classifier;
#else
	cv::CascadeClassifier classifier;
#endif

	if (!classifier.load(cascade)){
		cout << "Error loading cascade classifier: " << cascade << endl;
		return -1;
	}

	cv::namedWindow("video", cv::WINDOW_AUTOSIZE);
#if USE_GPU
	cv::gpu::GpuMat gpu_image;
	cv::gpu::GpuMat grey;
	cv::Mat image;
#else
	cv::Mat image;
	cv::Mat tmp;
	cv::Mat grey;
#endif

	int frames = 0;
	std::clock_t start;
	double totalTime = 0, deltaTime = 0;


	while (true){
		vector<cv::Rect> objects;
		cv::Rect largest;

		start = std::clock();
		vc >> image;

		if (!image.empty()){
#if USE_GPU
			gpu_image.upload(image);
			cv::gpu::GpuMat faceBuf;
			int detections = 0;
#endif
			

#if USE_GPU
			cv::gpu::cvtColor(gpu_image, grey, CV_BGR2GRAY);
			cv::gpu::equalizeHist(grey, grey);
			detections = classifier.detectMultiScale(grey, faceBuf);

			cv::Mat gpuDownload;
			faceBuf.colRange(0, detections).download(gpuDownload);
			cv::Rect* faceRects = gpuDownload.ptr<cv::Rect>();

			for (int i = 0; i < detections; i++) {
				objects.push_back(faceRects[i]);
			}

#else
			cv::cvtColor(image, grey, CV_BGR2GRAY);
			cv::equalizeHist(grey, grey);
			classifier.detectMultiScale(grey, objects, 1.1, 2);

#endif
			for (size_t i = 0; i < objects.size(); i++){
				if (i == 0)
					largest = objects[0];
				if (objects[i].width > largest.width)
					largest = objects[i];

				cv::rectangle(image, objects[i], cv::Scalar(0, 0, 255), 6);
			}


			imshow("video", image);

		}else{
			cout << "Error with frame!" << endl;
			return -1;
		}

		if (cv::waitKey(30) >= 0)
			break;

		deltaTime = (std::clock() - start) / (double)CLOCKS_PER_SEC;
		totalTime += deltaTime;
		frames++;

		if (frames % 20 == 0){
			cout << "Frames: " << frames << " Average fps: " << frames / totalTime << " fps: " << 1 / deltaTime << " Rectangles: " << objects.size() << " Width: " << largest.width << endl;
		}
	}


	return 0;
}


