#include "main.h"


// Module definitions
#define COMMON_CATHODE

// A common anode display has a single anode (current input) for the 7 segments.  Each segment is activated
// by pulling it low.  The opposite applies for a common cathode (current return) display.
#ifdef COMMON_ANODE
#define SEGMENT_ACTIVE 0
#define SEGMENT_INACTIVE 1
#define DIGIT_ACTIVE 0
#define DIGIT_INACTIVE 1
#else
#define SEGMENT_ACTIVE 1
#define SEGMENT_INACTIVE 0
#define DIGIT_ACTIVE 1
#define DIGIT_INACTIVE 0
#endif


// Function prototypes
void displayOff(void);
void displayZero(void);
void displayOne(void);
void displayTwo(void);
void displayThree(void);
void displayFour(void);
void displayFive(void);
void displaySix(void);
void displaySeven(void);
void displayEight(void);
void displayNine(void);

void displayValue(uint8_t value);

void digitOne(void);
void digitTwo(void);
void digitThree(void);
void digitFour(void);
