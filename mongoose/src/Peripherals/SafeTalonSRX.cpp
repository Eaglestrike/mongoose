/*
 * SafeTalonSRX.cpp
 *
 *  Created on: Feb 12, 2015
 *      Author: Team 114
 */

#include <WPILib.h>
#include "SafeTalonSRX.h"

SafeTalonSRX::SafeTalonSRX(int talonSRXPort, DigitalInput* button, bool reverse): TalonSRX(talonSRXPort), m_Reverse(reverse){
	m_Safety_Button = button;
}
//cole was here
SafeTalonSRX::~SafeTalonSRX(){

}

void SafeTalonSRX::Set(float output, uint8_t syncGroup){
	if(m_Reverse)
		output *= -1;

	if(m_Safety_Button->Get() && output < 0){
		//std::cerr << "Error: button pressed and power < 0" << " power: " << output << std::endl;
		output = 0;
	}

	SafeTalonSRX::TalonSRX::Set(output, syncGroup);
}


bool SafeTalonSRX::getButton(){
	return m_Safety_Button->Get();
}


