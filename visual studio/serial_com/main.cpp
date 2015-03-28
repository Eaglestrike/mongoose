


#include <iostream>
#include <string>
#include <cstdio>
#include "serial/serial.h"


using namespace std;

void enumerate_ports(){
	vector<serial::PortInfo> devices = serial::list_ports();
	vector <serial::PortInfo>::iterator iter = devices.begin();

	while (iter != devices.end()){

		serial::PortInfo device = *iter++;

		printf("(%s, %s, %s)\n", device.port.c_str(), device.description.c_str(), device.hardware_id.c_str());

	}
}


int main(int argc, char** argv){
	string port("COM4");
	unsigned long baud = 9600;

	serial::Serial arduino(port, baud, serial::Timeout::simpleTimeout(1000));
	
	if (!arduino.isOpen())
		cout << "Serial Port Not Open!";


	while (1){
		string result = arduino.readline();
		double dist = atof(result.c_str());
		cout << dist << endl;
	}
}


