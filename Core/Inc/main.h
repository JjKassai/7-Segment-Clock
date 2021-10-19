/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
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
#include "stm32f0xx_hal.h"

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
#define MCO_Pin GPIO_PIN_0
#define MCO_GPIO_Port GPIOF
#define Anode1_Pin GPIO_PIN_0
#define Anode1_GPIO_Port GPIOA
#define Anode2_Pin GPIO_PIN_1
#define Anode2_GPIO_Port GPIOA
#define VCP_TX_Pin GPIO_PIN_2
#define VCP_TX_GPIO_Port GPIOA
#define Anode3_Pin GPIO_PIN_3
#define Anode3_GPIO_Port GPIOA
#define Anode4_Pin GPIO_PIN_4
#define Anode4_GPIO_Port GPIOA
#define Anode5_Pin GPIO_PIN_5
#define Anode5_GPIO_Port GPIOA
#define Anode6_Pin GPIO_PIN_6
#define Anode6_GPIO_Port GPIOA
#define Segment1_Pin GPIO_PIN_0
#define Segment1_GPIO_Port GPIOB
#define Segment2_Pin GPIO_PIN_1
#define Segment2_GPIO_Port GPIOB
#define BattVoltage_Pin GPIO_PIN_10
#define BattVoltage_GPIO_Port GPIOA
#define SWDIO_Pin GPIO_PIN_13
#define SWDIO_GPIO_Port GPIOA
#define SWCLK_Pin GPIO_PIN_14
#define SWCLK_GPIO_Port GPIOA
#define VCP_RX_Pin GPIO_PIN_15
#define VCP_RX_GPIO_Port GPIOA
#define Segment3_Pin GPIO_PIN_3
#define Segment3_GPIO_Port GPIOB
#define Segment4_Pin GPIO_PIN_4
#define Segment4_GPIO_Port GPIOB
#define Segment5_Pin GPIO_PIN_5
#define Segment5_GPIO_Port GPIOB
#define Segment6_Pin GPIO_PIN_6
#define Segment6_GPIO_Port GPIOB
#define Segment7_Pin GPIO_PIN_7
#define Segment7_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
