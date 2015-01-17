#include "WPILib.h"
#include "ArmCode.h"
#include "Xbox.h"

class Robot: public IterativeRobot
{
private:
	LiveWindow *lw;
	ArmCode* arm;
	Xbox* controller;

	void RobotInit()
	{
		lw = LiveWindow::GetInstance();
		arm = new ArmCode(0,1,0,1,2,3,4,5,0,0,0,0,0,0);
		controller = new Xbox(0);
	}

	void AutonomousInit()
	{

	}

	void AutonomousPeriodic()
	{

	}

	void TeleopInit()
	{

	}

	int counter = 0;
	void TeleopPeriodic()
	{
		arm->setRVictor(controller->getRX());
		arm->setLVictor(controller->getLX());
		if(controller->getStart()) {
			arm->calibrate();
		}

		if(counter % 50 == 0){
			std::cout 	<< "LB: " << arm->getLButton() << " RB: " << arm->getRButton()
						<< " LM: " << controller->getLX() << " RM: " << controller->getRX()
						<< " LE: " << arm->getLTick() << " RE: " << arm->getRTick()
						<< std::endl;
		}

		counter++;
		Wait(0.005);
	}

	void TestPeriodic()
	{
		lw->Run();
	}
};

START_ROBOT_CLASS(Robot);
