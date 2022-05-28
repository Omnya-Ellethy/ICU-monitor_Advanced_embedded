/**
 * Copyright (C) PlatformIO <contact@platformio.org>
 * See LICENSE for details.
 */
#include<time.h>
#include"util/delay.h"
#include <math.h>
#include <stdio.h>
#include <avr/interrupt.h>
#include <avr/io.h>

#include "LCD.h"
#include "LED.h"
#include "BUZZER.h"
#include "HBR_Sensor.h"




extern volatile int BPM; 
extern volatile int QS;

  

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////



void interruptSetup()
{     
  // Initializes Timer2 to throw an interrupt every 2mS.
  TCCR2A = 0x02;     // DISABLE PWM ON DIGITAL PINS 3 AND 11, AND GO INTO CTC MODE
  TCCR2B = 0x06;     // DON'T FORCE COMPARE, 256 PRESCALER 
  OCR2A = 0X7C;      // SET THE TOP OF THE COUNT TO 124 FOR 500Hz SAMPLE RATE
  TIMSK2 = 0x02;     // ENABLE INTERRUPT ON MATCH BETWEEN TIMER2 AND OCR2A
  sei();             // MAKE SURE GLOBAL INTERRUPTS ARE ENABLED      
} 


// THIS IS THE TIMER 2 INTERRUPT SERVICE ROUTINE. 
// Timer 2 makes sure that we take a reading every 2 miliseconds
ISR(TIMER2_COMPA_vect)
{                          // triggered when Timer2 counts to 124
            cli(); 
            HBR_Calculation();
            
                      sei();                                     // enable interrupts when youre done!
}


//***************************main*********************
int main(void) 
{
  
  // clock_t time_req;
  // time_req = clock();
  LCD_Init();
  //time_req = clock()- time_req;
  //cout ("Processor time taken for multiplication: "<< (float)time_req/CLOCKS_PER_SEC << " seconds" << endl);
  //printf("Processor time taken for multiplication: ",(float)time_req/CLOCKS_PER_SEC)
  interruptSetup();                 
  HBR_Set();
  led_Set();
  
  LCD_Print("Heart Beat Rate:");
  
  while (1)
  { 

    
  }
  return 0; 
  }
