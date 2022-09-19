// IO.c
// This software configures the switch and LED
// You are allowed to use any switch and any LED, 
// although the Lab suggests the SW1 switch PF4 and Red LED PF1
// Runs on TM4C123
// Program written by: Yang Tsung-Hsien
// Date Created: 31.07.2022
// Last Modified:  19.09.2022
// Lab number: 7


#include "../inc/tm4c123gh6pm.h"
#include <stdint.h>
#include "ST7735.h"

//------------IO_Init------------
// Initialize GPIO Port for a switch and an LED
// Input: none
// Output: none
void IO_Init(void) {
 // --UUU-- Code to initialize PF4 and PF2
	volatile unsigned long delay;
	SYSCTL_RCGCGPIO_R |= 0x20;
	delay = SYSCTL_RCGCGPIO_R;
	GPIO_PORTF_AMSEL_R &= 0x00; // disable analog function
	GPIO_PORTF_PCTL_R &= 0x00000000; // GPIO clear bit PCTL
	GPIO_PORTF_DIR_R &= ~0x10; // PF4 input
	GPIO_PORTF_DIR_R |= 0x04;  // PF2 output
	GPIO_PORTF_AFSEL_R &= 0x00; // no alternate function
	GPIO_PORTF_PUR_R |= 0x10; // enable pull up resistor on PF4
	GPIO_PORTF_DEN_R |= 0x14; //enable digital pins on PF2 & PF4
	
	//unsigned long sw1 = GPIO_PORTF_DATA_R & 0x10;  // read PF4 
	//unsigned long LED = GPIO_PORTF_DATA_R |= 0x04; // PF2 on
	
}

//------------IO_HeartBeat------------
// Toggle the output state of the  LED.
// Input: none
// Output: none
void IO_HeartBeat(void) {
 // --UUU-- PF2 is heartbeat
	
	GPIO_PORTF_DATA_R ^= 0x04;
}


//------------IO_Touch------------
// wait for release and press of the switch
// Delay to debounce the switch
// Input: none
// Output: none
void IO_Touch(void) {
 // --UUU-- wait for release; delay for 20ms; and then wait for press
	while(1)
	{
		if( (GPIO_PORTF_DATA_R & 0x10) == 0)
			break;
	}
	
	Delay1ms(20);
	
	while(1)
	{
		if((GPIO_PORTA_AHB_DATA_R & 0x10) != 0)
			return;
	
	}
	
}  

