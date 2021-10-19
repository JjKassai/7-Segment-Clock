#include "primaryFunctions.h"

void blinkAll(uint16_t delayValue)
{
	HAL_GPIO_WritePin(GPIOA, Anode1_Pin|Anode2_Pin|Anode3_Pin|Anode4_Pin|Anode5_Pin|Anode6_Pin, GPIO_PIN_RESET);

	HAL_GPIO_WritePin(GPIOB, Segment1_Pin|Segment2_Pin|Segment3_Pin|Segment4_Pin|Segment5_Pin|Segment6_Pin|Segment7_Pin, GPIO_PIN_RESET);

	HAL_Delay(delayValue);

	HAL_GPIO_WritePin(GPIOA, Anode1_Pin|Anode2_Pin|Anode3_Pin|Anode4_Pin|Anode5_Pin|Anode6_Pin, GPIO_PIN_SET);

	HAL_GPIO_WritePin(GPIOB, Segment1_Pin|Segment2_Pin|Segment3_Pin|Segment4_Pin|Segment5_Pin|Segment6_Pin|Segment7_Pin, GPIO_PIN_SET);

	HAL_Delay(delayValue);
}

void count(void)
{
	displayZero();
	HAL_Delay(1000);
	displayOne();
	HAL_Delay(1000);
	displayTwo();
	HAL_Delay(1000);
	displayThree();
	HAL_Delay(1000);
	displayFour();
	HAL_Delay(1000);
	displayFive();
	HAL_Delay(1000);
	displaySix();
	HAL_Delay(1000);
	displaySeven();
	HAL_Delay(1000);
	displayEight();
	HAL_Delay(1000);
	displayNine();
	HAL_Delay(1000);
}

void sendUARTGreeting(UART_HandleTypeDef commChannel)
{
	HAL_UART_Transmit(&commChannel, (uint8_t*)UARTBuffer, sprintf(UARTBuffer, "\r\nUART Test"), 500);
}

void sendUARTByte(UART_HandleTypeDef commChannel, char outputByte)
{
	HAL_UART_Transmit(&commChannel, (uint8_t*)UARTBuffer, sprintf(UARTBuffer, "\r\nOutput Value: %d", outputByte), 500);
}
