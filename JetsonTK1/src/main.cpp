/*
 * main.cpp
 *
 *  Created on: Jan 12, 2015
 *      Author: LAHS
 */

#include <iostream>

#include "opencv2/opencv.hpp"
#include "opencv2/gpu/gpu.hpp"

int main(){

	cv::VideoCapture vc(0);

	cv::Mat matrix;
	cv::gpu::GpuMat gpuMat;

	vc >> matrix;
	gpuMat.upload(matrix);

	std::cout << matrix;

}



