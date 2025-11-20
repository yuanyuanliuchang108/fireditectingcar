/*
 * Buzzer.c
 *
 *  Created on: Nov 14, 2025
 *      Author: vvyy
 */

#include "Buzzer.h"

void buzzer_on()
{
	HAL_GPIO_WritePin(Buzzer_GPIO_Port, Buzzer_Pin, RESET);
}
void buzzer_off()
{
	HAL_GPIO_WritePin(Buzzer_GPIO_Port, Buzzer_Pin, SET);
}
