/*
 * COMMON_CONFIG.h
 *
 * Created: 9/29/2018 10:18:22 PM
 *  Author: 3laa
 */ 


#ifndef COMMON_CONFIG_H_
#define COMMON_CONFIG_H_

#define  F_CPU 8000000UL
#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "DIO.h"
#include "ADC.h"
#include "KEYPAD.h"
#include "LCD.h"
#include "EEPROM.h"
#include "UART.h"
#include "SPI.h"
#include "I2C.h"
#include "TIMER.h"
#include "TimerPWM.h"
#include "Led.h"

#include "Function.h"



#define SET_BIT(reg,bit) reg|=(1<<bit)
#define CLR_BIT(reg,bit) reg&=(~(1<<bit))
#define TOG_BIT(reg,bit) reg^=(1<<bit)
#define READ_BIT_SET(reg,bit) ((reg&(1<<bit))>>bit)




#endif /* COMMON_CONFIG_H_ */