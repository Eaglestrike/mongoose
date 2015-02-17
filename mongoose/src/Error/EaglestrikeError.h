/*
 * EaglestrikeError.h
 *
 *  Created on: Feb 16, 2015
 *      Author: Team 114
 */

#ifndef EAGLESTRIKEERROR_H_
#define EAGLESTRIKEERROR_H_

#include <string>
#include <iostream>

class EaglestrikeError {
public:
	explicit EaglestrikeError(const char* where, const char* what, bool fatal = false);
	virtual ~EaglestrikeError();
	const char* what();
	const char* where();
	bool shouldBeFatal();
	friend std::ostream& operator << (std::ostream& os, EaglestrikeError&);
private:
	const char* m_Error;
	const char* m_Location;
	bool m_Fatal;
};

#endif /* EAGLESTRIKEERROR_H_ */
