

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
	cv::Mat tmp;
#else
	cv::Mat image;
#endif
	while (true){

#if USE_GPU
		vc >> tmp;
		image.upload(tmp);
#else
		vc >> image;
#endif
		if (!image.empty()){
			cv::Mat grey;
			vector<cv::Rect> objects;

			cv::cvtColor(image, grey, CV_BGR2GRAY);
			cv::equalizeHist(grey, grey);

			classifier.detectMultiScale(grey, objects, 1.1, 2);

			for (size_t i = 0; i < objects.size(); i++){
				cv::rectangle(image, objects[i], cv::Scalar(0, 0, 255), 6);
			}

			imshow("video", image);

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


