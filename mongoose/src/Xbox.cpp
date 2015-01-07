
#include "Xbox.h"

Xbox::Xbox(int port): Joystick(port){

}


bool Xbox::GetA(){
	return GetRawButton(1);
}

bool Xbox::GetB(){
	return GetRawButton(2);
}

bool Xbox::GetX(){
	return GetRawButton(3);
}

bool Xbox::GetY(){
	return GetRawButton(4);
}

bool Xbox::GetRB(){
	return GetRawButton(6);
}

bool Xbox::GetLB(){
	return GetRawButton(5);
}

bool Xbox::GetStart(){
	return GetRawButton(8);
}

bool Xbox::GetBack(){
	return GetRawButton(7);
}

bool Xbox::GetR3(){
	return GetRawButton(10);
}

bool Xbox::GetL3(){
	return GetRawButton(9);
}

bool Xbox::GetRB() {
    return GetRawButton(6);
}

bool Xbox::GetLB() {
    return GetRawButton(5);
}

float Xbox::GetLT(){
	return GetRawAxis(3);
}

float Xbox::GetRT(){
	return GetRawAxis(3);
}

float Xbox::GetRX(){
	return GetRawAxis(4);
}

float Xbox::GetRY(){
	return -GetRawAxis(5);
}

float Xbox::GetLX(){
	return GetX();
}

float Xbox::GetLY(){
	return -GetY();
}
