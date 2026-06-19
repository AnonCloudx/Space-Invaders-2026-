// dac.c

#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "DAC.h"

#define DAC_DATA (*((volatile uint32_t *)0x4000503C))  // PB0-3: output to DAC circuit
#define DAC_PORTS 0x0F
#define DAC_PCTL 0x0000FFFF
// Code files contain the actual implemenation for public functions
// this file also contains an private functions and private data

// **************DAC_Init*********************
// Initialize 3-bit DAC, called once 
// DAC bit 0 on PB0 (least significant bit)
// DAC bit 1 on PB1
// DAC bit 2 on PB2
// DAC bit 3 on PB3 (most significant bit)
// Input: none
// Output: none
void DAC_Init(void){  
  SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOB; // activate port B
	while ((SYSCTL_RCGC2_R&SYSCTL_RCGC2_GPIOB)!=SYSCTL_RCGC2_GPIOB){}

  GPIO_PORTB_AMSEL_R &= ~DAC_PORTS;      // no analog 
  GPIO_PORTB_PCTL_R &= ~DAC_PCTL; // regular function
  GPIO_PORTB_DIR_R |= DAC_PORTS;      // make PB3-0 out
  GPIO_PORTB_AFSEL_R &= ~DAC_PORTS;   // disable alt funct on PB3-0
  GPIO_PORTB_DEN_R |= DAC_PORTS;      // enable digital I/O on PB3-0
}

// **************DAC_Out*********************
// output to DAC
// Input: 4-bit data, 0 to 15 
// Input=n is converted to n*3.3V/15
// Output: none
void DAC_Out(uint8_t data){
  DAC_DATA = data;
}