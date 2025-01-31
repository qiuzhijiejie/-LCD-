/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
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
#include "stm32c0xx_hal.h"

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
#define LEDK_GPIO_O_P_Pin GPIO_PIN_9
#define LEDK_GPIO_O_P_GPIO_Port GPIOB
#define LCD_E_GPIO_O_P_Pin GPIO_PIN_14
#define LCD_E_GPIO_O_P_GPIO_Port GPIOC
#define LCD_RS_GPIO_O_P_Pin GPIO_PIN_15
#define LCD_RS_GPIO_O_P_GPIO_Port GPIOC
#define LCD_R_W_GPIO_O_P_Pin GPIO_PIN_0
#define LCD_R_W_GPIO_O_P_GPIO_Port GPIOA
#define LCD_RST_GPIO_O_P_Pin GPIO_PIN_1
#define LCD_RST_GPIO_O_P_GPIO_Port GPIOA
#define DB0_GPIO_O_P_Pin GPIO_PIN_4
#define DB0_GPIO_O_P_GPIO_Port GPIOA
#define DB1_GPIO_O_P_Pin GPIO_PIN_5
#define DB1_GPIO_O_P_GPIO_Port GPIOA
#define DB2_GPIO_O_P_Pin GPIO_PIN_6
#define DB2_GPIO_O_P_GPIO_Port GPIOA
#define DB3_GPIO_O_P_Pin GPIO_PIN_7
#define DB3_GPIO_O_P_GPIO_Port GPIOA
#define DISP_INT_Pin GPIO_PIN_0
#define DISP_INT_GPIO_Port GPIOB
#define DISP_EN_Pin GPIO_PIN_1
#define DISP_EN_GPIO_Port GPIOB
#define LCD_CS2_GPIO_O_P_Pin GPIO_PIN_2
#define LCD_CS2_GPIO_O_P_GPIO_Port GPIOB
#define DB4_GPIO_O_P_Pin GPIO_PIN_8
#define DB4_GPIO_O_P_GPIO_Port GPIOA
#define DB5_GPIO_O_P_Pin GPIO_PIN_9
#define DB5_GPIO_O_P_GPIO_Port GPIOA
#define LCD_CS1_GPIO_O_P_Pin GPIO_PIN_6
#define LCD_CS1_GPIO_O_P_GPIO_Port GPIOC
#define DB6_GPIO_O_P_Pin GPIO_PIN_10
#define DB6_GPIO_O_P_GPIO_Port GPIOA
#define DB7_GPIO_O_P_Pin GPIO_PIN_11
#define DB7_GPIO_O_P_GPIO_Port GPIOA
#define SW4_GPIO_I_P_Pin GPIO_PIN_3
#define SW4_GPIO_I_P_GPIO_Port GPIOB
#define SW3_GPIO_I_P_Pin GPIO_PIN_4
#define SW3_GPIO_I_P_GPIO_Port GPIOB
#define SW2_GPIO_I_P_Pin GPIO_PIN_5
#define SW2_GPIO_I_P_GPIO_Port GPIOB
#define SW1__GPIO_I_P_Pin GPIO_PIN_8
#define SW1__GPIO_I_P_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
