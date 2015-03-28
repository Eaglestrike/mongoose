

#include "opencv2/opencv.hpp"
#include "opencv2/gpu/gpu.hpp"

#include <iostream>
#include <stdio.h>


using namespace std;


int main(int argc, char** argv){

	if (argc != 3){
		cout << "usage: " << argv[0] << " <cascade.xml> <picture>" << endl;
		return -1;
	}
		
	char* cascade = argv[1];
	char* picture = argv[2];

	cv::CascadeClassifier classifier;

	if (!classifier.load(cascade)){
		cout << "Error loading cascade classifier: " << cascade << endl;
		return -1;
	}

	cv::Mat image = cv::imread(picture);
	if (!image.empty()){
		cv::Mat grey;
		vector<cv::Rect> objects;

		cv::cvtColor(image, grey, CV_BGR2GRAY);
		cv::equalizeHist(grey, grey);
		
		classifier.detectMultiScale(grey, objects, 1.1, 2);

		for (size_t i = 0; i < objects.size(); i++){
			cv::rectangle(image, objects[i], cv::Scalar(0,0,255), 6);
		}

		cv::namedWindow(picture, cv::WINDOW_NORMAL);
		imshow(picture, image);

		while (1){
			if (cv::waitKey(30) >= 0)
				return 0;
		}

		return 0;

	}
	else{
		cout << "Error loading picture: " << picture << endl;
	}
}


