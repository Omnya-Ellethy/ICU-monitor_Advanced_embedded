/*
 * Author : Omnya Ellithy
 * Date   : 26/05/2022
 * Version: 1.0.0
 * Module: LCD
 * File Name: LCD.c
 * description: source file for lcd driver
 */
#include "stdio.h"

#include "LCD.h"
#include "DIO.h"
#include "util/delay.h"
#include "CONFIG.h"


static void LCD_LatchSignal(void);

void LCD_Init() {
    #if LCD_MODE == LCD_8BIT_MODE
        DIO_SetPortDirection(LCD_DPRT, OUTPUT);
        DIO_SetPinDirection(LCD_CPRT, LCD_RS, OUTPUT);
        DIO_SetPinDirection(LCD_CPRT, LCD_RW, OUTPUT);
        DIO_SetPinDirection(LCD_CPRT, LCD_EN, OUTPUT);
        LCD_SendCommand(0x38);
        LCD_SendCommand(0x0E);
        LCD_SendCommand(0x01);
        _delay_ms(2);
    #elif LCD_MODE == LCD_4BIT_MODE
        // TODO:
        DIO_SetPortDirection(LCD_DPRT,OUTPUT); /*configure data port as output*/
        _delay_ms(1);
        /*Configure the control pins(E,RS,RW) as output pins*/
        DIO_SetPinDirection(LCD_CPRT, LCD_RS, OUTPUT);
        DIO_SetPinDirection(LCD_CPRT, LCD_RW, OUTPUT);
        DIO_SetPinDirection(LCD_CPRT, LCD_EN, OUTPUT);
        LCD_SendCommand(0x32);/*init lcd for 4 bit data*/
        LCD_SendCommand(0x33); 
        LCD_SendCommand(0x28); /*init. LCD 2 lines,5×7 matrix*/
        LCD_SendCommand(0x0E);/*display on, cursor on*/
        LCD_SendCommand(0x01);/*clear LCD at the beginning*/
        LCD_SendCommand(0x06);/*shift cursor right*/
        _delay_ms(1);

    #else
        #error Please Select The Correct Mode of LCD
    #endif
}

void LCD_SendCommand(unsigned char Command) {
    #if LCD_MODE == LCD_8BIT_MODE
        DIO_WritePort(LCD_DPRT, Command);
        DIO_WritePin(LCD_CPRT, LCD_RS, 0);
        DIO_WritePin(LCD_CPRT, LCD_RW, 0);
        LCD_LatchSignal();
    #elif LCD_MODE == LCD_4BIT_MODE
        DIO_WritePort(LCD_DPRT, Command & 0xf0);
        DIO_WritePin(LCD_CPRT, LCD_RS, 0);/* Instruction Mode RS=0 */
        DIO_WritePin(LCD_CPRT, LCD_RW, 0);/* write data to LCD so RW=0 */
        LCD_LatchSignal();
        DIO_WritePort(LCD_DPRT, Command<<4);/* out the required command to the data bus D4 --> D7 */
        LCD_LatchSignal();
        _delay_ms(100);
    #else
        #error Please Select The Correct Mode of LCD
    #endif
}

void LCD_SendData(unsigned char Data) {
    #if LCD_MODE == LCD_8BIT_MODE
        DIO_WritePort(LCD_DPRT, Data);

        DIO_WritePin(LCD_CPRT, LCD_RS, 1);
        DIO_WritePin(LCD_CPRT, LCD_RW, 0);
        LCD_LatchSignal();
    #elif LCD_MODE == LCD_4BIT_MODE
        DIO_WritePort(LCD_DPRT, Data & 0xf0);
        DIO_WritePin(LCD_CPRT, LCD_RS, 1); /* Data Mode RS=1 */
        DIO_WritePin(LCD_CPRT, LCD_RW, 0); /* write data to LCD so RW=0 */
        LCD_LatchSignal();
        DIO_WritePort(LCD_DPRT, Data<<4);/* out the required data char to the data bus D4 --> D7 */
        LCD_LatchSignal();
        _delay_ms(2);
    #else
        #error Please Select The Correct Mode of LCD
    #endif
}
void LCD_SetCursorAt(unsigned char x, unsigned char y) {
  // TODO: 
  unsigned char firstCharAdr[] = {0x80, 0xC0, 0x94, 0xD4};
  LCD_SendCommand(firstCharAdr[y-1]+x-1);
  _delay_us(100);

}

void LCD_Print(const char* Str) {
  // TODO: 
  unsigned char i=0;
  while (Str[i]!=0)
  {
      LCD_SendData(Str[i]);
      i++;

  }
}
void LCD_Clear(void){

   LCD_SendCommand(0x01); 
}
static void LCD_LatchSignal(void) {
  DIO_WritePin(LCD_CPRT, LCD_EN, 1); /*enable lcd*/
  _delay_us(1);
  DIO_WritePin(LCD_CPRT, LCD_EN, 0);/*disable lcd*/
  _delay_us(100);
}
void LCD_IntgerToStr(int data){
    char buff[16]; /* String to hold the ascii result */
    itoa(data,buff,10); /* 10 for decimal */
    LCD_Print(buff);
}

void sendDataToProcessing(const char * symbol, int data )
{   
     
    LCD_SendCommand(0xC0);
    LCD_Print(symbol);  // symbol prefix tells Processing what type of data is coming
    LCD_SendCommand(0xC1);
    LCD_IntgerToStr(data); // the data to send culminating in a carriage return
    
    
  }