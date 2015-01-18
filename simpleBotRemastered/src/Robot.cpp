#include "WPILib.h"
#include <vector>
#include <algorithm>
#include <thread>
#include <string>
#include "ServerSocket.h"
#include "SocketException.h"
PowerDistributionPanel* pdp;
Timer hudtime;
    void *HUD(void *) {
    	try
    	    {
    	      // Create the socket
    	      ServerSocket server ( 5801 );

    	      while ( true )
    	        {

    	          ServerSocket new_sock;
    	          server.accept ( new_sock );

    	          try
    	            {
    	              while ( true )
    	                {
    	            	  float port0=pdp->GetCurrent(0);
						  float port1=pdp->GetCurrent(1);
						  float port2=pdp->GetCurrent(2);
						  float port3=pdp->GetCurrent(3);
						  float port4=pdp->GetCurrent(4);
						  float port5=pdp->GetCurrent(5);
						  float port6=pdp->GetCurrent(6);
						  float port7=pdp->GetCurrent(7);
						  float port8=pdp->GetCurrent(8);
						  float port9=pdp->GetCurrent(9);
						  float port10=pdp->GetCurrent(10);
						  float port11=pdp->GetCurrent(11);
						  float port12=pdp->GetCurrent(12);
						  float port13=pdp->GetCurrent(13);
						  float port14=pdp->GetCurrent(14);
						  float port15=pdp->GetCurrent(15);
						  int clawpos = 2;
						  float bath;
						  float voltage = pdp->GetVoltage()*-0.076875;
						  if(voltage >= 12.5)
						  {
							  bath = -160;
						  }
						  else{
							  bath = pdp->GetVoltage()*-0.076875;
						  }

						  int matchtime = hudtime.Get();

    	                  new_sock << std::to_string(clawpos) << " " << std::to_string(bath) << " " << std::to_string(matchtime) << " " << std::to_string(port0) << " " << std::to_string(port1) << " " << std::to_string(port2) << " " << std::to_string(port3) << " " << std::to_string(port4) << " " << std::to_string(port5) << " " << std::to_string(port6) << " " << std::to_string(port7) << " " << std::to_string(port8) << " " << std::to_string(port9) << " " << std::to_string(port10) << " " << std::to_string(port11) << " " << std::to_string(port12) << " " << std::to_string(port13) << " " << std::to_string(port14) << " " << std::to_string(port15) << "\n";
    	                }
    	            }
    	          catch ( SocketException& ) {}

    	        }
    	    }
    	  catch ( SocketException& e )
    	    {
    	      std::cout << "Exception was caught:" << e.description() << "\nExiting.\n";
    	    }
    	  return NULL;
    }
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
		pthread_t t;
		pthread_create(&t, NULL, HUD, NULL);

		        //Join the thread with the main thread
		pthread_join(t, NULL);



				    //Makes the main thread wait for the new thread to finish execution, therefore blocks its own execution.

	}

	int counter = 0;
	bool last;
	std::vector<float> throttleReadings;
	int size = 25;
	int times = 0;
	int count = 0;
	bool lastTime;
	void AutonomousInit	(){
		hudtime.Start();
	}

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
		if(i % 60 == 0)
			std::cout << leftJoy->GetY() << std::endl;
		i++;

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
			angle = -angle;
			if(angle < 0.0) {
				leftMotorOutput = (throttle + angle);
				rightMotorOutput = fmax(throttle, -angle);
			}
			else {
				leftMotorOutput = fmax(throttle, angle);
				rightMotorOutput = (throttle - angle);
			}
		}
		else {
		 	if(angle > 0.0) {
				leftMotorOutput = -fmax(-throttle, angle);
				rightMotorOutput = throttle + angle;
				std::cout << rightMotorOutput << std::endl;
			}
			else {
				leftMotorOutput = throttle - angle;
				rightMotorOutput = -fmax(-throttle,-angle);
			}

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
