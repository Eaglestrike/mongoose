/*
 * Settings.h
 *
 *  Created on: Feb 12, 2015
 *      Author: Team 114
 */

#ifndef SETTINGS_H_
#define SETTINGS_H_

#define UNKNOWN_PORT 27

#define MAX_ELEVATOR_DOWN -0.3
#define CALIBRATE_ELEVATOR_DOWN 0
#define CALIBRATE_ELEVATOR_UP .3
#define MAX_ELEVATOR_UP 1
#define MAX_ARM_POWER 1

#define SCORPION_PORT 0

/*Elevator*/
#define ELEVATOR_1 4
#define ELEVATOR_2 5
#define ELEVATOR_SAFTEY_BUTTON 3
#define ELEVATOR_ENCODER_A 10
#define ELEVATOR_ENCODER_B 11
#define MAX_ELEVATOR_CALIBRATE_TIME_IN 0
#define MAX_ELEVATOR_CALIBRATE_TIME_OUT 3
#define MIN_ELEVATOR_DISTANCE_CALIBRATE 0.05

/*Arm*/

#define LEFT_ARM_MOTOR 6
#define RIGHT_ARM_MOTOR 7
#define LEFT_ARM_BUTTON 1
#define MID_ARM_BUTTON 0
#define RIGHT_ARM_BUTTON 2
#define LEFT_ARM_ENCODER_A 4
#define LEFT_ARM_ENCODER_B 5
#define RIGHT_ARM_ENCODER_A 6
#define RIGHT_ARM_ENCODER_B 7

#define RIGHT_ARM_1_KP 0.276498
#define LEFT_ARM_1_KP 0.387998
#define RIGHT_ARM_1_KI 0.0012
#define LEFT_ARM_1_KI 0.0012
#define RIGHT_ARM_1_KD 0.0
#define LEFT_ARM_1_KD 0.0262
#define DIFF_ARM_1_KP 0.0
#define DIFF_ARM_1_KD 0.2875
#define DIFF_ARM_1_KI 0.0

#define RIGHT_ARM_2_KP 0.0
#define LEFT_ARM_2_KP 0.0
#define RIGHT_ARM_2_KI 0.0
#define LEFT_ARM_2_KI 0.0
#define RIGHT_ARM_2_KD 0.0
#define LEFT_ARM_2_KD 0.0
#define DIFF_ARM_2_KP 0.0
#define DIFF_ARM_2_KD 0.0
#define DIFF_ARM_2_KI 0.0

#define MAX_DELTA_X 13.5
#define MAX_CALIBRATE_TIME_IN 0.5
#define MAX_CALIBRATE_TIME_OUT 4
#define MIN_CALIBRATION_DISTANCE 0.05
#define MAX_CALIBRATE_LEFT_POWER 0.45
#define MAX_CALIBRATE_RIGHT_POWER 0.5

/*Drive*/
#define DRIVE_LEFT_1 0
#define DRIVE_LEFT_2 1
#define DRIVE_RIGHT_1 2
#define DRIVE_RIGHT_2 3
#define DRIVE_ENCODER_A 8
#define DRIVE_ENCODER_B 9
#define DRIVE_GYRO 0

#define DRIVE_1_P 0
#define DRIVE_1_I 0
#define DRIVE_1_D 0

#define ANGLE_1_P 0.0286
#define ANGLE_1_I 0
#define ANGLE_1_D 0.1096

/*Intake*/
#define INTAKE_SOLENOID_1 1
#define INTAKE_SOLENOID_2 2
#define INTAKE_MOTOR_1 8
#define INTAKE_MOTOR_2 13

#endif /* SETTINGS_H_ */
