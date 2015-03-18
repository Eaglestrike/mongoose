/*
 * Settings.h
 *
 *  Created on: Feb 12, 2015
 *      Author: Team 114
 */

#ifndef SETTINGS_H_
#define SETTINGS_H_

#define UNKNOWN_PORT 27


/*PRACTICE BOT POWER; CHANGE*/
#define ELEVATOR_DROP_POWER -0.2
#define MAX_ELEVATOR_DOWN -0.2
#define CALIBRATE_ELEVATOR_DOWN -0.4
#define CALIBRATE_ELEVATOR_UP 0.7
#define MAX_ELEVATOR_UP 1
#define MAX_ARM_POWER 1
#define MAX_ELEVATOR_INPUT 55
#define MIN_ELEVATOR_INPUT 0

#define SCORPION_PORT 0
#define MANTA_CORE_SPIKE_PORT 0

/*Elevator*/
#define ELEVATOR_1 4
#define ELEVATOR_2 5
#define ELEVATOR_SAFTEY_BUTTON 3
#define ELEVATOR_ENCODER_A 10
#define ELEVATOR_ENCODER_B 11
#define MAX_ELEVATOR_CALIBRATE_TIME_UP 0.35
#define MAX_ELEVATOR_CALIBRATE_TIME_DOWN 5
#define MIN_ELEVATOR_DISTANCE_CALIBRATE 0.1
#define INCHES_PER_ELEVATOR_PULSE 0.023329
#define ELEVATOR_P 0.206999
#define ELEVATOR_I 0.0012
#define ELEVATOR_D 0.157
#define ELEVATOR_LEVEL_1 0
#define ELEVATOR_LEVEL_2 0
#define ELEVATOR_LEVEL_3 0

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

#define MAX_DELTA_X 12
#define OPEN_LEFT_SETPOINT 1
#define MAX_CALIBRATE_TIME_IN 0.5
#define MAX_CALIBRATE_TIME_OUT 4
#define ARM_CLOSED_TOTE_DISTANCE 3.7625
#define ARM_CLOSED_CONTAINER_DISTANCE 0
#define MIN_CALIBRATION_DISTANCE 0.05
#define MAX_CALIBRATE_LEFT_POWER 0.5
#define MAX_CALIBRATE_RIGHT_POWER 0.5

/*Drive*/
#define DRIVE_LEFT_1 0
#define DRIVE_LEFT_2 1
#define DRIVE_RIGHT_1 2
#define DRIVE_RIGHT_2 3
#define DRIVE_ENCODER_A 8
#define DRIVE_ENCODER_B 9
#define DRIVE_GYRO 0

#define FEET_PER_DRIVE_PULSE 0.00584
#define DRIVE_1_P 0.33009
#define DRIVE_1_I 0
#define DRIVE_1_D 0.00939999

#define ANGLE_1_P 0.0333
#define ANGLE_1_I 0
#define ANGLE_1_D 0.1091

/*Intake*/
#define INTAKE_SOLENOID_1 1
#define INTAKE_SOLENOID_2 2
#define INTAKE_MOTOR_1 8
#define INTAKE_MOTOR_2 13


/*Logging*/
#define USB_DIRECTORY "/media/sda1"
#define BACKUP_DIRECTORY "/home/lvuser/logs"



#endif /* SETTINGS_H_ */
