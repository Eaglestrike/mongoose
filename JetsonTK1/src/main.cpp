

#include <iostream>
#include "opencv2/opencv.hpp"
#include "opencv2/gpu/gpu.hpp"


using namespace cv;
using namespace std;

int main(){

	VideoCapture vc(0);
	Mat image;

	vc >> image;

	imshow("test", image);

	waitKey(0);

}
