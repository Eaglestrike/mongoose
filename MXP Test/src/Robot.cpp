#include "WPILib.h"
#include <iostream>
#include <vector>

class Robot: public IterativeRobot
{
private:
	LiveWindow *lw;
	std::vector<DigitalInput*> buttons;

	void RobotInit()
	{
		lw = LiveWindow::GetInstance();

		for(int i = 10; i < 25; ++i){
			buttons.push_back(new DigitalInput(i));
		}
	}

	void AutonomousInit()
	{

	}

	void AutonomousPeriodic()
	{
		for(size_t i = 0; i < buttons.size(); ++i){
			std::cout << "port: " << buttons[i]->GetChannel() << " value: " << buttons[i]->Get() << std::endl;
		}
		std::cout << "******************************" << std::endl;

		Wait(0.5);
	}

	void TeleopInit()
	{

	}

	void TeleopPeriodic()
	{

	}

	void TestPeriodic()
	{
		lw->Run();
	}
};

START_ROBOT_CLASS(Robot);
