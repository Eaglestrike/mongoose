#include "RobotModule.h"


RobotModule::RobotModule(std::string name): m_Module_Name(name), m_Error_Checking_Thread(RobotModule::callCheckError, this){
	
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

void RobotModule::checkError(){
	std::cout <<  m_Module_Name << " checkError() not overwritten!" << std::endl;
}

void RobotModule::callCheckError(void* m){
	RobotModule* module = (RobotModule*) m;
	module->checkError();
}
