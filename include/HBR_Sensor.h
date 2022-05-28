/*
 * Author : Omnya Ellithy
 * Date   : 26/05/2022
 * Version: 1.0.0
 * Module: heart beat rate sensor module
 * File Name: HBR_sensor.h
 * description: header file for heart beat rate sensor driver
 */
#ifndef HBR_Sensor_H
#define HBR_Sensor_H

#define true 1
#define false 0

void HBR_Set(void);
int HBR_readings(void);
void HBR_Calculation(void);
void monitor_data(void);



#endif /* HBR_Sensor_H */
