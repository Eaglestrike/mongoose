/*
 * Settings.h
 *
 *  Created on: Feb 12, 2015
 *      Author: Team 114
 */

#ifndef SETTINGS_H_
#define SETTINGS_H_

#define UNKNOWN_PORT 11

#define MAX_ELEVATOR_DOWN -0.1
#define MAX_ELEVATOR_UP 1
#define MAX_ARM_POWER 1

#define SCORPION_PORT 0

/*Elevator*/
#define ELEVATOR_1 4
#define ELEVATOR_2 5
#define ELEVATOR_SAFTEY_BUTTON 3
#define ELEVATOR_ENCODER_A 1
#define ELEVATOR_ENCODER_B 2


/*Arm*/

#define LEFT_ARM_MOTOR 6
#define RIGHT_ARM_MOTOR 7
#define LEFT_ARM_BUTTON 0
#define MID_ARM_BUTTON 1
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
