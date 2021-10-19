#include "sevenSegment.h"


// Function declarations
void displayOff(void)
{
	HAL_GPIO_WritePin(GPIOB, Segment1_Pin|Segment2_Pin|Segment3_Pin|Segment4_Pin|Segment5_Pin|Segment6_Pin|Segment7_Pin, SEGMENT_INACTIVE);
}
void displayZero(void)
{
	HAL_GPIO_WritePin(GPIOB, Segment1_Pin|Segment2_Pin|Segment3_Pin|Segment4_Pin|Segment5_Pin|Segment6_Pin, SEGMENT_ACTIVE);
	HAL_GPIO_WritePin(GPIOB, Segment7_Pin, SEGMENT_INACTIVE);
}

void displayOne(void)
{
	HAL_GPIO_WritePin(GPIOB, Segment2_Pin|Segment3_Pin, SEGMENT_ACTIVE);
	HAL_GPIO_WritePin(GPIOB, Segment1_Pin|Segment4_Pin|Segment5_Pin|Segment6_Pin|Segment7_Pin, SEGMENT_INACTIVE);
}

void displayTwo(void)
{
	HAL_GPIO_WritePin(GPIOB, Segment1_Pin|Segment2_Pin|Segment4_Pin|Segment5_Pin|Segment7_Pin, SEGMENT_ACTIVE);
	HAL_GPIO_WritePin(GPIOB, Segment3_Pin|Segment6_Pin, SEGMENT_INACTIVE);
}

void displayThree(void)
{
	HAL_GPIO_WritePin(GPIOB, Segment1_Pin|Segment2_Pin|Segment3_Pin|Segment4_Pin|Segment7_Pin, SEGMENT_ACTIVE);
	HAL_GPIO_WritePin(GPIOB, Segment5_Pin|Segment6_Pin, SEGMENT_INACTIVE);
}

void displayFour(void)
{
	HAL_GPIO_WritePin(GPIOB, Segment2_Pin|Segment3_Pin|Segment6_Pin|Segment7_Pin, SEGMENT_ACTIVE);
	HAL_GPIO_WritePin(GPIOB, Segment1_Pin|Segment4_Pin|Segment5_Pin, SEGMENT_INACTIVE);
}

void displayFive(void)
{
	HAL_GPIO_WritePin(GPIOB, Segment1_Pin|Segment3_Pin|Segment4_Pin|Segment6_Pin|Segment7_Pin, SEGMENT_ACTIVE);
	HAL_GPIO_WritePin(GPIOB, Segment2_Pin|Segment5_Pin, SEGMENT_INACTIVE);
}

void displaySix(void)
{
	HAL_GPIO_WritePin(GPIOB, Segment1_Pin|Segment3_Pin|Segment4_Pin|Segment5_Pin|Segment6_Pin|Segment7_Pin, SEGMENT_ACTIVE);
	HAL_GPIO_WritePin(GPIOB, Segment2_Pin, SEGMENT_INACTIVE);
}

void displaySeven(void)
{
	HAL_GPIO_WritePin(GPIOB, Segment1_Pin|Segment2_Pin|Segment3_Pin, SEGMENT_ACTIVE);
	HAL_GPIO_WritePin(GPIOB, Segment4_Pin|Segment5_Pin|Segment6_Pin|Segment7_Pin, SEGMENT_INACTIVE);
}

void displayEight(void)
{
	HAL_GPIO_WritePin(GPIOB, Segment1_Pin|Segment2_Pin|Segment3_Pin|Segment4_Pin|Segment5_Pin|Segment6_Pin|Segment7_Pin, SEGMENT_ACTIVE);
}

void displayNine(void)
{
	HAL_GPIO_WritePin(GPIOB, Segment1_Pin|Segment2_Pin|Segment3_Pin|Segment4_Pin|Segment6_Pin|Segment7_Pin, SEGMENT_ACTIVE);
	HAL_GPIO_WritePin(GPIOB, Segment5_Pin, SEGMENT_INACTIVE);
}

void displayValue(uint8_t value)
{
	switch(value)
	{
		case 0:
		  displayZero();
		  break;
		case 1:
		  displayOne();
		  break;
		case 2:
		  displayTwo();
		  break;
		case 3:
		  displayThree();
		  break;
		case 4:
		  displayFour();
		  break;
		case 5:
		  displayFive();
		  break;
		case 6:
		  displaySix();
		  break;
		case 7:
		  displaySeven();
		  break;
		case 8:
		  displayEight();
		  break;
		case 9:
			displayNine();
			break;
		default:
			displayOff();
			break;
	}
}


void digitOne(void)
{
	HAL_GPIO_WritePin(GPIOA, Anode1_Pin, DIGIT_ACTIVE);
	HAL_GPIO_WritePin(GPIOA, Anode2_Pin|Anode3_Pin|Anode4_Pin|Anode5_Pin|Anode6_Pin, DIGIT_INACTIVE);
}

void digitTwo(void)
{
	HAL_GPIO_WritePin(GPIOA, Anode2_Pin, DIGIT_ACTIVE);
	HAL_GPIO_WritePin(GPIOA, Anode1_Pin|Anode3_Pin|Anode4_Pin|Anode5_Pin|Anode6_Pin, DIGIT_INACTIVE);
}

void digitThree(void)
{
	HAL_GPIO_WritePin(GPIOA, Anode3_Pin, DIGIT_ACTIVE);
	HAL_GPIO_WritePin(GPIOA, Anode1_Pin|Anode2_Pin|Anode4_Pin|Anode5_Pin|Anode6_Pin, DIGIT_INACTIVE);
}

void digitFour(void)
{
	HAL_GPIO_WritePin(GPIOA, Anode4_Pin, DIGIT_ACTIVE);
	HAL_GPIO_WritePin(GPIOA, Anode1_Pin|Anode2_Pin|Anode3_Pin|Anode5_Pin|Anode6_Pin, DIGIT_INACTIVE);
}

