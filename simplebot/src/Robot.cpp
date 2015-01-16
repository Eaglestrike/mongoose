#include "WPILib.h"
#include <vector>
//#include <algorithm>

class Robot: public IterativeRobot
{
private:
	LiveWindow *lw;
	int i =0;
	Victor* left1;
	Victor* left2;
	Victor* right1;
	Victor* right2;
	Joystick* leftJoy;
	Joystick* rightJoy;
	Compressor* comp;
	Solenoid* cole;
	BuiltInAccelerometer* rom;
	Timer* tim;
	Encoder* lEnc;


	void RobotInit()
	{
		lw = LiveWindow::GetInstance();
		left1 = new Victor(0);
		left2 = new Victor(1);
		right1 = new Victor(3);
		right2 = new Victor(2);
		leftJoy = new Joystick(0);
		rightJoy = new Joystick(1);
		comp = new Compressor(0);
		comp->SetClosedLoopControl(true);
		cole = new Solenoid(0);
		rom = new BuiltInAccelerometer();
		lEnc = new Encoder(0,1);
		tim = new Timer();

	}

	int counter = 0;
	bool last;
	std::vector<float> throttleReadings;
	int size = 25;
	int times = 0;
	int count = 0;
	bool lastTime;

	void TeleopPeriodic()
	{
		tim->Start();
		if(last != rightJoy->GetRawButton(4))
			counter++;
		last = rightJoy->GetRawButton(4);

		if(counter % 4 == 0)
			cole->Set(true);
		else if(counter % 2 == 0)
			cole->Set(false);
		i++;
		if(lastTime != rightJoy->GetRawButton(5)) {
			count++;
		}
		lastTime = rightJoy->GetRawButton(5);
		throttleReadings.insert(throttleReadings.begin(), leftJoy->GetY());
		float power = 0;
		if(count % 4 == 0){
			power = throttleReadings.at(0);
		}
		else if(count % 2 == 0){
			for(int k = 0; k < throttleReadings.size(); k++) {
				power+=throttleReadings.at(k);
			}
			power = power/throttleReadings.size();
		}
		if(i % 60 == 0) {
			//std::cout << -rightJoy->GetX() << std::endl;
		}
		float angle = -rightJoy->GetX();
		if(angle < .04 && angle > -.04) {
			angle = 0;
		}
		drive(power, angle);
//		left1->Set(power);
//		left2->Set(power);
//		right1->Set(-power);
//		right2->Set(-power);
		times++;
//		left1->Set(leftJoy->GetY());
//		left2->Set(leftJoy->GetY());
//		right1->Set(-leftJoy->GetY());
//		right2->Set(-leftJoy->GetY());

//		float acceleration = lEnc->GetRate()/tim->Get();
		if(throttleReadings.size() > size) {
			throttleReadings.pop_back();
			//throttleReadings.erase(throttleReadings.begin());
		}
		tim->Stop();
		Wait(0.005);

	}

	void TestPeriodic()
	{
		lw->Run();
	}

	void DisabledPeriodic() {
		throttleReadings.clear();
		//std::cout << "PI" << std::endl;
	}
	void drive(double throttle, double angle) {

		double leftMotorOutput =  0;
		double rightMotorOutput = 0;

		//std::cout << angle <<std::endl;
		if(angle < 0.0)
			angle = -(angle * angle);
		else
			angle = angle * angle;

		if(throttle > 0.0)
			throttle = throttle * throttle;
		else
			throttle = - throttle * throttle;

		if(throttle > 0.0) {
			if(angle < 0.0) {
				rightMotorOutput = throttle - angle;
				leftMotorOutput = fmin(throttle, angle);
			}
			else {
				rightMotorOutput = fmin(throttle, -angle);
				leftMotorOutput = throttle + angle;
			}
		}
		else {
		 	if(angle > 0.0) {
				leftMotorOutput = -fmin(-throttle, angle);
				rightMotorOutput = throttle + angle;
			}
			else {
				leftMotorOutput = throttle - angle;
				rightMotorOutput = -fmin(-throttle,-angle);
			}

		}
		if(throttle == 0 && angle == 0) {
			leftMotorOutput = 0;
			rightMotorOutput = 0;
		}
		if(angle == 0) {
			leftMotorOutput = throttle;
			rightMotorOutput = throttle;
		}
		if(i%60 == 0) {
			std::cout << "Left Motor: " << leftMotorOutput << " , Right Motor: " << -rightMotorOutput << std::endl;
		}
		left1->Set(leftMotorOutput);
		left2->Set(leftMotorOutput);
		right1->Set(-rightMotorOutput);
		right2->Set(-rightMotorOutput);
	}

//	void slowDown(float targetAcceleration, float currentAcceleration) {
//		float error = currentAcceleration - targetAcceleration;
//		if(error <= 100) return;
//		float p = .0005;
//		left1->Set(left1->Get() + error*p);
//		left2->Set(left2->Get() + error*p);
//		right1->Set(-right1->Get() - error*p);
//		right2->Set(-right2->Get() - error*p);
//		std::cout << "in the method" << std::endl;
//
//	}
};

START_ROBOT_CLASS(Robot);
