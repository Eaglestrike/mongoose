/*
 * Settings.h
 *
 *  Created on: Feb 12, 2015
 *      Author: Team 114
 */

#ifndef SETTINGS_H_
#define SETTINGS_H_

#define UNKNOWN_PORT 11

#define MAX_ELEVATOR_DOWN -0.05
#define MAX_ELEVATOR_UP 0.2
#define MAX_ARM_POWER 0.5

/*Elevator*/
#define ELEVATOR_1 4
#define ELEVATOR_2 5
#define ELEVATOR_SAFTEY_BUTTON 3
#define ELEVATOR_ENCODER_A 1
#define ELEVATOR_ENCODER_B 2


/*Arm*/

#define LEFT_ARM_MOTOR 6
#define RIGHT_ARM_MOTOR 7
#define LEFT_ARM_BUTTON 1
#define MID_ARM_BUTTON 0
#define RIGHT_ARM_BUTTON 2
#define LEFT_ARM_ENCODER_A UNKNOWN_PORT
#define LEFT_ARM_ENCODER_B UNKNOWN_PORT
#define RIGHT_ARM_ENCODER_A UNKNOWN_PORT
#define RIGHT_ARM_ENCODER_B UNKNOWN_PORT

#define RIGHT_ARM_1_KP 0.0
#define LEFT_ARM_1_KP 0.0
#define RIGHT_ARM_1_KI 0.0
#define LEFT_ARM_1_KI 0.0
#define RIGHT_ARM_1_KD 0.0
#define LEFT_ARM_1_KD 0.0
#define DIFF_ARM_1_KP 0.0
#define DIFF_ARM_1_KD 0.0
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

#define MAX_DELTA_X 14

/*Drive*/
#define DRIVE_LEFT_1 0
#define DRIVE_LEFT_2 1
#define DRIVE_RIGHT_1 2
#define DRIVE_RIGHT_2 3
#define DRIVE_ENCODER_A UNKNOWN_PORT
#define DRIVE_ENCODER_B 10
#define DRIVE_GYRO 0


#endif /* SETTINGS_H_ */
