#include "RobotModule.h"

RobotModule::RobotModule(std::string name): m_Module_Name(name), m_Error_Checking_Thread(RobotModule::callCheckError, this), m_Enabled(false){
	
}

void RobotModule::enable(){
	m_Enabled = true;
}

void RobotModule::disable(){
	m_Enabled = false;
}

void RobotModule::reset(){

}

std::vector<std::string> RobotModule::getLoggingHeader(){
	std::vector<std::string> header;
	header.push_back("test");
}

std::vector<double> RobotModule::getLoggingData(){
	std::vector<double> data;
	data.push_back(0);
	return data;
}

std::string RobotModule::getModuleName(){
	return m_Module_Name;
}

RobotModule::~RobotModule(){

}

void RobotModule::checkError(){
	std::cout <<  m_Module_Name << " checkError() not overwritten!" << std::endl;
}

void RobotModule::callCheckError(void* m){

	RobotModule* module = (RobotModule*) m;

	std::cout << module->getModuleName() << "::callCheckError()" << std::endl;

	try{

		module->checkError();

	}catch(EaglestrikeError& e){

		std::cout << "CAUGHT EAGLESTRIKE ERROR: " << std::endl;
		std::cout << "Error ptr: " << &e << std::endl;

		if(e.shouldBeFatal()){
			std::cout << "Fatal Error: " << std::flush;
		}else{
			std::cout << "Error: " << std::flush;
		}

		std::cout << "getModuleName()" << std::endl;
		module->getModuleName();
		std::cout << "toString()" << std::endl;
		e.toString();

		std::cout << "In module: " << module->getModuleName() << " " << e.toString() << std::endl;

		if(e.shouldBeFatal()){
			module->handleFatalError();
		}else
			callCheckError(module);

	}
}


void RobotModule::handleFatalError(){
	disable();
}
