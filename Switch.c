//Switch.c
#include <stdint.h>
#include "..//inc//tm4c123gh6pm.h"
#include "Switch.h"

//Use Port D switches
void Switch_Init(){
	SYSCTL_RCGC2_R |= 0x8;												//Turn on Port D
	while((SYSCTL_RCGC2_R & 0x8) != 0x8){
	}//wait to stabilize
  GPIO_PORTD_DEN_R |= 0x0F;      							//enable PD 0 - 3
  GPIO_PORTD_DIR_R &= ~(0x0F);   			   		//PD 0 - 3 are inputs
  GPIO_PORTD_AFSEL_R &= ~(0x0F);   				//disable alternative for PD 0 - 3
	GPIO_PORTD_PCTL_R &= ~0x0000FFFF; //  configure PD 0 ~ 3 as GPIO
  GPIO_PORTD_AMSEL_R &= ~0x0F;  //    disable analog functionality on PD 0 ~ 3
	GPIO_PORTD_PDR_R |= 0x0F;
}

uint8_t Switch_In(void){
  return GPIO_PORTD_DATA_R&0x0F;
}
