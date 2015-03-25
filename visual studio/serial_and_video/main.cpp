


#include <iostream>
#include <string>
#include <cstdio>
#include "serial/serial.h"
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

string port("COM4");
char* cascade = "C:\\Robotics\\mongoose\\cascade_detector\\Release\\cascade.xml";
unsigned long baud = 9600;
serial::Serial* arduino;

double dist = 0;

void connectSerial(){
	arduino = new serial::Serial(port, baud, serial::Timeout::simpleTimeout(1000));
}

void updateDistance(){
	if (!arduino){
		cout << "arduno null" << endl;
		connectSerial();
		return;
	}
//	cout << "waiting" << endl;
//	arduino->waitForChange();
	if (arduino->isOpen() && arduino->available()){
		cout << "in if" << endl;
		string result = arduino->readline();
		dist = atof(result.c_str());
		arduino->flush();
		uint8_t* buf;
		arduino->read(buf, 1000);
	}
}

double calculateDeltaX(double distance, int center, int width){
	double totalX = 1.547*distance;
	double prop = (double)center / width;
	double delta = (totalX * prop - totalX / 2);
	//apply calibration
	delta = delta * 10 / 14;

	return delta;
}



int main(){

	VideoCapture vc(0);
	vc.set(CV_CAP_PROP_FRAME_WIDTH, 1280);
	vc.set(CV_CAP_PROP_FRAME_HEIGHT, 720);

	CascadeClassifier classifier;

	if (!classifier.load(cascade)){
		cout << "Error loading cascade classifier: " << cascade << endl;
		getchar();
		return -1;
	}

	namedWindow("video", WINDOW_AUTOSIZE);
	
	Mat frame, grey;
	unsigned long frames = 0;

	while (true){
		vector<Rect> logos;
		Rect largest;

		vc >> frame;

		if (!frame.empty()){

			cvtColor(frame, grey, CV_BGR2GRAY);
			equalizeHist(grey, grey);
			classifier.detectMultiScale(grey, logos, 1.1, 2);

			for (size_t i = 0; i < logos.size(); i++){
				if (i == 0)
					largest = logos[0];
				if (logos[i].width > largest.width)
					largest = logos[i];

				rectangle(frame, logos[i], Scalar(0, 0, 255), 6);
			}

			imshow("video", frame);

		} else {
			cout << "frame empty!" << endl;
			getchar();
			return -1;
		}

		if (frames % 2 == 0){
			updateDistance();
			int center = largest.x + largest.width / 2;
			int wid = frame.cols;
			double delta = calculateDeltaX(dist, center, wid);

			cout << "Width: " << largest.width << " Distance: " << dist << " DeltaX: " << delta << endl;

		}

		if (cv::waitKey(30) >= 0)
			break;

		frames++;
	}

	return 0;
}