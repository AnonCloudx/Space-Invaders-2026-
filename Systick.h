// Systick.h
// Runs on TM4C123

#include <stdint.h>


void SysTick_Init(uint32_t period);
void SysTickStop(void);
void SystickStart(void);