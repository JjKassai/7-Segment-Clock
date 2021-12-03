/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "primaryFunctions.h"
#include "DS3231.h"

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
I2C_HandleTypeDef hi2c1;

UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */
uint8_t value;
uint8_t value2;
uint8_t commandValue;
char returnMessage[50];


// Variables used for time-keeping
uint8_t hours;
uint8_t minutes;
uint8_t seconds;

uint8_t month;
uint8_t day;
uint8_t year;

uint8_t monthDifference;
uint8_t dayDifference;
uint8_t yearDifference;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_I2C1_Init(void);
/* USER CODE BEGIN PFP */
void displayCurrentTime(void);
void displayDifference(void);
void checkInputs(void);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

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
  MX_USART2_UART_Init();
  MX_I2C1_Init();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  // Read the current time
	  hours = readHours(hi2c1);
	  minutes = readMinutes(hi2c1);
	  seconds = readSeconds(hi2c1);
	  month = readMonth(hi2c1);
	  day = readDay(hi2c1);
	  year = readYear(hi2c1);

	  // Calculate the difference
	  dayDifference = calculateDayDifference(month, day);
	  monthDifference = calculateMonthDifference(month, day);
	  yearDifference = calculateYearDifference(year, month, day);

	  // Display the time
    displayDifference();
	 
	  checkInputs();
  }
  /* USER CODE END 3 */
}

void displayCurrentTime(void)
{
  // Turn off all digits while switching cathodes
  displayOff();

  if(hours > 9)
  {
    uint8_t temp;

    digitOne();
    if(hours > 19)
    {
      displayTwo();
      temp = hours - 20;
    }
    else
    {
      displayOne();
      temp = hours - 10;
    }
    HAL_Delay(1);
    displayOff();
    digitTwo();
    displayValue(temp);
    HAL_Delay(1);
    displayOff();
  }
  else
  {
    digitTwo();
    displayValue(hours);
    HAL_Delay(1);
    displayOff();
  }

  uint8_t tensValue;
  tensValue = minutes / 10;
  digitThree();
  displayValue(tensValue);
  HAL_Delay(1);
  displayOff();
  digitFour();

  displayValue(minutes - (tensValue * 10));

  HAL_Delay(1);
  displayOff();

  tensValue = seconds / 10;
  digitFive();
  displayValue(tensValue);
  HAL_Delay(1);
  displayOff();

  digitSix();
  displayValue(seconds - (tensValue * 10));
  HAL_Delay(1);
  displayOff();
}

void displayDifference(void)
{
  // Turn off all digits while switching cathodes
  displayOff();

  uint8_t tensValue;

  if(yearDifference > 9)
  {
    tensValue = yearDifference / 10;
    digitOne();
    displayValue(tensValue);
    HAL_Delay(1);
    displayOff();

    digitTwo();
    displayValue(yearDifference - (tensValue * 10));
    HAL_Delay(1);
    displayOff();
  } 
  else
  {
    digitTwo();
    displayValue(yearDifference);
    HAL_Delay(1);
    displayOff();
  }

  if(monthDifference > 9)
  {
    tensValue = monthDifference / 10;
    digitThree();
    displayValue(tensValue);
    HAL_Delay(1);
    displayOff();
    
    digitFour();
    displayValue(monthDifference - (tensValue * 10));
    HAL_Delay(1);
    displayOff();
  }
  else
  {
    digitFour();
    displayValue(monthDifference);
    HAL_Delay(1);
    displayOff();
  }

  if(dayDifference > 9)
  {
    tensValue = dayDifference / 10;
    digitFive();
    displayValue(tensValue);
    HAL_Delay(1);
    displayOff();

    digitSix();
    displayValue(dayDifference - (tensValue * 10));
    HAL_Delay(1);
    displayOff();
  }
  else
  {
    digitSix();
    displayValue(dayDifference);
    HAL_Delay(1);
    displayOff();
  }
}

void checkInputs(void)
{
	// Clear out any previous commands
	  commandValue = 0;

  // Determine if any new commands have been sent
  HAL_UART_Receive(&huart2, &commandValue, 1, 0);
  switch(commandValue)
  {
    case 'h':
      HAL_UART_Transmit(&huart2, (uint8_t*)returnMessage, sprintf(returnMessage, "\r\nSet the clock - hours:\r\n"), 500);
      HAL_UART_Receive(&huart2, &value, 1, 10000);
      sendUARTByte(huart2, value-48);
      HAL_UART_Receive(&huart2, &value2, 1, 10000);
      sendUARTByte(huart2, value2-48);
      writeHours(hi2c1, (value-48), (value2-48));
      break;
    case 'm':
      HAL_UART_Transmit(&huart2, (uint8_t*)returnMessage, sprintf(returnMessage, "\r\nSet the clock - minutes:\r\n"), 500);
      HAL_UART_Receive(&huart2, &value, 1, 10000);
      sendUARTByte(huart2, value-48);
      HAL_UART_Receive(&huart2, &value2, 1, 10000);
      sendUARTByte(huart2, value2-48);
      writeMinutes(hi2c1, (value-48), (value2-48));
      break;
    case 's':
      HAL_UART_Transmit(&huart2, (uint8_t*)returnMessage, sprintf(returnMessage, "\r\nSet the clock - seconds:\r\n"), 500);
      HAL_UART_Receive(&huart2, &value, 1, 10000);
      sendUARTByte(huart2, value-48);
      HAL_UART_Receive(&huart2, &value2, 1, 10000);
      sendUARTByte(huart2, value2-48);
      writeSeconds(hi2c1, (value - 48), (value2 - 48));
      break;
    case 'n':
      HAL_UART_Transmit(&huart2, (uint8_t*)returnMessage, sprintf(returnMessage, "\r\nSet the clock - month:\r\n"), 500);
      HAL_UART_Receive(&huart2, &value, 1, 10000);
      sendUARTByte(huart2, value-48);
      HAL_UART_Receive(&huart2, &value2, 1, 10000);
      sendUARTByte(huart2, value2-48);
      writeMonth(hi2c1, (value - 48), (value2 - 48));
      break;
    case 'd':
      HAL_UART_Transmit(&huart2, (uint8_t*)returnMessage, sprintf(returnMessage, "\r\nSet the clock - day:\r\n"), 500);
      HAL_UART_Receive(&huart2, &value, 1, 10000);
      sendUARTByte(huart2, value-48);
      HAL_UART_Receive(&huart2, &value2, 1, 10000);
      sendUARTByte(huart2, value2-48);
      writeDay(hi2c1, (value - 48), (value2 - 48));
      break;
    case 'y':
      HAL_UART_Transmit(&huart2, (uint8_t*)returnMessage, sprintf(returnMessage, "\r\nSet the clock - year:\r\n"), 500);
      HAL_UART_Receive(&huart2, &value, 1, 10000);
      sendUARTByte(huart2, value-48);
      HAL_UART_Receive(&huart2, &value2, 1, 10000);
      sendUARTByte(huart2, value2-48);
      writeYear(hi2c1, (value - 48), (value2 - 48));
      break;
    case 'r':
      HAL_UART_Transmit(&huart2, (uint8_t*)UARTBuffer, sprintf(UARTBuffer, "\r\nCurrent Time: %02d:%02d:%02d", hours, minutes, seconds), 500);
      HAL_UART_Transmit(&huart2, (uint8_t*)UARTBuffer, sprintf(UARTBuffer, "\r\nCurrent Date: %02d/%02d/%02d", month, day, year), 500);
      break;
    case 'M':
      HAL_UART_Transmit(&huart2, (uint8_t*)UARTBuffer, sprintf(UARTBuffer, "\r\nYear Difference: %d", yearDifference), 500);
      HAL_UART_Transmit(&huart2, (uint8_t*)UARTBuffer, sprintf(UARTBuffer, "\r\nMonth Difference: %d", monthDifference), 500);
      HAL_UART_Transmit(&huart2, (uint8_t*)UARTBuffer, sprintf(UARTBuffer, "\r\nDay Difference: %d", dayDifference), 500);
      break;
    default:
      break;
  }
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
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_I2C1;
  PeriphClkInit.I2c1ClockSelection = RCC_I2C1CLKSOURCE_HSI;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C1_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  hi2c1.Instance = I2C1;
  hi2c1.Init.Timing = 0x2000090E;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure Analogue filter
  */
  if (HAL_I2CEx_ConfigAnalogFilter(&hi2c1, I2C_ANALOGFILTER_ENABLE) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure Digital filter
  */
  if (HAL_I2CEx_ConfigDigitalFilter(&hi2c1, 0) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

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
  huart2.Init.BaudRate = 38400;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  huart2.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
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

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, Anode1_Pin|Anode2_Pin|Anode3_Pin|Anode4_Pin
                          |Anode5_Pin|Anode6_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, Segment1_Pin|Segment2_Pin|Segment3_Pin|Segment4_Pin
                          |Segment5_Pin|Segment6_Pin|Segment7_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : Anode1_Pin Anode2_Pin Anode3_Pin Anode4_Pin
                           Anode5_Pin Anode6_Pin */
  GPIO_InitStruct.Pin = Anode1_Pin|Anode2_Pin|Anode3_Pin|Anode4_Pin
                          |Anode5_Pin|Anode6_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : Segment1_Pin Segment2_Pin Segment3_Pin Segment4_Pin
                           Segment5_Pin Segment6_Pin Segment7_Pin */
  GPIO_InitStruct.Pin = Segment1_Pin|Segment2_Pin|Segment3_Pin|Segment4_Pin
                          |Segment5_Pin|Segment6_Pin|Segment7_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : BattVoltage_Pin */
  GPIO_InitStruct.Pin = BattVoltage_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(BattVoltage_GPIO_Port, &GPIO_InitStruct);

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

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
