/*
 * main.cpp
 *
 *  Created on: Jan 12, 2015
 *      Author: LAHS
 */

#include <iostream>

#include "opencv2/opencv.hpp"
#include "opencv2/gpu/gpu.hpp"

#include <thread>

void printHi(){
	std::cout << "hi" << std::endl;

}

void printHi2(){
	std::cout << "hi 2" << std::endl;
}


int main(){

	std::thread hi1 (printHi);
	std::thread hi2 (printHi2);

	hi1.join();
	hi2.join();

	std::cout << "done" << std::endl;

	return 0;
}



