/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "adc.h"
#include "i2c.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "oled.h"
#include "stdio.h"
#include "ds18b20.h"
#include <stdint.h>
#include "delay.h"
#include "motor.h"
#include "Buzzer.h"
#include "stm32f1xx_it.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

typedef struct {
    uint8_t start;         // 起始符 0x5A
    uint8_t temp_high;     // 温度高字节
    uint8_t temp_low;      // 温度低字节
    uint8_t smoke_high;    // 烟雾浓度高字节
    uint8_t smoke_low;     // 烟雾浓度低字节
    uint8_t fire;          // 火灾状态（0=no，1=yes）
    uint8_t distance[3];   // 保留位（填 0x00）
    uint8_t checksum;      // 校验和
} DataPacket;

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

uint8_t calculate_checksum(DataPacket* packet) {
    uint8_t* data = (uint8_t*)packet;
    uint8_t sum = 0;
    for (int i = 0; i < 9; i++) {
        sum += data[i];
    }
    return sum;
}

void send_data(uint16_t temp, uint16_t smoke, uint8_t fire,uint32_t distance) {
    DataPacket packet;
    // 填充数据
    packet.start = 0x5A;
    packet.temp_high = (temp >> 8) & 0xFF;  // 温度高字节
    packet.temp_low = temp & 0xFF;          // 温度低字节
    packet.smoke_high = (smoke >> 8) & 0xFF;// 烟雾高字节
    packet.smoke_low = smoke & 0xFF;        // 烟雾低字节
    packet.fire = fire;
    packet.distance[0] = (distance >> 16) & 0xFF;
    packet.distance[1] = (distance >> 8) & 0xFF;
    packet.distance[2] = distance & 0xFF;
    // 计算校验和
    packet.checksum = calculate_checksum(&packet);

    // 串口发送（USART1，超时 100ms）
    HAL_UART_Transmit(&huart3, (uint8_t*)&packet, sizeof(DataPacket),100);
}

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
char mq2[20]="";
char dis[20]="";
char tem1[20]="";
char tem2[20]="";
char tem3[20]="";
char fs[20]="";
char keys[20]="";
/* 这里使用重定义函数以及其他函数定义 */

/* 超声波用 */
int upEdge = 0;
int downEdge = 0;
float distance = 0;
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)//超声波用
{
	if (htim == &htim1 && htim->Channel == HAL_TIM_ACTIVE_CHANNEL_4)
	{
		upEdge = HAL_TIM_ReadCapturedValue(&htim1, TIM_CHANNEL_3);//频道3接收上升沿
		downEdge = HAL_TIM_ReadCapturedValue(&htim1, TIM_CHANNEL_4);//频道4接收下降沿
		distance = (downEdge - upEdge) * 0.034 / 2;//计算距离
	}
}
/* 超声波用 */
uint16_t temperature1 = 0;
uint16_t temperature2 = 0;
uint16_t temperature3 = 0;
uint16_t temperature = 0;
uint16_t adc_mq2 = 0;
uint8_t fs1 = 0;
uint8_t fs2 = 0;
uint8_t fs3 = 0;
uint8_t fs_state = 0;
uint8_t fire_state = 0;
uint8_t t = 0;
uint16_t tmep= 0;
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if (htim == &htim4)
	{
		send_data(temperature,adc_mq2,fire_state,distance*10);

	}
}
uint16_t max(uint16_t a,uint16_t b, uint16_t c)
{
	uint16_t max_val = a;
	if(b > max_val){max_val = b;}
	if(c > max_val){max_val = c;}
	return max_val;
}
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_I2C2_Init();
  MX_ADC1_Init();
  MX_USART3_UART_Init();
  MX_TIM1_Init();
  MX_TIM3_Init();
  MX_TIM4_Init();
  /* USER CODE BEGIN 2 */

  //这里写上初始化代码
  HAL_Delay(50);
  OLED_Init();
  HAL_Delay(50);
  HAL_ADCEx_Calibration_Start(&hadc1);//ADC校准初始化
  HAL_TIM_Base_Start(&htim1);//超声传感器定时器启动初始化
  HAL_TIM_IC_Start(&htim1, TIM_CHANNEL_3);
  HAL_TIM_IC_Start_IT(&htim1, TIM_CHANNEL_4);

  HAL_TIM_Base_Start_IT(&htim4);//定时器中断发送

  HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
  HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2);
  ds18b20_init_1();
  Motor_stop();
  buzzer_off();
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	/* 小车 */


	if(key == 1)
	{
		buzzer_off();
		fire_state = 0;
		track2();
		if(fs1 || fs2 || fs3 ||  adc_mq2>=50)
		{
		 buzzer_on();
		 Motor_stop();
		 key = 0;
		 fire_state = 1;
		}
	}

		/* 小车 */

	/* 超声波模块用 */
	 HAL_GPIO_WritePin(Trig_GPIO_Port, Trig_Pin, GPIO_PIN_SET);
	 HAL_Delay(1);
	 HAL_GPIO_WritePin(Trig_GPIO_Port, Trig_Pin, GPIO_PIN_RESET);
	 __HAL_TIM_SET_COUNTER(&htim1, 0);

	/* 超声波模块用 */

	/* 温度传感器用 */

	  while(t>=20){t++;}
	  t = 0;
	  temperature1= ds18b20_get_temperature_1()/10;			    /* 获取温度值*/
	  if(temperature1>=10000){temperature1 = 25;}
	  while(t>=20){t++;}
	  t = 0;
	  temperature2= ds18b20_get_temperature_2()/10;			    /* 获取温度值*/
	  if(temperature2>=10000){temperature2 = 25;}
	  while(t>=20){t++;}
	  t = 0;
	  temperature3= ds18b20_get_temperature_3()/10;			    /* 获取温度值*/
	  if(temperature3>=10000){temperature3 = 25;}
	  temperature = max(temperature1, temperature2, temperature3);
	  if(temperature>=10000){temperature = 25;}


	/* 温度传感器用 */

	/* MQ2 烟雾传感器用 */
	 adc_mq2 = ADC_IN_1()/100;
	/* MQ2 烟雾传感器用 */



	/* 火焰传感器用 */
	 if(!HAL_GPIO_ReadPin(MH1_GPIO_Port, MH1_Pin)){fs1 = 1;}else{fs1 = 0;}
	 if(!HAL_GPIO_ReadPin(MH2_GPIO_Port, MH2_Pin)){fs2 = 1;}else{fs2 = 0;}
	 if(!HAL_GPIO_ReadPin(MH3_GPIO_Port, MH3_Pin)){fs3 = 1;}else{fs3 = 0;}
	/* 火焰传感器用 */

	/* OLED显示用 */

  	 OLED_NewFrame();
	 sprintf(tem1, "tem1:%u",temperature1);
	 OLED_PrintASCIIString(0, 0, tem1,&afont8x6 , OLED_COLOR_NORMAL);
	 sprintf(tem2, "tem2:%u",temperature2);
	 OLED_PrintASCIIString(0, 8, tem2, &afont8x6, OLED_COLOR_NORMAL);
	 sprintf(tem3, "tem3:%u",temperature3);
	 OLED_PrintASCIIString(0, 16, tem3, &afont8x6, OLED_COLOR_NORMAL);
	 sprintf(mq2,"smoke:%u", adc_mq2);
	 OLED_PrintASCIIString(0, 24, mq2, &afont8x6, OLED_COLOR_NORMAL);
	 sprintf(dis,"distance:%.1fcm",distance);
	 OLED_PrintASCIIString(0, 32, dis, &afont8x6, OLED_COLOR_NORMAL);
	 sprintf(fs,"fs:%u",fire_state);
	 OLED_PrintASCIIString(0, 40, fs, &afont8x6, OLED_COLOR_NORMAL);
	 sprintf(keys,"key:%u",key);
	 OLED_PrintASCIIString(0, 48, keys, &afont8x6, OLED_COLOR_NORMAL);

	 OLED_ShowFrame();

	/* OLED显示用 */



    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_ADC;
  PeriphClkInit.AdcClockSelection = RCC_ADCPCLK2_DIV6;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}
#ifdef USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
