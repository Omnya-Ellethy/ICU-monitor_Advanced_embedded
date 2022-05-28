/*
 * Author : Omnya Ellithy
 * Date   : 20/05/2022
 * Version: 1.0.0
 */
#ifndef CONFIG_H
#define CONFIG_H






//////////LED Configration////////////
#define LED_PORT 'C'
#define LED_PIN 1

////////////BUZZER Configration /////////////////
#define BUZZER_PORT 'C'
#define BUZZER_PIN 2

///////////////////HBR Sensor configration/////////
#define HBR_Sensor_PIN 0     // Pulse Sensor purple wire connected to analog pin 0
#define HBR_Sensor_PORT "C"
#define ADC_PORT "C"


////////////LCD Configration//////////////

#define LCD_DPRT 'D'  // LCD DATA PORT
#define LCD_CPRT 'B'  // LCD COMMANDS PORT
//#define LCD_RS 0      // LCD RS
#define LCD_RW 1      // LCD RW
//#define LCD_EN 2      // LCD EN
#define LCD_RS 4      // LCD RS
#define LCD_EN 3 


#endif /* CONFIG_H */
