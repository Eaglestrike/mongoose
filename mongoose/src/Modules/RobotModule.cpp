#include "RobotModule.h"

RobotModule::RobotModule(std::string){
	
}

void RobotModule::enable(){
	m_Enabled = true;
}

void RobotModule::disable(){
	m_Enabled = false;
}

void RobotModule::reset(){

}

void RobotModule::getLoggingData(){

}

RobotModule::~RobotModule(){
	// Destructor
}
