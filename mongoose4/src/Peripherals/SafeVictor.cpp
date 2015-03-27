/*
 * SafeVictor.cpp
 *
 *  Created on: Feb 12, 2015
 *      Author: Team 114
 */


#include "SafeVictor.h"

SafeVictor::SafeVictor(int victorPort, DigitalInput* button, bool reverse): Victor(victorPort), m_Reverse(reverse){
	m_Safety_Button = button;
}

SafeVictor::~SafeVictor(){

}


void SafeVictor::Set(float output, uint8_t syncGroup){
	if(m_Reverse)
		output *= -1;

	if(m_Safety_Button->Get() && output < 0)
		output = 0;

	SafeVictor::Victor::Set(output, syncGroup);
}

bool SafeVictor::getButton(){
	return m_Safety_Button->Get();
}
