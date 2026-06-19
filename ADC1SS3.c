// ADC2SS3.c
// Runs on TM4C123, starter file for space invader game
// 05/06/2026

#include "tm4c123gh6pm.h"
#include <stdint.h>
#include <stdlib.h>

#define ADC1_MODULE 0x00020000
#define Sample_Seq3 0x0008
#define PE5_MASK       0x20
#define ADC1_PSSI_SS3 (0x0008)    // start sample sequencer 3
#define ADC1_ISC_SS3  (0x0008)    // acknowledge sample sequencer 3 interrupt
#define ADC1_RIS_SS3  (0x08)
#define MAX_WIDTH     83
#define SHIP_WIDTH    18
#define ADC_RANGE     4096
// This initialization function sets up the ADC2 Sample Sequencer 3 
// Max sample rate: <=125,000 samples/second
// SS3 triggering event: software trigger
// SS3 1st sample source: Ain8 (PE5)
// SS3 interrupts: flag set on completion but no interrupt requested
void ADC1SS3_Init(void){ 
	SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R4;   // 1) activate clock for Port E
	while ((SYSCTL_RCGCGPIO_R&SYSCTL_RCGCGPIO_R4)!=SYSCTL_RCGCGPIO_R4){}

	GPIO_PORTE_DIR_R &= ~PE5_MASK;      // 2) make PE5 input
  GPIO_PORTE_AFSEL_R |= PE5_MASK;     // 3) enable alternate function on PE5
  GPIO_PORTE_DEN_R &= ~PE5_MASK;      // 4) disable digital I/O on PE5
  GPIO_PORTE_AMSEL_R |= PE5_MASK;     // 5) enable analog function on PE5
  
	SYSCTL_RCGC0_R |= ADC1_MODULE;   // 6) activate ADC1
	while ((SYSCTL_RCGC0_R&ADC1_MODULE)!=ADC1_MODULE){}
         
  SYSCTL_RCGC0_R &= ~0x00000300;  // 7) configure for 125K 
  ADC1_SSPRI_R = 0x0123;          // 8) Sequencer 3 is highest priority
  ADC1_ACTSS_R &= ~Sample_Seq3;        // 9) disable sample sequencer 3
  ADC1_EMUX_R &= ~0xF000;         // 10) seq3 is software trigger
  ADC1_SSMUX3_R = (ADC1_SSMUX3_R&0xFFFFFFF0)+8; // 11) channel Ain8 (PE5)
  ADC1_SSCTL3_R = 0x0006;         // 12) no TS0 D0, yes IE0 END0
  ADC1_ACTSS_R |= Sample_Seq3;         // 13) enable sample sequencer 3
}

//------------ADC1SS3_In------------
// Busy-wait Analog to digital conversion
// Input: none
// Output: 12-bit result of ADC conversion
uint16_t ADC1SS3_In(void){ 
	uint16_t ADC_Value=0;
	// TODO: start ADC1 SS3 and read the ditigal output.
	ADC1_PSSI_R = ADC1_PSSI_SS3;            // 1) initiate SS3:1000
  while((ADC1_RIS_R&ADC1_RIS_SS3)==0){};   // 2) wait for conversion done
  ADC_Value = ADC1_SSFIFO3_R&0xFFF;   // 3 read result
  ADC1_ISC_R = ADC1_ISC_SS3;             // 4) acknowledge completion
	return 	ADC_Value;
}
//value coming in ADCVALUE [0:4095]
// Convert a ADC value to a value between [0, max_x_axis]
uint8_t ADCValue_To_X_AXIS(uint16_t ADCValue,uint8_t max_x_axis){
	uint8_t x_position=0;
	x_position = (ADCValue * (MAX_WIDTH - SHIP_WIDTH)) / ADC_RANGE;//divide by 49 to get the raito
  return x_position;
}