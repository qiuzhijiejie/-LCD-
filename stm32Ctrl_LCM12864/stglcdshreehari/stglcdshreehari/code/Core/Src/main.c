/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include <MATH.H>

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

UART_HandleTypeDef huart1;
UART_HandleTypeDef huart2;
unsigned char Page;
unsigned char Col;
//unsigned char code font[];
//unsigned char code Character[];

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_USART2_UART_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */



const uint16_t font[] = {
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,  // sp
0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x0000, 0x1000, 0x0000, 0x0000,  // !
0x2800, 0x2800, 0x2800, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,  // "
0x2400, 0x2400, 0x7C00, 0x2400, 0x4800, 0x7C00, 0x4800, 0x4800, 0x0000, 0x0000,  // #
0x3800, 0x5400, 0x5000, 0x3800, 0x1400, 0x5400, 0x5400, 0x3800, 0x1000, 0x0000,  // $
0x2000, 0x5400, 0x5800, 0x3000, 0x2800, 0x5400, 0x1400, 0x0800, 0x0000, 0x0000,  // %
0x1000, 0x2800, 0x2800, 0x1000, 0x3400, 0x4800, 0x4800, 0x3400, 0x0000, 0x0000,  // &
0x1000, 0x1000, 0x1000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,  // '
0x0800, 0x1000, 0x2000, 0x2000, 0x2000, 0x2000, 0x2000, 0x2000, 0x1000, 0x0800,  // (
0x2000, 0x1000, 0x0800, 0x0800, 0x0800, 0x0800, 0x0800, 0x0800, 0x1000, 0x2000,  // )
0x1000, 0x3800, 0x1000, 0x2800, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,  // *
0x0000, 0x0000, 0x1000, 0x1000, 0x7C00, 0x1000, 0x1000, 0x0000, 0x0000, 0x0000,  // +
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x1000, 0x1000, 0x1000,  // ,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x3800, 0x0000, 0x0000, 0x0000, 0x0000,  // -
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x1000, 0x0000, 0x0000,  // .
0x0800, 0x0800, 0x1000, 0x1000, 0x1000, 0x1000, 0x2000, 0x2000, 0x0000, 0x0000,  // /
0x3800, 0x4400, 0x4400, 0x5400, 0x4400, 0x4400, 0x4400, 0x3800, 0x0000, 0x0000,  // 0
0x1000, 0x3000, 0x5000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x0000, 0x0000,  // 1
0x3800, 0x4400, 0x4400, 0x0400, 0x0800, 0x1000, 0x2000, 0x7C00, 0x0000, 0x0000,  // 2
0x3800, 0x4400, 0x0400, 0x1800, 0x0400, 0x0400, 0x4400, 0x3800, 0x0000, 0x0000,  // 3
0x0800, 0x1800, 0x2800, 0x2800, 0x4800, 0x7C00, 0x0800, 0x0800, 0x0000, 0x0000,  // 4
0x7C00, 0x4000, 0x4000, 0x7800, 0x0400, 0x0400, 0x4400, 0x3800, 0x0000, 0x0000,  // 5
0x3800, 0x4400, 0x4000, 0x7800, 0x4400, 0x4400, 0x4400, 0x3800, 0x0000, 0x0000,  // 6
0x7C00, 0x0400, 0x0800, 0x1000, 0x1000, 0x2000, 0x2000, 0x2000, 0x0000, 0x0000,  // 7
0x3800, 0x4400, 0x4400, 0x3800, 0x4400, 0x4400, 0x4400, 0x3800, 0x0000, 0x0000,  // 8
0x3800, 0x4400, 0x4400, 0x4400, 0x3C00, 0x0400, 0x4400, 0x3800, 0x0000, 0x0000,  // 9
0x0000, 0x0000, 0x1000, 0x0000, 0x0000, 0x0000, 0x0000, 0x1000, 0x0000, 0x0000,  // :
0x0000, 0x0000, 0x0000, 0x1000, 0x0000, 0x0000, 0x0000, 0x1000, 0x1000, 0x1000,  // ;
0x0000, 0x0000, 0x0C00, 0x3000, 0x4000, 0x3000, 0x0C00, 0x0000, 0x0000, 0x0000,  // <
0x0000, 0x0000, 0x0000, 0x7C00, 0x0000, 0x7C00, 0x0000, 0x0000, 0x0000, 0x0000,  // =
0x0000, 0x0000, 0x6000, 0x1800, 0x0400, 0x1800, 0x6000, 0x0000, 0x0000, 0x0000,  // >
0x3800, 0x4400, 0x0400, 0x0800, 0x1000, 0x1000, 0x0000, 0x1000, 0x0000, 0x0000,  // ?
0x3800, 0x4400, 0x4C00, 0x5400, 0x5C00, 0x4000, 0x4000, 0x3800, 0x0000, 0x0000,  // @
0x1000, 0x2800, 0x2800, 0x2800, 0x2800, 0x7C00, 0x4400, 0x4400, 0x0000, 0x0000,  // A
0x7800, 0x4400, 0x4400, 0x7800, 0x4400, 0x4400, 0x4400, 0x7800, 0x0000, 0x0000,  // B
0x3800, 0x4400, 0x4000, 0x4000, 0x4000, 0x4000, 0x4400, 0x3800, 0x0000, 0x0000,  // C
0x7000, 0x4800, 0x4400, 0x4400, 0x4400, 0x4400, 0x4800, 0x7000, 0x0000, 0x0000,  // D
0x7C00, 0x4000, 0x4000, 0x7C00, 0x4000, 0x4000, 0x4000, 0x7C00, 0x0000, 0x0000,  // E
0x7C00, 0x4000, 0x4000, 0x7800, 0x4000, 0x4000, 0x4000, 0x4000, 0x0000, 0x0000,  // F
0x3800, 0x4400, 0x4000, 0x4000, 0x5C00, 0x4400, 0x4400, 0x3800, 0x0000, 0x0000,  // G
0x4400, 0x4400, 0x4400, 0x7C00, 0x4400, 0x4400, 0x4400, 0x4400, 0x0000, 0x0000,  // H
0x3800, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x3800, 0x0000, 0x0000,  // I
0x0400, 0x0400, 0x0400, 0x0400, 0x0400, 0x0400, 0x4400, 0x3800, 0x0000, 0x0000,  // J
0x4400, 0x4800, 0x5000, 0x6000, 0x5000, 0x4800, 0x4800, 0x4400, 0x0000, 0x0000,  // K
0x4000, 0x4000, 0x4000, 0x4000, 0x4000, 0x4000, 0x4000, 0x7C00, 0x0000, 0x0000,  // L
0x4400, 0x6C00, 0x6C00, 0x5400, 0x4400, 0x4400, 0x4400, 0x4400, 0x0000, 0x0000,  // M
0x4400, 0x6400, 0x6400, 0x5400, 0x5400, 0x4C00, 0x4C00, 0x4400, 0x0000, 0x0000,  // N
0x3800, 0x4400, 0x4400, 0x4400, 0x4400, 0x4400, 0x4400, 0x3800, 0x0000, 0x0000,  // O
0x7800, 0x4400, 0x4400, 0x4400, 0x7800, 0x4000, 0x4000, 0x4000, 0x0000, 0x0000,  // P
0x3800, 0x4400, 0x4400, 0x4400, 0x4400, 0x4400, 0x5400, 0x3800, 0x0400, 0x0000,  // Q
0x7800, 0x4400, 0x4400, 0x4400, 0x7800, 0x4800, 0x4800, 0x4400, 0x0000, 0x0000,  // R
0x3800, 0x4400, 0x4000, 0x3000, 0x0800, 0x0400, 0x4400, 0x3800, 0x0000, 0x0000,  // S
0x7C00, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x0000, 0x0000,  // T
0x4400, 0x4400, 0x4400, 0x4400, 0x4400, 0x4400, 0x4400, 0x3800, 0x0000, 0x0000,  // U
0x4400, 0x4400, 0x4400, 0x2800, 0x2800, 0x2800, 0x1000, 0x1000, 0x0000, 0x0000,  // V
0x4400, 0x4400, 0x5400, 0x5400, 0x5400, 0x6C00, 0x2800, 0x2800, 0x0000, 0x0000,  // W
0x4400, 0x2800, 0x2800, 0x1000, 0x1000, 0x2800, 0x2800, 0x4400, 0x0000, 0x0000,  // X
0x4400, 0x4400, 0x2800, 0x2800, 0x1000, 0x1000, 0x1000, 0x1000, 0x0000, 0x0000,  // Y
0x7C00, 0x0400, 0x0800, 0x1000, 0x1000, 0x2000, 0x4000, 0x7C00, 0x0000, 0x0000,  // Z
0x1800, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1800,  // [
0x2000, 0x2000, 0x1000, 0x1000, 0x1000, 0x1000, 0x0800, 0x0800, 0x0000, 0x0000,  /* \ */
0x3000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x3000,  // ]
0x1000, 0x2800, 0x2800, 0x4400, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,  // ^
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xFE00,  // _
0x2000, 0x1000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,  // `
0x0000, 0x0000, 0x3800, 0x4400, 0x3C00, 0x4400, 0x4C00, 0x3400, 0x0000, 0x0000,  // a
0x4000, 0x4000, 0x5800, 0x6400, 0x4400, 0x4400, 0x6400, 0x5800, 0x0000, 0x0000,  // b
0x0000, 0x0000, 0x3800, 0x4400, 0x4000, 0x4000, 0x4400, 0x3800, 0x0000, 0x0000,  // c
0x0400, 0x0400, 0x3400, 0x4C00, 0x4400, 0x4400, 0x4C00, 0x3400, 0x0000, 0x0000,  // d
0x0000, 0x0000, 0x3800, 0x4400, 0x7C00, 0x4000, 0x4400, 0x3800, 0x0000, 0x0000,  // e
0x0C00, 0x1000, 0x7C00, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x0000, 0x0000,  // f
0x0000, 0x0000, 0x3400, 0x4C00, 0x4400, 0x4400, 0x4C00, 0x3400, 0x0400, 0x7800,  // g
0x4000, 0x4000, 0x5800, 0x6400, 0x4400, 0x4400, 0x4400, 0x4400, 0x0000, 0x0000,  // h
0x1000, 0x0000, 0x7000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x0000, 0x0000,  // i
0x1000, 0x0000, 0x7000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0xE000,  // j
0x4000, 0x4000, 0x4800, 0x5000, 0x6000, 0x5000, 0x4800, 0x4400, 0x0000, 0x0000,  // k
0x7000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x0000, 0x0000,  // l
0x0000, 0x0000, 0x7800, 0x5400, 0x5400, 0x5400, 0x5400, 0x5400, 0x0000, 0x0000,  // m
0x0000, 0x0000, 0x5800, 0x6400, 0x4400, 0x4400, 0x4400, 0x4400, 0x0000, 0x0000,  // n
0x0000, 0x0000, 0x3800, 0x4400, 0x4400, 0x4400, 0x4400, 0x3800, 0x0000, 0x0000,  // o
0x0000, 0x0000, 0x5800, 0x6400, 0x4400, 0x4400, 0x6400, 0x5800, 0x4000, 0x4000,  // p
0x0000, 0x0000, 0x3400, 0x4C00, 0x4400, 0x4400, 0x4C00, 0x3400, 0x0400, 0x0400,  // q
0x0000, 0x0000, 0x5800, 0x6400, 0x4000, 0x4000, 0x4000, 0x4000, 0x0000, 0x0000,  // r
0x0000, 0x0000, 0x3800, 0x4400, 0x3000, 0x0800, 0x4400, 0x3800, 0x0000, 0x0000,  // s
0x2000, 0x2000, 0x7800, 0x2000, 0x2000, 0x2000, 0x2000, 0x1800, 0x0000, 0x0000,  // t
0x0000, 0x0000, 0x4400, 0x4400, 0x4400, 0x4400, 0x4C00, 0x3400, 0x0000, 0x0000,  // u
0x0000, 0x0000, 0x4400, 0x4400, 0x2800, 0x2800, 0x2800, 0x1000, 0x0000, 0x0000,  // v
0x0000, 0x0000, 0x5400, 0x5400, 0x5400, 0x6C00, 0x2800, 0x2800, 0x0000, 0x0000,  // w
0x0000, 0x0000, 0x4400, 0x2800, 0x1000, 0x1000, 0x2800, 0x4400, 0x0000, 0x0000,  // x
0x0000, 0x0000, 0x4400, 0x4400, 0x2800, 0x2800, 0x1000, 0x1000, 0x1000, 0x6000,  // y
0x0000, 0x0000, 0x7C00, 0x0800, 0x1000, 0x2000, 0x4000, 0x7C00, 0x0000, 0x0000,  // z
0x1800, 0x1000, 0x1000, 0x1000, 0x2000, 0x2000, 0x1000, 0x1000, 0x1000, 0x1800,  // {
0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000,  // |
0x3000, 0x1000, 0x1000, 0x1000, 0x0800, 0x0800, 0x1000, 0x1000, 0x1000, 0x3000,  // }
0x0000, 0x0000, 0x0000, 0x7400, 0x4C00, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,  // ~
};


uint8_t ReadDataFromPins(void)
	  {
	      uint8_t RDFP_temp = 0;
	        // Set each pin high individually

	      	HAL_GPIO_WritePin(GPIOA, DB0_Pin, GPIO_PIN_SET);
	        HAL_GPIO_WritePin(GPIOA, DB1_Pin, GPIO_PIN_SET);
	        HAL_GPIO_WritePin(GPIOA, DB2_Pin, GPIO_PIN_SET);
	        HAL_GPIO_WritePin(GPIOA, DB3_Pin, GPIO_PIN_SET);
	        HAL_GPIO_WritePin(GPIOA, DB4_Pin, GPIO_PIN_SET);
	        HAL_GPIO_WritePin(GPIOA, DB5_Pin, GPIO_PIN_SET);
	        HAL_GPIO_WritePin(GPIOA, DB6_Pin, GPIO_PIN_SET);
	        HAL_GPIO_WritePin(GPIOA, DB7_Pin, GPIO_PIN_SET);


	      // Read each pin and combine the result
	      RDFP_temp |= (HAL_GPIO_ReadPin(GPIOA, DB0_Pin) == GPIO_PIN_SET) ? (1 << 0) : 0;
	      RDFP_temp |= (HAL_GPIO_ReadPin(GPIOA, DB1_Pin) == GPIO_PIN_SET) ? (1 << 1) : 0;
	      RDFP_temp |= (HAL_GPIO_ReadPin(GPIOA, DB2_Pin) == GPIO_PIN_SET) ? (1 << 2) : 0;
	      RDFP_temp |= (HAL_GPIO_ReadPin(GPIOA, DB3_Pin) == GPIO_PIN_SET) ? (1 << 3) : 0;
	      RDFP_temp |= (HAL_GPIO_ReadPin(GPIOA, DB4_Pin) == GPIO_PIN_SET) ? (1 << 4) : 0;
	      RDFP_temp |= (HAL_GPIO_ReadPin(GPIOA, DB5_Pin) == GPIO_PIN_SET) ? (1 << 5) : 0;
	      RDFP_temp |= (HAL_GPIO_ReadPin(GPIOA, DB6_Pin) == GPIO_PIN_SET) ? (1 << 6) : 0;
	      RDFP_temp |= (HAL_GPIO_ReadPin(GPIOA, DB7_Pin) == GPIO_PIN_SET) ? (1 << 7) : 0;

	      return RDFP_temp;
	  }

////////////////////////////////////////////////////////////////////////////////////////////
void Printdata(unsigned char data)
{

	if((data&0x01)==0x01)
	{
		HAL_GPIO_WritePin(GPIOA, DB0_Pin, GPIO_PIN_SET);
	}
	else{
		HAL_GPIO_WritePin(GPIOA, DB0_Pin, GPIO_PIN_RESET);
	}

	if((data&0x02)==0x02)
	{
		HAL_GPIO_WritePin(GPIOA, DB1_Pin, GPIO_PIN_SET);
	}
	else{
		HAL_GPIO_WritePin(GPIOA, DB1_Pin, GPIO_PIN_RESET);
	}

	if((data&0x04)==0x04)
	{
		HAL_GPIO_WritePin(GPIOA, DB2_Pin, GPIO_PIN_SET);
	}
	else{HAL_GPIO_WritePin(GPIOA, DB2_Pin, GPIO_PIN_RESET);}

	if((data&0x08)==0x08)
	{
		HAL_GPIO_WritePin(GPIOA, DB3_Pin, GPIO_PIN_SET);
	}
	else{HAL_GPIO_WritePin(GPIOA, DB3_Pin, GPIO_PIN_RESET);}

	if((data&0x10)==0x10)
	{
		HAL_GPIO_WritePin(GPIOA, DB4_Pin, GPIO_PIN_SET);
	}
	else{HAL_GPIO_WritePin(GPIOA, DB4_Pin, GPIO_PIN_RESET);}

	if((data&0x20)==0x20)
	{
		HAL_GPIO_WritePin(GPIOA, DB5_Pin, GPIO_PIN_SET);
	}
	else{HAL_GPIO_WritePin(GPIOA, DB5_Pin, GPIO_PIN_RESET);}

	if((data&0x40)==0x40)
	{
		HAL_GPIO_WritePin(GPIOA, DB6_Pin, GPIO_PIN_SET);
	}
	else{HAL_GPIO_WritePin(GPIOA, DB6_Pin, GPIO_PIN_RESET);}

	if((data&0x80)==0x80)
	{
		HAL_GPIO_WritePin(GPIOA, DB7_Pin, GPIO_PIN_SET);
	}
	else{HAL_GPIO_WritePin(GPIOA, DB7_Pin, GPIO_PIN_RESET);}


}
//////////////////////////////////////////////////////////////////////////////////////////////////
void BusyL(void)
{
	//unsigned char flag=0xff;
unsigned char flag = ReadDataFromPins();
// CS1= 1;       //active "H"
 HAL_GPIO_WritePin(GPIOC, LCD_CS1_Pin, GPIO_PIN_SET);

 //CS2= 0;
 HAL_GPIO_WritePin(GPIOB, LCD_CS2_Pin, GPIO_PIN_RESET);
 //RS = 0;
 HAL_GPIO_WritePin(GPIOC, LCD_RS_Pin, GPIO_PIN_RESET);
// RW = 1;
 HAL_GPIO_WritePin(GPIOA, LCD_RW_Pin, GPIO_PIN_SET);//RW
 //P1 = 0xFF;
 //Printdata(0xff);
 ReadDataFromPins();

while ((flag&0x80)==0x80)
 {
// E=1;
	HAL_GPIO_WritePin(GPIOC,LCD_E_Pin , GPIO_PIN_SET);
 //_nop_();
	HAL_Delay(10);
// flag=P1;
	flag= ReadDataFromPins();
 //E=0;
 HAL_GPIO_WritePin(GPIOC, LCD_E_Pin, GPIO_PIN_RESET);
 }
}
////////////////////////////////////////////////////////////////////////////////////////////////////////
void BusyR(void)
{
	//unsigned char flag=0xff;
	unsigned char flag = ReadDataFromPins();
// CS1= 0;
 HAL_GPIO_WritePin(GPIOC, LCD_CS1_Pin, GPIO_PIN_RESET);
// CS2= 1;        //active "H"
 HAL_GPIO_WritePin(GPIOB, LCD_CS2_Pin, GPIO_PIN_SET);
 //RS = 0;
 HAL_GPIO_WritePin(GPIOC, LCD_RS_Pin, GPIO_PIN_RESET);
 //RW = 1;
 HAL_GPIO_WritePin(GPIOA, LCD_RW_Pin, GPIO_PIN_SET);//RW
 //P1 = 0xFF;
 ReadDataFromPins();
while ((flag&0x80)==0x80)
 {
// E=1;
HAL_GPIO_WritePin(GPIOC,LCD_E_Pin , GPIO_PIN_SET);
 //_nop_();
HAL_Delay(10);
// flag=P1;
flag= ReadDataFromPins();
// E=0;
	 HAL_GPIO_WritePin(GPIOC, LCD_E_Pin, GPIO_PIN_RESET);
 }
}
/////////////////////////////////////////////////////////////////////////////////////////////////
void Locatexy(void)
{
 unsigned char x,y,Z;
// switch (Col&0xc0) /*  col.and.0xC0 */
// {
//  case 0: {BusyL();break;}
//  case 0x40: {BusyR();break;}
// }
 x = 0XB8;//((Col&0x3F)|0x40); /* col.and.0x3f.or.Set X Address*/
// y =0X40; //((Page&0x07)|0xB8); /* row.and.0x07.or.set Page */
 //Z=0XC0;
//
// RS = 0;
 HAL_GPIO_WritePin(GPIOC, LCD_RS_Pin, GPIO_PIN_RESET);
// RW = 0;
 HAL_GPIO_WritePin(GPIOA, LCD_RW_Pin, GPIO_PIN_RESET);
// P1 = y;
 Printdata(x);
// E  = 1;
 HAL_GPIO_WritePin(GPIOC,LCD_E_Pin , GPIO_PIN_SET);
 //_nop_();
 HAL_Delay(100);
 //E  = 0;
for (unsigned char col1 = 0X40; col1 < 0X7F; col1++) {
         y = 0x40 + col1;} // Set column address from 0x40 to 0x7F

 HAL_GPIO_WritePin(GPIOC, LCD_E_Pin, GPIO_PIN_RESET);
 //_nop_();
 HAL_Delay(100);
// RS = 0;
 HAL_GPIO_WritePin(GPIOC, LCD_RS_Pin, GPIO_PIN_RESET);
// RW = 0;
 HAL_GPIO_WritePin(GPIOA, LCD_RW_Pin, GPIO_PIN_RESET);
// P1 = x;
 Printdata(y);
 //E  = 1;
 HAL_GPIO_WritePin(GPIOC,LCD_E_Pin , GPIO_PIN_SET);
// _nop_();
	HAL_Delay(100);
// E  = 0;
	 HAL_GPIO_WritePin(GPIOC, LCD_E_Pin, GPIO_PIN_RESET);
 //_nop_();
	 HAL_Delay(10);

	 for (unsigned char line1 = 0XC0; line1< 8; line1++) {
	             Z = 0xC0 + line1; }// Increment line address from 0xC0 to 0xC7

	 HAL_GPIO_WritePin(GPIOC, LCD_RS_Pin, GPIO_PIN_RESET);
	 // RW = 0;
	  HAL_GPIO_WritePin(GPIOA, LCD_RW_Pin, GPIO_PIN_RESET);
	 // P1 = y;
	  Printdata(Z);
	 // E  = 1;
	  HAL_GPIO_WritePin(GPIOC,LCD_E_Pin , GPIO_PIN_SET);
	  //_nop_();
	  HAL_Delay(100);
	  //E  = 0;
	  HAL_GPIO_WritePin(GPIOC, LCD_E_Pin, GPIO_PIN_RESET);
	  //_nop_();
	  HAL_Delay(100);

}
////////////////////////////////////////////////////////////////////
void WriteCommandL( unsigned char CommandByte )
{
 BusyL();
// P1 = CommandByte;
 Printdata(CommandByte );
// RS = 0;
 HAL_GPIO_WritePin(GPIOC, LCD_RS_Pin, GPIO_PIN_RESET);
// RW = 0;
 HAL_GPIO_WritePin(GPIOA, LCD_RW_Pin, GPIO_PIN_RESET);
// E  = 1;
 HAL_GPIO_WritePin(GPIOC,LCD_E_Pin , GPIO_PIN_SET);
// _nop_();
 HAL_Delay(1000);
// E  = 0;
 HAL_GPIO_WritePin(GPIOC, LCD_E_Pin, GPIO_PIN_RESET);
// _nop_();
 HAL_Delay(1000);

}
//////////////////////////////////////////////////////////////////
void WriteCommandR( unsigned char CommandByte )
{
 BusyR();
// P1 = CommandByte;
 Printdata(CommandByte );
// RS = 0;
// RW = 0;
// E  = 1;
// _nop_();
// E  = 0;
// _nop_();
 // RS = 0;
  HAL_GPIO_WritePin(GPIOC, LCD_RS_Pin, GPIO_PIN_RESET);
 // RW = 0;
  HAL_GPIO_WritePin(GPIOA, LCD_RW_Pin, GPIO_PIN_RESET);
 // E  = 1;
  HAL_GPIO_WritePin(GPIOC,LCD_E_Pin , GPIO_PIN_SET);
 // _nop_();
  HAL_Delay(1000);
 // E  = 0;
  HAL_GPIO_WritePin(GPIOC, LCD_E_Pin, GPIO_PIN_RESET);
 // _nop_();
  HAL_Delay(1000);
}
///////////////////////////////////////////////////////////////////
//unsigned char ReadData( void )
//{
// unsigned char DataByte;
// Locatexy();
// //RS = 1;
// HAL_GPIO_WritePin(GPIOC, LCD_RS_Pin, GPIO_PIN_SET);
//// RW = 1;
// HAL_GPIO_WritePin(GPIOA, LCD_RW_Pin, GPIO_PIN_SET);
//// P1 = 0xFF;
// ReadDataFromPins();
// // _nop_();
// HAL_Delay(10);
// //E  = 1;
// HAL_GPIO_WritePin(GPIOA, LCD_RS_Pin, GPIO_PIN_SET);
// //_nop_();
// HAL_Delay(10);
// //DataByte = P1;
// DataByte =ReadDataFromPins();
//// E  = 0;
// HAL_GPIO_WritePin(GPIOA, LCD_RS_Pin, GPIO_PIN_RESET);
//// _nop_();
//// CS1=0;
// HAL_GPIO_WritePin(GPIOC, LCD_CS1_Pin, GPIO_PIN_RESET);
//
// //CS2= 0;
// HAL_GPIO_WritePin(GPIOB, LCD_CS2_Pin, GPIO_PIN_RESET);
//// CS2=0;
// return DataByte;
//}
///////////////////////////////////////////////////////////////////////////////////////
void WriteData( unsigned char DataByte )
{
	HAL_GPIO_WritePin(GPIOC, LCD_CS1_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOB, LCD_CS2_Pin, GPIO_PIN_RESET);

 Locatexy();
// RS = 1;
 HAL_GPIO_WritePin(GPIOC, LCD_RS_Pin, GPIO_PIN_SET);
// RW = 0;
 HAL_GPIO_WritePin(GPIOA, LCD_RW_Pin, GPIO_PIN_RESET);
// P1 = DataByte;
 ReadDataFromPins();
// E  = 1;
 HAL_GPIO_WritePin(GPIOA, LCD_E_Pin, GPIO_PIN_SET);
// _nop_();
 HAL_Delay(1000);
 //E  = 0;
 HAL_GPIO_WritePin(GPIOA, LCD_E_Pin, GPIO_PIN_RESET);

 //_nop_();
 HAL_Delay(1000);
// CS1=0;
// CS2=0;
// HAL_GPIO_WritePin(GPIOC, LCD_CS1_Pin, GPIO_PIN_SET);

  //CS2= 0;
//  HAL_GPIO_WritePin(GPIOB, LCD_CS2_Pin, GPIO_PIN_RESET);
 // CS2=0;
}
//////////////////////////////////////////////////////////////////////////////
void LcmClear( void )
{
 Page = 0xB8;
 Col  = 0X40;
 for(Page=0XB8;Page<0XB8;Page++)
  for(Col=0X40;Col<0X3F;Col++)
   WriteData(0);
}

void LcmInit( void )
{
	 WriteCommandL(0x3e); //DISPALY off
	 WriteCommandR(0x3e);
 WriteCommandL(0x3f); //DISPALY ON
 WriteCommandR(0x3f);

 WriteCommandL(0xc0); //SET START ADDRESS
 WriteCommandR(0xc0);

 WriteCommandL(0x3f); //DISPLAY ON
 WriteCommandR(0x3f);

}
void LcmPutDots( unsigned char DotByte,unsigned char DotByte1 )
{
 Page = 0xB8;
 Col  = 0x40;
 for(Page=0XB8;Page<0XBF;Page++)
 {
  for(Col=0X40;Col<0X3F;Col++)
  {
   WriteData( DotByte );
   Col++;
   WriteData( DotByte1 );
  }

 }
}

//void LcmPutBMP( unsigned char *puts )
//{
// unsigned int X=0;
// Page = 0;
// Col  = 0;
// for(Page=0;Page<8;Page++)
// {
//  for(Col=0;Col<128;Col++)
//  {
//   WriteData( puts[X] );
//   X++;
//  }
// }
//}
//
//void LcmReverseBMPP( unsigned char *puts )
//{
// unsigned int X=0;
// Page = 0;
// Col  = 0;
// for(Page=0;Page<8;Page++)
// {
//  for(Col=0;Col<128;Col++)
//  {
//   WriteData(~puts[X] );
//   X++;
//  }
// }
//}
//
//void Display_8_8(unsigned char C[],unsigned char i)
//{ unsigned char k,num=0;
// num=i*0x08;
// for(k=0;k<0x08;k++)
// {
//  WriteData(C[num+k]);
//  Col+=0x01;
// }
//
//}
////////////////////////////////////////////////////////////////////////////
//void Display_16_16(unsigned char F[],unsigned char i)
//{
// unsigned char k=0;
// unsigned int	num=0;
// num=i*0x20;
//
// for(k=0;k<0x10;k++)
// {
//  WriteData(F[num+k]);
//  Col+=0x01;
// }
//  Col-=0x10;
//  Page+=0x01;
//  for(k=16;k<0x20;k++)
// {
//  WriteData(F[num+k]);
//  Col+=0x01;
// }
//  Page-=0x01;
//  HAL_Delay(10);
//}

//void Display_character()
//{ unsigned char k,c, a=0;
//char font;///// please check
//char character;/// please check
// Col  = 0;
// for(c=0;c<8;c++)
// { Page = c;
//	for(k=0;k<16;k++)
// 	{ Display_8_8(character,0);
// 	}
// Col  = 0;
// }
// HAL_Delay(10);
//
// for(c=0;c<8;c++)
// { Page = c;
//	for(k=0;k<16;k++)
// 	{ Display_8_8(character,1);
// 	}
// Col  = 0;
// }
// HAL_Delay(10);
//
// for(c=0;c<8;c++)
// { Page = c;
//	for(k=0;k<16;k++)
// 	{ Display_8_8(character,2);
// 	}
// Col  = 0;
// }
// HAL_Delay(10);
//
//
//}

//void Display_Chinese()
//{unsigned char a=0;
// Page = 0;
// Col  = 0;
////char font;
// for(a=0;a<8;a++)
// {
// Display_16_16(font,a);
// }
// Page = 2;
// Col  = 0;
// for(a=8;a<16;a++)
// {
// Display_16_16(font,a);
// }
//
// Page = 4;
// Col  = 0;
// for(a=16;a<24;a++)
// {
// Display_16_16(font,a);
// }
//
// Page = 6;
// Col  = 0;
// for(a=24;a<32;a++)
// {
// Display_16_16(font,a);
// }
//
//}


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
 //HAL_GPIO_WritePin(GPIOA, LED_K_Pin, GPIO_PIN_SET);
 // HAL_GPIO_WritePin(GPIOA, LCD_RESET_Pin, GPIO_PIN_SET);
  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART1_UART_Init();
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */
  HAL_GPIO_WritePin(GPIOA, LED_K_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(GPIOA, LCD_RESET_Pin, GPIO_PIN_SET);
  LcmInit();
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
	 // HAL_GPIO_WritePin(GPIOA, LED_K_Pin, GPIO_PIN_SET);
	  LcmPutDots(0x55,0xaa);
	 //  Delay(600);
	  HAL_Delay(100);
	    LcmPutDots(0xaa,0x55);
	   // Delay(600);
	    HAL_Delay(100);
	   LcmPutDots(0x55,0x55);
	 //  Delay(600);
	   HAL_Delay(100);
	    LcmPutDots(0xaa,0xaa);
	  //  Delay(600);
	    HAL_Delay(100);

	    LcmPutDots(0xff,0x00);
	   // Delay(600);
	    HAL_Delay(100);
	    LcmPutDots(0x00,0xff);
	   // Delay(600);
	    HAL_Delay(100);
	   // LcmPutBMP(BMP3);
	    //HAL_Delay(10);

	   //  LcmReverseBMPP(BMP3);
	   //  HAL_Delay(100);
	     // Delay(1000);
	  //   LcmPutBMP(BMP4);
	    //  Delay(1000);
	     //   LcmReverseBMPP(BMP4);
	     // Delay(1000);
	     //   HAL_Delay(100);
	      //LcmClear();
	     // Display_Chinese();
	   //   HAL_Delay(10);
	    //  Display_character();
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

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSIDiv = RCC_HSI_DIV4;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.SYSCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_APB1_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  huart1.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart1.Init.ClockPrescaler = UART_PRESCALER_DIV1;
  huart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_SetTxFifoThreshold(&huart1, UART_TXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_SetRxFifoThreshold(&huart1, UART_RXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_DisableFifoMode(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  huart2.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart2.Init.ClockPrescaler = UART_PRESCALER_DIV1;
  huart2.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, LED_K_Pin|DISP_EN_Pin|LCD_CS2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, LCD_E_Pin|LCD_RS_Pin|LCD_CS1_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, LCD_RW_Pin|LCD_RESET_Pin|DB0_Pin|DB1_Pin
                          |DB2_Pin|DB3_Pin|DB4_Pin|DB5_Pin
                          |DB6_Pin|DB7_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : LED_K_Pin DISP_EN_Pin LCD_CS2_Pin */
  GPIO_InitStruct.Pin = LED_K_Pin|DISP_EN_Pin|LCD_CS2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : LCD_E_Pin LCD_RS_Pin LCD_CS1_Pin */
  GPIO_InitStruct.Pin = LCD_E_Pin|LCD_RS_Pin|LCD_CS1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : LCD_RW_Pin LCD_RESET_Pin DB0_Pin DB1_Pin
                           DB2_Pin DB3_Pin DB4_Pin DB5_Pin
                           DB6_Pin DB7_Pin */
  GPIO_InitStruct.Pin = LCD_RW_Pin|LCD_RESET_Pin|DB0_Pin|DB1_Pin
                          |DB2_Pin|DB3_Pin|DB4_Pin|DB5_Pin
                          |DB6_Pin|DB7_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : DISP_INTO_Pin */
  GPIO_InitStruct.Pin = DISP_INTO_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(DISP_INTO_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : SW4_Pin SW3_Pin SW2_Pin SW1_Pin */
  GPIO_InitStruct.Pin = SW4_Pin|SW3_Pin|SW2_Pin|SW1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
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

#ifdef  USE_FULL_ASSERT
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