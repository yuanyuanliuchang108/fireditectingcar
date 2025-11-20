/*
 * motor.h
 *
 *  Created on: Nov 14, 2025
 *      Author: vvyy
 */

#ifndef INC_MOTOR_H_
#define INC_MOTOR_H_

#include "main.h"
#include "tim.h"
void Motor_On(void);
void Motor_Off(void);
void Set_Speed(uint8_t side, int8_t duty);
void Motor_SetSpeed(int8_t Speed_L,int8_t Speed_R);
void Motor_stop(void);

void L1(void);
void L2(void);
void L3(void);
void R1(void);
void R2(void);
void R3(void);

void track(void);
void track1(void);
void track2(void);
#endif /* INC_MOTOR_H_ */
