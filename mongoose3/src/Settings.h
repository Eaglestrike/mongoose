/*
 * Settings.h
 *
 *  Created on: Feb 12, 2015
 *      Author: Team 114
 */

#ifndef SETTINGS_H_
#define SETTINGS_H_

#define UNKNOWN_PORT 27

/*Auto*/
#define AUTO_MANTA_CORE 0
#define AUTO_DRIVE_STRAIGHT 1
#define AUTO_GRAB_TOTE 2
#define AUTO_MANTA_CORE_WITHOUT_BACK 3
#define AUTO_GRAB_THREE_TOTE 4
#define AUTO_DO_NOTHING -1

/*PRACTICE BOT POWER; CHANGE*/
#define ELEVATOR_DROP_POWER -0.2
#define CALIBRATE_ELEVATOR_DOWN -0.2
#define CALIBRATE_ELEVATOR_UP 0.4
#define MAX_ELEVATOR_UP 0.75
#define MAX_ELEVATOR_DOWN -0.3
#define MAX_ARM_POWER 1
#define MAX_ELEVATOR_INPUT 55
#define MIN_ELEVATOR_INPUT 0
#define ARM_DISTANCE_PER_PULSE .001

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
#define INCHES_PER_ELEVATOR_PULSE 0.0931677
#define PRACTICE_INCHES_PER_ELEVATOR_PULSE 0
#define ELEVATOR_P 0.206999
#define ELEVATOR_I 0.0012
#define ELEVATOR_D 0.157
#define ELEVATOR_LEVEL_0 0
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

#define RIGHT_ARM_2_KP 0.397614

#define LEFT_ARM_2_KP 0.321999
#define RIGHT_ARM_2_KI 0.0
#define LEFT_ARM_2_KI 0.0
#define RIGHT_ARM_2_KD 0.0
#define LEFT_ARM_2_KD 0.0
#define DIFF_ARM_2_KP 0.0
#define DIFF_ARM_2_KD 0.0
#define DIFF_ARM_2_KI 0.0

#define MAX_DELTA_X 12
#define OPEN_LEFT_SETPOINT 1
#define MAX_CALIBRATE_TIME_IN 0.50
#define MAX_CALIBRATE_TIME_OUT 4
#define ARM_CLOSED_TOTE_DISTANCE 3.2625
#define ARM_CLOSED_CONTAINER_DISTANCE 5
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
#define DRIVE_REAL_P 0.33009
#define DRIVE_REAL_I 0
#define DRIVE_REAL_D 0.00939999

#define ANGLE_REAL_P .0523
#define ANGLE_REAL_I 0
#define ANGLE_REAL_D 0.1091

#define FEET_PER_DRIVE_PULSE_2 0.00584
#define DRIVE_PRAC_P 0.138
#define DRIVE_PRAC_I 0
#define DRIVE_PRAC_D 0

#define ANGLE_PRAC_P 0.0333
#define ANGLE_PRAC_I 0
#define ANGLE_PRAC_D 0.1091

#define GYRO_ADJUSTMENT_REAL -.40315
#define GYRO_ADJUSTMENT_PRAC .20677

/*Intake*/
#define INTAKE_SOLENOID_1 1
#define INTAKE_SOLENOID_2 2
#define INTAKE_MOTOR_1 8
#define INTAKE_MOTOR_2 9 /*13*/


/*Logging*/
#define USB_DIRECTORY "/media/sda1"
#define BACKUP_DIRECTORY "/home/lvuser"



#endif /* SETTINGS_H_ */