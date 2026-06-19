// PLL.h
// Runs on TM4C123


// TODO:
// Determine the #define statement SYSDIV initializes
// the PLL to the desired frequency.
#define SYSDIV2  4
// bus frequency is 400MMHz/(SYSDIV+1) 400/(4 + 1) = 80mhz

void PLL_Init(void);