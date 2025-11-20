/*
 * motor.c
 *
 *  Created on: Nov 14, 2025
 *      Author: vvyy
 */


#include "motor.h"

void Motor_On(void)
{
	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, 25);
	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, 25);
}

void Motor_Off(void)
{
	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, 0);
	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, 0);
}
void Motor_stop(void)
{

    HAL_GPIO_WritePin(AIN1_GPIO_Port, AIN1_Pin, SET);
    HAL_GPIO_WritePin(AIN2_GPIO_Port, AIN2_Pin, SET);
    HAL_GPIO_WritePin(BIN1_GPIO_Port, BIN1_Pin, RESET);
    HAL_GPIO_WritePin(BIN2_GPIO_Port, BIN2_Pin, RESET);

}
void Set_Speed(uint8_t side, int8_t duty) //side代表方向 A左0 B右1
{

    if(side == 0)
    {
        if(duty > 0)
        {

            __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, duty);
            HAL_GPIO_WritePin(AIN1_GPIO_Port, AIN1_Pin, SET);
            HAL_GPIO_WritePin(AIN2_GPIO_Port, AIN2_Pin, RESET);

        }
        else if(duty < 0)
        {
        	duty = -duty;
            __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, duty);
            HAL_GPIO_WritePin(AIN1_GPIO_Port, AIN1_Pin, RESET);
            HAL_GPIO_WritePin(AIN2_GPIO_Port, AIN2_Pin, SET);

        }
        else
        {
        	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, 0);
        }
    }
    else
    {
        if(duty > 0)
        {
            __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, duty);
            HAL_GPIO_WritePin(BIN1_GPIO_Port, BIN1_Pin, SET);
            HAL_GPIO_WritePin(BIN2_GPIO_Port, BIN2_Pin, RESET);

        }
        else if(duty < 0)
        {
        	duty = -duty;
            __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, duty);
            HAL_GPIO_WritePin(BIN1_GPIO_Port, BIN1_Pin, RESET);
            HAL_GPIO_WritePin(BIN2_GPIO_Port, BIN2_Pin, SET);

        }
        else
        {
        	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, 0);
        }
    }
}
void Motor_SetSpeed(int8_t Speed_L,int8_t Speed_R)
{
    Set_Speed(0,Speed_L);
    Set_Speed(1,Speed_R);
}
void L1(void)//左1量向左转弯
{
	Motor_SetSpeed(20,30);
}
void L2(void)
{
	Motor_SetSpeed(15,35);
}
void L3(void)
{
	Motor_SetSpeed(10,40);
}
void R1(void)
{
	Motor_SetSpeed(30,20);
}
void R2(void)
{
	Motor_SetSpeed(35,15);
}
void R3(void)
{
	Motor_SetSpeed(40,10);
}
void track(void)
{
	if((!HAL_GPIO_ReadPin(X4_GPIO_Port, X4_Pin) || !HAL_GPIO_ReadPin(X5_GPIO_Port, X5_Pin)) && HAL_GPIO_ReadPin(X1_GPIO_Port, X1_Pin) && HAL_GPIO_ReadPin(X1_GPIO_Port, X1_Pin) && HAL_GPIO_ReadPin(X2_GPIO_Port, X2_Pin)&& HAL_GPIO_ReadPin(X3_GPIO_Port, X3_Pin)  && HAL_GPIO_ReadPin(X6_GPIO_Port, X6_Pin)  && HAL_GPIO_ReadPin(X7_GPIO_Port, X7_Pin) && HAL_GPIO_ReadPin(X8_GPIO_Port, X8_Pin))
	{
		Motor_SetSpeed(25, 25);
	}
	if(!HAL_GPIO_ReadPin(X3_GPIO_Port, X3_Pin))
	{
		L1();
	}

	if(!HAL_GPIO_ReadPin(X2_GPIO_Port, X2_Pin))
	{
		L2();
	}

	if(!HAL_GPIO_ReadPin(X1_GPIO_Port, X1_Pin))
	{
		L3();
	}

	if(!HAL_GPIO_ReadPin(X6_GPIO_Port, X6_Pin))
	{
		R1();
	}

	if(!HAL_GPIO_ReadPin(X7_GPIO_Port, X7_Pin))
	{
		R2();
	}

	if(!HAL_GPIO_ReadPin(X8_GPIO_Port, X8_Pin))
	{
		R3();
	}


}


void track1(void)
{
	if(!HAL_GPIO_ReadPin(X1_GPIO_Port, X1_Pin))
	{
		L2();
	}

	if(!HAL_GPIO_ReadPin(X2_GPIO_Port, X2_Pin))
	{
		Motor_SetSpeed(25, 25);
	}

	if(!HAL_GPIO_ReadPin(X3_GPIO_Port, X3_Pin))
	{
		R2();
	}
}
void track2(void)
{
	if(HAL_GPIO_ReadPin(X1_GPIO_Port, X1_Pin))
	{
		L3();
	}

	if(HAL_GPIO_ReadPin(X2_GPIO_Port, X2_Pin) && !HAL_GPIO_ReadPin(X3_GPIO_Port, X3_Pin))
	{
		L1();
	}

	if(HAL_GPIO_ReadPin(X3_GPIO_Port, X3_Pin) && !HAL_GPIO_ReadPin(X1_GPIO_Port, X1_Pin) && !HAL_GPIO_ReadPin(X5_GPIO_Port, X5_Pin))
	{
		Motor_SetSpeed(25, 25);
	}

	if(HAL_GPIO_ReadPin(X4_GPIO_Port, X4_Pin) && !HAL_GPIO_ReadPin(X3_GPIO_Port, X3_Pin))
	{
		R1();
	}

	if(HAL_GPIO_ReadPin(X5_GPIO_Port, X5_Pin))
	{
		R3();
	}

}


