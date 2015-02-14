/*
 * PrintQueue.h
 *
 *  Created on: Feb 13, 2015
 *      Author: Giggles Upanda
 */

#include <vector>
#include <iostream>

#ifndef PRINTQUEUE_H_
#define PRINTQUEUE_H_

class PrintQueue {
public:
	PrintQueue(int mod);
	virtual ~PrintQueue();
	void print();
	void add(std::string log);

private:
	std::vector<std::string> queue;
	int mod;
};

#endif /* PRINTQUEUE_H_ */
