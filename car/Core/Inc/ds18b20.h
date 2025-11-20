/*
 * ds18b20.h
 *
 *  Created on: Nov 13, 2025
 *      Author: vvyy
 */

#ifndef INC_DS18B20_H_
#define INC_DS18B20_H_


#include "gpio.h"
#include "main.h"
#include "delay.h"

/* PF口时钟使能 */
#define DS18B20_DQ_GPIO_CLK_ENABLE()  do{ __HAL_RCC_GPIOA_CLK_ENABLE(); }while(0)
/* IO操作函数 */

#define DS18B20_DQ1_OUT(x)   do{ x ? \
HAL_GPIO_WritePin(DQ1_GPIO_Port, DQ1_Pin, GPIO_PIN_SET):\
HAL_GPIO_WritePin(DQ1_GPIO_Port, DQ1_Pin, GPIO_PIN_RESET);\
}while(0)        /* 数据端口输出 */

#define DS18B20_DQ2_OUT(x)   do{ x ? \
HAL_GPIO_WritePin(DQ2_GPIO_Port, DQ2_Pin, GPIO_PIN_SET):\
HAL_GPIO_WritePin(DQ2_GPIO_Port, DQ2_Pin, GPIO_PIN_RESET);\
}while(0)        /* 数据端口输出 */

#define DS18B20_DQ3_OUT(x)   do{ x ? \
HAL_GPIO_WritePin(DQ3_GPIO_Port, DQ3_Pin, GPIO_PIN_SET):\
HAL_GPIO_WritePin(DQ3_GPIO_Port, DQ3_Pin, GPIO_PIN_RESET);\
}while(0)        /* 数据端口输出 */

/* 数据端口输入 */
#define DS18B20_DQ1_IN  HAL_GPIO_ReadPin(DQ1_GPIO_Port, DQ1_Pin)
#define DS18B20_DQ2_IN  HAL_GPIO_ReadPin(DQ2_GPIO_Port, DQ2_Pin)
#define DS18B20_DQ3_IN  HAL_GPIO_ReadPin(DQ3_GPIO_Port, DQ3_Pin)
uint8_t ds18b20_init_1(void); /* 初始化DS18B20 */
uint8_t ds18b20_init_2(void); /* 初始化DS18B20 */
uint8_t ds18b20_init_3(void); /* 初始化DS18B20 */
uint8_t ds18b20_check_1(void); /* 检测是否存在DS18B20 */
uint8_t ds18b20_check_2(void); /* 检测是否存在DS18B20 */
uint8_t ds18b20_check_3(void); /* 检测是否存在DS18B20 */
short ds18b20_get_temperature_1(void);/* 获取温度 */
short ds18b20_get_temperature_2(void);/* 获取温度 */
short ds18b20_get_temperature_3(void);/* 获取温度 */
#endif
