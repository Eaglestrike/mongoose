

#define USE_GPU 1

#include "opencv2/opencv.hpp"

#if USE_GPU
#include "opencv2/gpu/gpu.hpp"
#endif

#include <iostream>
#include <stdio.h>


using namespace std;


char* trim(char* str){
	char *end;
	while (isspace(*str)) str++;

	if (*str == 0)
		return str;

	end = str + strlen(str) - 1;
	while (end > str && isspace(*end)) end--;
	*(end + 1) = 0;

	return str;
}

int main(int argc, char** argv){

	cv::VideoCapture vc;

	if (argc < 3){
		cout << "usage: " << argv[0] << " <cascade.xml> [-v <video> | -w <webcam> = 0]" << endl;
		return -1;
	}else{
		char* trimmed = trim(argv[2]);
		if (strcmp(trimmed, "-v") > 0)
			vc = cv::VideoCapture(argv[3]);
		else if (strcmp(trimmed, "-w")){
			if (argc == 3)
				vc = cv::VideoCapture(0);
			else
				vc = cv::VideoCapture(atoi(argv[3]));
		}
	}
		
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
	cv::gpu::GpuMat image;
	cv::gpu::GpuMat grey;
	cv::Mat tmp;
#else
	cv::Mat image;
	cv::Mat grey;
#endif

	while (true){

#if USE_GPU
		vc >> tmp;
		image.upload(tmp);
#else
		vc >> image;
#endif
		if (!image.empty()){

#if USE_GPU
			cv::gpu::GpuMat faceBuf;
			int detections = 0;
#endif

			vector<cv::Rect> objects;


#if USE_GPU
			cv::gpu::cvtColor(image, grey, CV_BGR2GRAY);
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

#if USE_GPU
			for (size_t i = 0; i < objects.size(); i++){
				cv::rectangle(tmp, objects[i], cv::Scalar(0, 0, 255), 6);
			}

			imshow("video", tmp);
#else
			for (size_t i = 0; i < objects.size(); i++){
				cv::rectangle(image, objects[i], cv::Scalar(0, 0, 255), 6);
			}

			imshow("video", image);
#endif
		}
		else{
			cout << "Error with frame!" << endl;
			return -1;
		}

		if (cv::waitKey(30) >= 0)
			break;

	}


	return 0;
}


