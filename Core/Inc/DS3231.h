#ifndef HEADER_DS3231
#define HEADER_DS3231

// Includes
#include "main.h"

// Defines
#define address_Seconds 	0x00;
#define address_Minutes 	0x01;
#define address_Hour		0x02;
#define address_Day         0x03;
#define address_Date		0x04;
#define address_Month		0x05;
#define address_Year		0x06;

// Constants
// Left-shift the 7-bit address one time per the STM32 HAL notes (see the HAL code comments)
static const unsigned int address_DS3231 = 0b1101000 << 1;

// Variables
extern unsigned char i2cBuffer[16];
extern unsigned char address;

// Function prototypes
uint8_t readSeconds(I2C_HandleTypeDef commChannel);
uint8_t readMinutes(I2C_HandleTypeDef commChannel);
uint8_t readHours(I2C_HandleTypeDef commChannel);
uint8_t readMonth(I2C_HandleTypeDef commChannel);
uint8_t readDay(I2C_HandleTypeDef commChannel);
uint8_t readYear(I2C_HandleTypeDef commChannel);

void writeHours(I2C_HandleTypeDef commChannel, uint8_t hoursValueTens, uint8_t hoursValueOnes);
void writeMinutes(I2C_HandleTypeDef commChannel, uint8_t minutesValueTens, uint8_t minutesValueOnes);
void writeSeconds(I2C_HandleTypeDef commChannel, uint8_t secondsValueTens, uint8_t secondsValueOnes);

void writeYear(I2C_HandleTypeDef commChannel, uint8_t yearValueTens, uint8_t yearValueOnes);
void writeMonth(I2C_HandleTypeDef commChannel, uint8_t monthValueTens, uint8_t monthValueOnes);
void writeDay(I2C_HandleTypeDef commChannel, uint8_t dayValueTens, uint8_t dayValueOnes);

uint8_t calculateYearDifference(uint8_t currentYear, uint8_t currentMonth, uint8_t currentDay);
uint8_t calculateMonthDifference(uint8_t currentMonth, uint8_t currentDay);
uint8_t calculateDayDifference(uint8_t currentMonth, uint8_t currentDay);

#endif
