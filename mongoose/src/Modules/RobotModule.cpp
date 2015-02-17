#include "RobotModule.h"
#include <thread>

RobotModule::RobotModule(std::string): m_Error_Checking_Thread(RobotModule::checkError()){
	
}

void RobotModule::enable(){
	m_Enabled = true;
}

void RobotModule::disable(){
	m_Enabled = false;
}

void RobotModule::reset(){

}
//cole was here
double* RobotModule::getLoggingData(){
	return 0;
}

RobotModule::~RobotModule(){
	// Destructor
}
