/*
 * Author : Omnya Ellithy
 * Date   : 26/05/2022
 * Version: 1.0.0
 * Module: heart beat rate sensor module
 * File Name: HBR_sensor.c
 * description: source file for heart beat rate sensor driver
 */
#include "DIO.h"
#include "ADC.h"
#include "LED.h"
#include "LCD.h"
#include "BUZZER.h"
#include"util/delay.h"
#include "avr/io.h"
#include "HBR_Sensor.h"
#include "CONFIG.h"


/**
 * 
   set port and pin for the data from the sensor
*/
void HBR_Set(void){
   ADC_Init();  
   ADC_SelectChannel(HBR_Sensor_PIN);

}

/**
    return data gotten from the sensor the converted by the ADC
    @return signal converted by ADC.
*/
int HBR_readings(void){

   int signal = ADC_ReadChannel(HBR_Sensor_PIN);  
   return signal;
}
//  VARIABLES
int pulsePin = 0;                 // Pulse Sensor purple wire connected to analog pin 0
int blinkPin = 13;                // pin to blink led at each beat

// these variables are volatile because they are used during the interrupt service routine!
volatile int BPM;                   // used to hold the pulse rate
volatile int Signal;                // holds the incoming raw data
volatile int IBI = 600;             // holds the time between beats, the Inter-Beat Interval
volatile int Pulse = false;     // true when pulse wave is high, false when it's low
volatile int QS = false;        // becomes true when Arduoino finds a beat.






volatile int rate[10];                    // used to hold last ten IBI values
volatile unsigned long sampleCounter = 0;          // used to determine pulse timing
volatile unsigned long lastBeatTime = 0;           // used to find the inter beat interval
volatile int P =512;                      // used to find peak in pulse wave
volatile int T = 512;                     // used to find trough in pulse wave
volatile int thresh = 750;                // used to find instant moment of heart beat
volatile int amp = 100;                   // used to hold amplitude of pulse waveform
volatile int firstBeat = true;        // used to seed rate array so we startup with reasonable BPM
volatile int secondBeat = true;       // used to seed rate array so we startup with reasonable BPM

void HBR_Calculation(void){
   
   Signal = HBR_readings();              // read the Pulse Sensor 
              sampleCounter += 2;                         // keep track of the time in mS with this variable
              int N = sampleCounter - lastBeatTime;       // monitor the time since the last beat to avoid noise

          //  find the peak and trough of the pulse wave
              if(Signal < thresh && N > (IBI/5)*3){       // avoid dichrotic noise by waiting 3/5 of last IBI
                  if (Signal < T){                        // T is the trough
                      T = Signal;                         // keep track of lowest point in pulse wave 
                  }
                }
                
              if(Signal > thresh && Signal > P){          // thresh condition helps avoid noise
                  P = Signal;                             // P is the peak
                }                                        // keep track of highest point in pulse wave
              
            // signal surges up in value every time there is a pulse
            if (N > 250)
              {                                   // avoid high frequency noise
                if ( (Signal > thresh) && (Pulse == false) && (N > (IBI/5)*3) ){        
                  Pulse = true;                               // set the Pulse flag when we think there is a pulse
                  //digitalWrite(blinkPin,1);                // turn on pin 13 LED
                  IBI = sampleCounter - lastBeatTime;         // measure time between beats in mS
                  lastBeatTime = sampleCounter;               // keep track of time for next pulse
                      
                      if(firstBeat){                         // if it's the first time we found a beat, if firstBeat == TRUE
                          firstBeat = false;                 // clear firstBeat flag
                          return;                            // IBI value is unreliable so discard it
                          }   
                      if(secondBeat){                        // if this is the second beat, if secondBeat == TRUE
                          secondBeat = false;                 // clear secondBeat flag
                            for(int i=0; i<=9; i++){         // seed the running total to get a realisitic BPM at startup
                                  rate[i] = IBI;                      
                                  }
                          }
                        
                // keep a running total of the last 10 IBI values
                  double runningTotal = 0;                   // clear the runningTotal variable    

                  for(int i=0; i<=8; i++){                // shift data in the rate array
                        rate[i] = rate[i+1];              // and drop the oldest IBI value 
                        runningTotal += rate[i];          // add up the 9 oldest IBI values
                      }
                      
                  rate[9] = IBI;                          // add the latest IBI to the rate array
                  runningTotal += rate[9];                // add the latest IBI to runningTotal
                  runningTotal /= 10;                     // average the last 10 IBI values 
                  BPM = 60000/runningTotal;               // how many beats can fit into a minute? that's BPM!
                  
                  
                  QS = true;                              // set Quantified Self flag 
                  // QS FLAG IS NOT CLEARED INSIDE THIS ISR
                  }                      
              }

            if (Signal < thresh && Pulse == true)
            {     // when the values are going down, the beat is over
              // digitalWrite(blinkPin,0);            // turn off pin 13 LED
                Pulse = false;                         // reset the Pulse flag so we can do it again
                amp = P - T;                           // get amplitude of the pulse wave
                thresh = amp/2 + T;                    // set thresh at 50% of the amplitude
                P = thresh;                            // reset these for next time
                T = thresh;
            }
            
            if (N > 2500){                             // if 2.5 seconds go by without a beat
                thresh = 512;                          // set thresh default
                P = 512;                               // set P default
                T = 512;                               // set T default
                lastBeatTime = sampleCounter;          // bring the lastBeatTime up to date        
                firstBeat = true;                      // set these to avoid noise
                secondBeat = true;                     // when we get the heartbeat back
                
              }
              monitor_data();
}

void monitor_data(void){
   if (QS == true){                       // Quantified Self flag is true when ISR get BPM Value  finds a heartbeat
                
        if((BPM>190)) {
          led_ON();
          BUZZER_ON();
          
          LCD_Clear();
          LCD_Print("alert BPM>190");

        }else if ((BPM<60))
        {
           led_ON();
           BUZZER_ON();
          
          LCD_Clear();
          LCD_Print("alert BPM<60");
        }
        
        else{
         led_OFF();
         BUZZER_OFF();
         LCD_Clear();
         LCD_Print("Heart Beat Rate:");
        }
        sendDataToProcessing("B",BPM);   // send heart rate with a 'B' prefix
        QS = false;                      // reset the Quantified Self flag for next time
        //_delay_ms(2);  
    
    }
}