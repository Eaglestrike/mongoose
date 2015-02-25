#include "WPILib.h"

class Robot: public IterativeRobot
{
private:
	LiveWindow *lw;
	TalonSRX* asdf;
	TalonSRX* awqer;

	void RobotInit()
	{
		lw = LiveWindow::GetInstance();
		asdf = new TalonSRX(6);
		awqer = new TalonSRX(7);
	}

	void AutonomousInit()
	{

	}

	void AutonomousPeriodic()
	{
		asdf->Set(0);
		awqer->Set(0);
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
