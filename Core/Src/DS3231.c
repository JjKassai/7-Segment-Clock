#include "DS3231.h"

// Constants
const uint8_t daysOfTheMonth[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

uint8_t readHours(I2C_HandleTypeDef commChannel)
{
	uint8_t rawValue;
	uint8_t returnValue;

	address = address_DS3231;
	i2cBuffer[0] = address_Hour;

	HAL_I2C_Master_Transmit(&commChannel, address, i2cBuffer, 1, 500);

	HAL_I2C_Master_Receive(&commChannel, address, &rawValue, 1, 500);

	returnValue = (((rawValue & 0b00111111)>> 4) * 10) + (rawValue & 0b00001111);

	return returnValue;
}


uint8_t readSeconds(I2C_HandleTypeDef commChannel)
{
	uint8_t rawValue;
	uint8_t calculatedValue;

	address = address_DS3231;
	i2cBuffer[0] = address_Seconds;

	HAL_I2C_Master_Transmit(&commChannel, address, i2cBuffer, 1, 500);

	HAL_I2C_Master_Receive(&commChannel, address, &rawValue, 1, 500);

	calculatedValue = ((rawValue >> 4) * 10) + (rawValue & 0b00001111);

	return calculatedValue;
}


uint8_t readMinutes(I2C_HandleTypeDef commChannel)
{
	uint8_t rawValue;
	uint8_t calculatedReturn;

	address = address_DS3231;
	i2cBuffer[0] = address_Minutes;

	HAL_I2C_Master_Transmit(&commChannel, address, i2cBuffer, 1, 500);

	HAL_I2C_Master_Receive(&commChannel, address, &rawValue, 1, 500);

	calculatedReturn = ((rawValue >> 4) * 10) + (rawValue & 0b00001111);

	return calculatedReturn;
}

uint8_t readMonth(I2C_HandleTypeDef commChannel)
{
	uint8_t rawValue;
	uint8_t calculatedReturn;

	address = address_DS3231;
	i2cBuffer[0] = address_Month;

	HAL_I2C_Master_Transmit(&commChannel, address, i2cBuffer, 1, 500);

	HAL_I2C_Master_Receive(&commChannel, address, &rawValue, 1, 500);

	calculatedReturn = ((rawValue & 0b00010000) >> 4) * 10 + (rawValue & 0b00001111);

	return calculatedReturn;
}

uint8_t readDay(I2C_HandleTypeDef commChannel)
{
	uint8_t returnValue;
	uint8_t calculatedValue;

	address = address_DS3231;
	i2cBuffer[0] = address_Date;

	HAL_I2C_Master_Transmit(&commChannel, address, i2cBuffer, 1, 500);

	HAL_I2C_Master_Receive(&commChannel, address, &returnValue, 1, 500);

	calculatedValue = ((returnValue & 0b11110000) >> 4) * 10 + (returnValue & 0b00001111);

	return calculatedValue;
}

uint8_t readYear(I2C_HandleTypeDef commChannel)
{
	uint8_t returnValue;
	uint8_t calculatedValue;

	address = address_DS3231;
	i2cBuffer[0] = address_Year;

	HAL_I2C_Master_Transmit(&commChannel, address, i2cBuffer, 1, 500);

	HAL_I2C_Master_Receive(&commChannel, address, &returnValue, 1, 500);

	calculatedValue = (returnValue >> 4) * 10 + (returnValue & 0b00001111);

	return calculatedValue;
}

void writeYear(I2C_HandleTypeDef commChannel, uint8_t yearValueTens, uint8_t yearValueOnes)
{
	uint8_t setValue;

	setValue =  yearValueTens << 4;
	setValue = setValue + yearValueOnes;

	address = address_DS3231;
	i2cBuffer[0] = address_Year;
	i2cBuffer[1] = setValue;

	HAL_I2C_Master_Transmit(&commChannel, address, i2cBuffer, 2, 500);
}

void writeMonth(I2C_HandleTypeDef commChannel, uint8_t monthValueTens, uint8_t monthValueOnes)
{
	uint8_t setValue;

	setValue =  monthValueTens << 4;
	setValue = setValue + monthValueOnes;

	address = address_DS3231;
	i2cBuffer[0] = address_Month;
	i2cBuffer[1] = setValue;

	HAL_I2C_Master_Transmit(&commChannel, address, i2cBuffer, 2, 500);
}

void writeDay(I2C_HandleTypeDef commChannel, uint8_t dayValueTens, uint8_t dayValueOnes)
{
	uint8_t setValue;

	setValue =  dayValueTens << 4;
	setValue = setValue + dayValueOnes;

	address = address_DS3231;
	i2cBuffer[0] = address_Date;
	i2cBuffer[1] = setValue;

	HAL_I2C_Master_Transmit(&commChannel, address, i2cBuffer, 2, 500);
}

void writeHours(I2C_HandleTypeDef commChannel, uint8_t hoursValueTens, uint8_t hoursValueOnes)
{
	uint8_t setValue;

	setValue = hoursValueTens << 4;
	setValue = setValue + hoursValueOnes;

	address = address_DS3231;
	i2cBuffer[0] = address_Hour;
	i2cBuffer[1] = setValue;

	HAL_I2C_Master_Transmit(&commChannel, address_DS3231, i2cBuffer, 2, 500);
}

void writeMinutes(I2C_HandleTypeDef commChannel, uint8_t minutesValueTens, uint8_t minutesValueOnes)
{
	uint8_t setValue;

	setValue = minutesValueTens << 4;
	setValue = setValue + minutesValueOnes;

	address = address_DS3231;
	i2cBuffer[0] = address_Minutes;
	i2cBuffer[1] = setValue;

	HAL_I2C_Master_Transmit(&commChannel, address_DS3231, i2cBuffer, 2, 500);
}

void writeSeconds(I2C_HandleTypeDef commChannel, uint8_t secondsValueTens, uint8_t secondsValueOnes)
{
	uint8_t setValue;

	setValue =  secondsValueTens << 4;
	setValue = setValue + secondsValueOnes;

	address = address_DS3231;
	i2cBuffer[0] = address_Seconds;
	i2cBuffer[1] = setValue;

	HAL_I2C_Master_Transmit(&commChannel, address, i2cBuffer, 2, 500);
}

uint8_t calculateYearDifference(uint8_t currentYear, uint8_t currentMonth, uint8_t currentDay)
{
	uint8_t returnValue;

	if(MILESTONE_CENTURY == 0)
	{
		// If the current year is greater than the milestone year
		if(currentYear > MILESTONE_YEAR)
		{
			// and the current month is less than the milestone month
			// then subtract 1 year from the difference
			if(currentMonth < MILESTONE_MONTH)
			{
				returnValue = currentYear - MILESTONE_YEAR - 1;
			}
			else if(currentMonth == MILESTONE_MONTH)
			{
				if(currentDay < MILESTONE_DATE)
				{
					returnValue = currentYear - MILESTONE_YEAR - 1;
				}
				else if(currentDay >= MILESTONE_DATE)
				{
					// It's the anniversary of the milestone date
					returnValue = currentYear - MILESTONE_YEAR;
				}
			}
			else
			{
				returnValue = currentYear - MILESTONE_YEAR;
			}
		}
		else if(currentYear == MILESTONE_YEAR)
		{
			returnValue = 0;
		}
		else
		{
			// This is a catch for currentYear < MILESTONE_YEAR
			// There may be an error, or in the future we may be counting down to a future date.

		}
	}
	else if(MILESTONE_CENTURY == 9)
	{
		// This code will have to be added
	}

	return returnValue;
}

uint8_t calculateMonthDifference(uint8_t currentMonth, uint8_t currentDay)
{
	uint8_t returnValue;

	// If the current year is greater than the milestone year
	if(currentMonth == MILESTONE_MONTH)
	{
		if(currentDay < MILESTONE_DATE)
		{
			returnValue = 11;
		}
		else
		// Anything later in this month means no difference
		{
			returnValue = 0;
		}
	}
	else if(currentMonth < MILESTONE_MONTH)
	{
		if(currentDay < MILESTONE_DATE)
		{
			returnValue = (12-MILESTONE_MONTH) + currentMonth - 1;
		}
		else if(currentDay >= MILESTONE_DATE)
		{
			returnValue = (12-MILESTONE_MONTH) + currentMonth;
		}
	}
	else
	{
		returnValue = currentMonth - MILESTONE_MONTH;
	}
	return returnValue;
}

uint8_t calculateDayDifference(uint8_t currentMonth, uint8_t currentDay)
{
	uint8_t dayDifference;

	if(currentMonth == MILESTONE_MONTH)
	{
		if(currentDay < MILESTONE_DATE)
		{
			dayDifference = (daysOfTheMonth[MILESTONE_MONTH - 1] - MILESTONE_DATE) + currentDay;
		}
		else if(currentDay == MILESTONE_DATE)
		{
			// Same day, no difference
			dayDifference = 0;
		}
		else
		{
			dayDifference = currentDay - MILESTONE_DATE;
		}
	}
	else
	{
		if(currentDay < MILESTONE_DATE)
		{
			dayDifference = (daysOfTheMonth[MILESTONE_MONTH - 1] - MILESTONE_DATE) + currentDay;
		}
		else if(currentDay == MILESTONE_DATE)
		{
			dayDifference = 0;
		}
		else if(currentDay > MILESTONE_DATE)
		{
			dayDifference = currentDay - MILESTONE_DATE;
		}
	}

	return dayDifference;
}
