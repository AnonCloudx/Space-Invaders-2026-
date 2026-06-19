// Systick.c
// Runs on TM4C123

#include "Systick.h"
#include "tm4c123gh6pm.h"
#include <stdint.h>

void SysTick_Init(uint32_t period){
  NVIC_ST_CTRL_R = 0;         // disable SysTick during setup
  NVIC_ST_RELOAD_R = period-1;// reload value: if period = 4
  NVIC_ST_CURRENT_R = 0;      // any write to current clears it
  NVIC_SYS_PRI3_R = (NVIC_SYS_PRI3_R&0x1FFFFFFF)|0x40000000; // priority 2
//	NVIC_ST_CTRL_R |= NVIC_ST_CTRL_CLK_SRC|NVIC_ST_CTRL_INTEN|NVIC_ST_CTRL_ENABLE;

}

void SysTickStop(void){
	 NVIC_ST_CTRL_R = 0;         // disable SysTick during setup
}

void SystickStart(void){
	NVIC_ST_CTRL_R |= NVIC_ST_CTRL_CLK_SRC|NVIC_ST_CTRL_INTEN|NVIC_ST_CTRL_ENABLE;
}