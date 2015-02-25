

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

	Mat image;

	namedWindow("test");

	while(1){
		vc >> image;
		imshow("test", image);


		if(waitKey(50) >= 0)
			break;
	}

	return 0;

}
