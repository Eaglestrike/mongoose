/*
 * ArmModule.h
 *
 *  Created on: Feb 13, 2015
 *      Author: Giggles Upanda
 */

#ifndef ARMMODULE_H_
#define ARMMODULE_H_

#include <WPIlib.h>
#include "RobotModule.h"
#include "../Peripherals/SafeTalonSRX.h"
#include "../Settings.h"
#include "../Error/CalibrationError.h"
#include "../Error/MovementError.h"


class ModifiedEncoder: public Encoder {
private:
	double addedDistance;
public:
	ModifiedEncoder(int portA, int portB, double addedDis) :
			Encoder(portA, portB) {
		addedDistance = addedDis;
	}

	double PIDGet() {
		return Encoder::PIDGet() + addedDistance;
	}
};

class ArmDifference: public PIDSource {
private:
	ModifiedEncoder* right;
	ModifiedEncoder* left;

public:
	ArmDifference(ModifiedEncoder* rE, ModifiedEncoder* le) {
		right = rE;
		left = le;
	}

	virtual ~ArmDifference(){}

	double PIDGet() {
		return right->PIDGet() - left->PIDGet();
	}
};

class ArmOut: public PIDOutput {
private:
	double power;

public:
	ArmOut(): power(0) {}
	virtual ~ArmOut(){}

	void PIDWrite(float output) {
		power = output;
	}

	double getPower() {
		return power;
	}
};

class ArmModule : public RobotModule{
public:
	ArmModule(int rightTalonPort, int leftTalonPort, int rightButtonPort, int midButtonPort, int leftButtonPort, int rEncoderA,
			int rEncoderB, int lEncoderA, int lEncoderB);
	virtual ~ArmModule();
	void setDeltaX(double deltaX);
	void disableDeltaX();
	void enablePID();
	void disablePID();
	void enable();
	void disable();
	void reset();
	void checkError();
	void handleFatalError();
	void setLeftArm(float setpoint);
	void setRightArm(float setpoint);
	void setLeftPower(float power);
	void setRightPower(float power);
	void calibrate();
	void setManual(bool man);

	bool getLeftButton();
	bool getMidButton();
	bool getRightButton();
	bool isManual();

	double getLeftPosition();
	double getRightPosition();
	double getLeftPower();
	double getRightPower();
	double getLeftSetpoint();
	double getDiffSetpoint();
	double getRightSetpoint();
	double getLeftError();
	double getDiffError();
	double getRightError();


	void grab(double deltaX);

private:
	void setSetPoint(float setPoint);

	SafeTalonSRX* m_Left_Talon;
	SafeTalonSRX* m_Right_Talon;
	DigitalInput* m_Saftey_Button;
	ModifiedEncoder* m_Left_Encoder;
	ModifiedEncoder* m_Right_Encoder;
	PIDController* m_Left_Arm_Controller;
	PIDController* m_Right_Arm_Controller;
	PIDController* m_Difference_Controller;
	ArmOut* m_Left_Output;
	ArmOut* m_Right_Output;
	ArmOut* m_Diff_Output;
	ArmDifference* m_Arm_Difference_Input;

	double m_DeltaX;
	bool m_Manual;
	bool m_Calibrating;
	bool m_Has_Calibrated;

};

#endif /* ARMMODULE_H_ */
