/*
 * Author : Abdullah Drwesh
 * Date   : 12/12/2021
 * Version: 1.0.0
 */
#include "DIO.h"
#include "avr/io.h"
#include "BUZZER.h"
#include "CONFIG.h"

void BUZZER_Set(void){
  DIO_SetPinDirection (BUZZER_PORT,BUZZER_PIN,OUTPUT);  //set alarm pin as output

}

void BUZZER_ON(void){
  DIO_WritePin(BUZZER_PORT,BUZZER_PIN,1);   //turn on alarm

}

void BUZZER_OFF(void){
  DIO_WritePin(BUZZER_PORT,BUZZER_PIN,0); //turn off alarm

}