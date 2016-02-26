#include <stdint.h>
#include "DAC.h"
#include "..//inc//tm4c123gh6pm.h"
//
//SSI0 PA2-PA5
//PA3 SSI0Fss
//PA2 SSI0Clk
//PA5 SSI0Tx
//PA4 SSI0Rx
//
//SSI1 PE0-PE3
//PE1 SSI1Fss
//PE0 SSI1Clk
//PE3 SSI1Tx
//PE2 SSI1Rx
//
//SSI2 PB4-PB7
//PB5 SSI1Fss
//PB4 SSI1Clk
//PB7 SSI1Tx
//PB6 SSI1Rx
//
void DAC_Init(uint16_t data){
  /*
	//SSI0
	SYSCTL_RCGCSSI_R |= 0x01;       // activate SSI0
  SYSCTL_RCGCGPIO_R |= 0x01;      // activate port A
  while((SYSCTL_PRGPIO_R&0x01) != 0x01){};// ready?
  GPIO_PORTA_AFSEL_R |= 0x2C;     // enable alt funct on PA2,3,5
  GPIO_PORTA_DEN_R |= 0x2C;       // configure PA2,3,5 as SSI
  GPIO_PORTA_PCTL_R = (GPIO_PORTA_PCTL_R&0xFF0F00FF)+0x00202200;
  GPIO_PORTA_AMSEL_R = 0;         // disable analog functionality on PA
  SSI0_CR1_R = 0x00000000;        // disable SSI, master mode
  SSI0_CPSR_R = 0x02;             // 8 MHz SSIClk 
  SSI0_CR0_R &= ~(0x0000FFF0);    // SCR = 0, SPH = 0, SPO = 0 Freescale
  SSI0_CR0_R |= 0x0F;             // DSS = 16-bit data
  SSI0_DR_R = data;               // load 'data' into transmit FIFO
  SSI0_CR1_R |= 0x00000002;       // enable SSI
	*/
	/*
	//SSI1
	SYSCTL_RCGCSSI_R |= 0x02;       // activate SSI1
  SYSCTL_RCGCGPIO_R |= 0x10;      // activate port E
  while((SYSCTL_PRGPIO_R&0x10) == 0){};// ready?
  GPIO_PORTE_AFSEL_R |= 0x0B;     // enable alt funct on PE0,1,3
  GPIO_PORTE_DEN_R |= 0x0B;       // configure PE0,1,3 as SSI
  GPIO_PORTE_PCTL_R = (GPIO_PORTE_PCTL_R&0xFFFF0F00)+0x00002022;
  GPIO_PORTE_AMSEL_R = 0;         // disable analog functionality on PE
  SSI1_CR1_R = 0x00000000;        // disable SSI, master mode
  SSI1_CPSR_R = 0x02;             // 8 MHz SSIClk 
  SSI1_CR0_R &= ~(0x0000FFF0);    // SCR = 0, SPH = 0, SPO = 0 Freescale
  SSI1_CR0_R |= 0x0F;             // DSS = 16-bit data
  SSI1_DR_R = data;               // load 'data' into transmit FIFO
  SSI1_CR1_R |= 0x00000002;       // enable SSI
	*/
	
	//SSI2
	SYSCTL_RCGCSSI_R |= 0x04;       // activate SSI2
  SYSCTL_RCGCGPIO_R |= 0x02;      // activate port B
  while((SYSCTL_PRGPIO_R&0x02) == 0){};// ready?
  GPIO_PORTB_AFSEL_R |= 0xB0;     // enable alt funct on PB4, 5, 7
  GPIO_PORTB_DEN_R |= 0xB0;       // configure PB4, 5, 7 as SSI
  GPIO_PORTB_PCTL_R = (GPIO_PORTB_PCTL_R&0x0F00FFFF)+(GPIO_PCTL_PB7_SSI2TX|GPIO_PCTL_PB5_SSI2FSS|GPIO_PCTL_PB4_SSI2CLK);
  GPIO_PORTB_AMSEL_R = 0;         // disable analog functionality on PB
  SSI2_CR1_R = 0x00000000;        // disable SSI, master mode
  SSI2_CPSR_R = 0x02;             // 8 MHz SSIClk 
  SSI2_CR0_R &= ~(0x0000FFF0);    // SCR = 0, SPH = 0, SPO = 0 Freescale
  SSI2_CR0_R |= 0x0F;             // DSS = 16-bit data
  SSI2_DR_R = data;               // load 'data' into transmit FIFO
  SSI2_CR1_R |= 0x00000002;       // enable SSI
	
}

// send the 16-bit code to the SSI
void DAC_Out(uint16_t code){
  /*
	//SSI0
	while((SSI0_SR_R&0x00000002)==0){};// wait until room in FIFO
  SSI0_DR_R = code; // data out
	*/
	/*
	//SSI1
	while((SSI1_SR_R&0x00000002)==0){};// wait until room in FIFO
  SSI1_DR_R = code; // data out
	*/
	//SSI2
	while((SSI2_SR_R&0x00000002)==0){};// wait until room in FIFO
  SSI2_DR_R = code; // data out
	
}
