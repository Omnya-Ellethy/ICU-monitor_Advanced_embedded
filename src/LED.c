/*
 * Author : Omnya Ellithy
 * Date   : 26/05/2022
 * Version: 1.0.0
 * Module: LED
 * File Name: LED.c
 * description: source file for led driver
 */
#include "DIO.h"
#include "avr/io.h"
#include "LED.h"
#include "CONFIG.h"

/*
  initiate and configure pins for the leds used
*/
void led_Set(void){
  DIO_SetPinDirection (LED_PORT,LED_PIN,OUTPUT);  //set led pin as output
}

/*
  set led state to be ON
*/
void led_ON(void){
  DIO_WritePin(LED_PORT,LED_PIN,1);

}

/*
  set led state to be OFF
*/
void led_OFF(void){
  DIO_WritePin(LED_PORT,LED_PIN,0);

}

// int LED_GetState(int led)
// {
//   unsigned char ret = 0;

//         ret = DIO_ReadPort(LED_PORT); // led_port, led_pin

//     /* End of your code */
//     return ret;
// }