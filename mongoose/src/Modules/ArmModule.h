/*
 * ArmModule.h
 *
 *  Created on: Feb 13, 2015
 *      Author: Giggles Upanda
 */

#ifndef ARMMODULE_H_
#define ARMMODULE_H_
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
	double PIDGet() {
		return right->PIDGet() - left->PIDGet();
	}
};

class ArmOut: public PIDOutput {
private:
	double power;

public:
	ArmOut() {
	}
	void PIDWrite(float output) {
		power = output;
	}

	double getPower() {
		return power;
	}
};

class ArmModule : public RobotModule{
public:
	ArmModule(int rightTalonPort, int leftTalonPort, int rEncoderA,
			int rEncoderB, int lEncoderA, int lEncoderB);
	virtual ~ArmModule();
	void setDeltaX(double deltaX);
	void disableDeltaX();
	void enable();
	void disable();
	void setLeftArm(float setpoint);
	void setRightArm(float setpoint);

private:
	void setSetPoint(float setPoint);

	SafeTalonSRX* m_Right_Talon;
	SafeTalonSRX* m_Left_Talon;
	ModifiedEncoder* m_Right_Encoder;
	ModifiedEncoder* m_Left_Encoder;
	PIDController* m_Right_Arm_Controller;
	PIDController* m_Left_Arm_Controller;
	PIDController* m_Difference_Controller;
	ArmOut* m_Right_Output;
	ArmOut* m_Left_Output;
	ArmOut* m_Diff_Output;
	ArmDifference* m_Arm_Difference_Input;
	double m_DeltaX;

};

#endif /* ARMMODULE_H_ */
