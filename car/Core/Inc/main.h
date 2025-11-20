/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define Key_Pin GPIO_PIN_2
#define Key_GPIO_Port GPIOC
#define Key_EXTI_IRQn EXTI2_IRQn
#define AIN1_Pin GPIO_PIN_3
#define AIN1_GPIO_Port GPIOC
#define MQ2_DO_Pin GPIO_PIN_1
#define MQ2_DO_GPIO_Port GPIOA
#define DQ1_Pin GPIO_PIN_2
#define DQ1_GPIO_Port GPIOA
#define DQ2_Pin GPIO_PIN_3
#define DQ2_GPIO_Port GPIOA
#define DQ3_Pin GPIO_PIN_4
#define DQ3_GPIO_Port GPIOA
#define MH1_Pin GPIO_PIN_5
#define MH1_GPIO_Port GPIOA
#define MH2_Pin GPIO_PIN_6
#define MH2_GPIO_Port GPIOA
#define MH3_Pin GPIO_PIN_7
#define MH3_GPIO_Port GPIOA
#define AIN2_Pin GPIO_PIN_4
#define AIN2_GPIO_Port GPIOC
#define BIN1_Pin GPIO_PIN_5
#define BIN1_GPIO_Port GPIOC
#define X1_Pin GPIO_PIN_0
#define X1_GPIO_Port GPIOB
#define X2_Pin GPIO_PIN_1
#define X2_GPIO_Port GPIOB
#define OLED_SCL_Pin GPIO_PIN_10
#define OLED_SCL_GPIO_Port GPIOB
#define OLED_SDA_Pin GPIO_PIN_11
#define OLED_SDA_GPIO_Port GPIOB
#define X5_Pin GPIO_PIN_12
#define X5_GPIO_Port GPIOB
#define X6_Pin GPIO_PIN_13
#define X6_GPIO_Port GPIOB
#define X7_Pin GPIO_PIN_14
#define X7_GPIO_Port GPIOB
#define X8_Pin GPIO_PIN_15
#define X8_GPIO_Port GPIOB
#define PWM1_Pin GPIO_PIN_6
#define PWM1_GPIO_Port GPIOC
#define PWM2_Pin GPIO_PIN_7
#define PWM2_GPIO_Port GPIOC
#define BIN2_Pin GPIO_PIN_8
#define BIN2_GPIO_Port GPIOC
#define Trig_Pin GPIO_PIN_9
#define Trig_GPIO_Port GPIOC
#define Buzzer_Pin GPIO_PIN_9
#define Buzzer_GPIO_Port GPIOA
#define Echo_Pin GPIO_PIN_10
#define Echo_GPIO_Port GPIOA
#define X3_Pin GPIO_PIN_8
#define X3_GPIO_Port GPIOB
#define X4_Pin GPIO_PIN_9
#define X4_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
