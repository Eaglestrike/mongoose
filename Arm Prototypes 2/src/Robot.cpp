#include "WPILib.h"
#include "ArmCode.h"

class Robot: public IterativeRobot
{
private:
	LiveWindow *lw;
	ArmCode* arm;

	void RobotInit()
	{
		lw = LiveWindow::GetInstance();
		arm = new ArmCode(0,1,0,1,2,3,4,5,0,0,0,0,0,0);
		std::cout << "ROBOT INIT!!!!";
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

	void TeleopPeriodic()
	{
		std::cout << "Left ";
		std::cout << arm->getLTick();
		std::cout << "\nRight ";
		std::cout << arm->getRTick();
		Wait(.1);
	}

	void TestPeriodic()
	{
		lw->Run();
	}
};

START_ROBOT_CLASS(Robot);