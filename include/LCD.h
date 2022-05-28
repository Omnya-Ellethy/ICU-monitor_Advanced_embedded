/*
 * Author : Omnya Ellithy
 * Date   : 26/05/2022
 * Version: 1.0.0
 * Module: LCD
 * File Name: LCD.h
 * description: header file for lcd driver
 */
#ifndef LCD_H
#define LCD_H

/* LCD Modes */
#define LCD_8BIT_MODE 0
#define LCD_4BIT_MODE 1

/* User Input */
//#define LCD_MODE LCD_8BIT_MODE
#define LCD_MODE LCD_4BIT_MODE


/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
void LCD_Init(void);

void LCD_SendCommand(unsigned char Command);

void LCD_SendData(unsigned char Data);

void LCD_SetCursorAt(unsigned char x, unsigned char y);

void LCD_Print(const char * Str);
void LCD_Clear(void);
void LCD_IntgerToStr(int data);
void sendDataToProcessing(const char * symbol, int data );


#endif /* LCD_H */
