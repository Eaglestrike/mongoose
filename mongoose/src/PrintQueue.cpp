/*
 * PrintQueue.cpp
 *
 *  Created on: Feb 13, 2015
 *      Author: Team 114
 */

#include "PrintQueue.h"
#include <thread>

PrintQueue::PrintQueue(int mod) {
	// TODO Auto-generated constructor stub
	PrintQueue::mod= mod;
	std::thread printLine(print);
}

PrintQueue::~PrintQueue() {
	// TODO Auto-generated destructor stub
}

void PrintQueue::print() {
	while(true) {
		if(queue.size() != 0) {
			std::cout << queue.at(0) << std::endl;
			queue.pop_back();
		}
	}
}

void PrintQueue::add(std::string log) {
	if(count % mod == 0)
		queue.push_back(log);
	count++;
}

