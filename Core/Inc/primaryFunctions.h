#include "main.h"
#include "sevenSegment.h"
#include "stdio.h"

#include "DS3231.h"

// Variables
char UARTBuffer[128];

// Function prototypes
void blinkAll(uint16_t delayValue);
void count(void);

void sendUARTGreeting(UART_HandleTypeDef outputChannel);
void sendUARTByte(UART_HandleTypeDef commChannel, char outputByte);
