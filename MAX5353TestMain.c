// MAX5353TestMain.c
// Runs on LM4F120/TM4C123
// Test the functions provided in MAX5353.c by outputting
// a sine wave at a particular frequency.
// Daniel Valvano
// September 11, 2013

/* This example accompanies the book
   "Embedded Systems: Real Time Interfacing to Arm Cortex M Microcontrollers",
   ISBN: 978-1463590154, Jonathan Valvano, copyright (c) 2014

 Copyright 2014 by Jonathan W. Valvano, valvano@mail.utexas.edu
    You may use, edit, run or distribute this file
    as long as the above copyright notice remains
 THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 VALVANO SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL,
 OR CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 For more information about my classes, my research, and my books, see
 http://users.ece.utexas.edu/~valvano/
 */

// SSI0Clk (SCLK, pin 4) connected to PA2
// SSI0Fss (!CS, pin 2) connected to PA3
// SSI0Tx (DIN, pin 3) connected to PA5
// see Figure 7.19 for complete schematic

#include <stdint.h>
#include "PLL.h"
#include "DAC.h"
#include "LED.h"
#include "Timer0A.h"
#include "SysTick.h"
#include "..//inc//tm4c123gh6pm.h"

// 12-bit 32-element sine wave
// multiply each value by 2 to shift into bits 12:1 of SSI packet
// three control bits in 15:13 are all zero for immediate DAC update
// book figure shows MAX5353 in unipolar rail-to-rail configuration
// that means when wave[n] = 0x0000 (LSB = 0), output = 0
//                 wave[n] = 0x1000 (LSB = 0), output = Vref
//                 wave[n] = 0x1FFE (LSB = 0), output = 2*Vref
const unsigned short Wave[32] = {  
  1024,1122,1215,1302,1378,1440,1486,1514,1524,1514,1486,
  1440,1378,1302,1215,1122,1024,926,833,746,670,608,
  562,534,524,534,562,608,670,746,833,926
};  


const unsigned short Trumpet[32] = {
	1007, 1088, 1156, 1194, 1067, 789, 303, 99, 789, 1510, 1476,
	1173, 1067, 1037, 1084, 1062, 1011, 1015, 1045, 1062, 1011, 1011,
	1058, 1113, 1084, 1075, 1079, 1105, 1088, 1049, 1015, 1045
};

struct MusicSheet{//make this more clear
	int8_t instrument1[10];
	int8_t noteLength1[10];//duration
	int8_t notePitch1[10];
	int8_t instrument2[10];
	int8_t noteLength2[10];
	int8_t notePitch2[10];
};

uint8_t dacIndex;
void PlayWave(void){
  dacIndex = (dacIndex+1)&0x1F; // 0 to 31
  DAC_Out(Wave[dacIndex]);
}
	
int main(void){
  PLL_Init(Bus80MHz);                   // 80 MHz
	dacIndex = 0;
  DAC_Init(0x1000);                  // initialize with command: Vout = Vref
	LED_Init();
  //SysTick_Init();
	Timer0A_Init(&PlayWave, 5681);
  while(1){
		LED_RedToggle();
		//PlayWave();
    // calculated frequencies are not exact, due to the impreciseness of delay loops
    // assumes using 16 MHz PIOSC (default setting for clock source)
    // maximum frequency with 16 MHz PIOSC: (8,000,000 bits/1 sec)*(1 sample/16 bits)*(1 wave/32 sample) = 15,625 Hz
    // maximum frequency with 20 MHz PLL: (10,000,000 bits/1 sec)*(1 sample/16 bits)*(1 wave/32 sample) = 19,531.25 Hz
//    SysTick_Wait(0);                 // ?? kHz sine wave (actually 12,000 Hz)
//    SysTick_Wait(9);                 // 55.6 kHz sine wave (actually 10,000 Hz)
//    SysTick_Wait(15);                // 33.3 kHz sine wave (actually 8,500 Hz)
//    SysTick_Wait(19);                // 26.3 kHz sine wave (actually 8,500 Hz)
//    SysTick_Wait(64);                // 7.81 kHz sine wave (actually 4,800 Hz)
//    SysTick_Wait(99);                // 5.05 kHz sine wave (actually 3,500 Hz)
//    SysTick_Wait(1136);              // 440 Hz sine wave (actually 420 Hz)
//    SysTick_Wait(50000);             // 10 Hz sine wave (actually 9.9 Hz)
  }
}
