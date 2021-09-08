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

#define TICK 10
#define FIVE_MIN (300*TICK)
#define Q_SEC (2.5*TICK)
#define HALF_SEC (5*TICK)
#define FIVE_MINUTES (5*TICK)


#define SET_BIT(reg,bit) reg|=(1<<bit)
#define CLR_BIT(reg,bit) reg&=(~(1<<bit))
#define TOG_BIT(reg,bit) reg^=(1<<bit)
#define READ_BIT_SET(reg,bit) ((reg&(1<<bit))>>bit)

#define HIGH 1
#define LOW 0
#define stop 0x00
#define CLEAR 0xFF
#define keyon 0x0F
#define LOGOUT_SLAVE '9'
#define SECOND_ROW 2
#define FIRST_ROW 1
	
#define admin_addrs 0x10
#define BLock_Addrs 0x20
#define Blocked_count 0x30
#define GUEST_addrs 0x40


#define Admin '1'
#define Guest '0'
#define MENU '='
#define LOUT '*'
#define NEXT '-'
#define ENTER '+'

#define LED_Power DDRC = 0xFF
#define LED_PORT PORTC
#define Logout_led 1
#define Login_led 0
#define Block_led 2
#define TICK_TIMER1 100

#define ATR_Port PORTC
#define ROOM1 '0'
#define ROOM2 '1'
#define ROOM3 '2'
#define TV '3'
#define AC '4'

#define ON '1'
#define OFF '0'
#define K_ON '1'
#define K_OFF '0'
#define PASS HIGH
#define FAIL LOW
#define keypad DDRD




/* FUNCTION THAT MAKES A SIMPLE EQUATION TO SAVE THE PASSWORD IN 1 BYTE	*/

char inline Password_inFun(char * Pw_ptr){
	char i,x , j = 4 ;
	
	char Password = 0;
	for( i = 0 ; i < 4 ; ++i , --j)
	{
		x = 1 ;
		for( ; j > 1 ; --j){
			x *= 2 ;
		}
		Password += (*(Pw_ptr + i)) * x ;
	}
	
	return Password ;
}

/***********************************************************************/


typedef struct counters {
	volatile unsigned char keypad_count ;
	volatile unsigned short pw_count ;
	volatile unsigned char EEPROM_count ;
	volatile unsigned char BlockAdressCounter ;
	volatile unsigned short Interrupt ;
	volatile unsigned short BlockCount1 ;
} Counters ;

typedef struct acess {
	char FirstAcessRead ;
	char SecondAcessRead ;
	char AccessHouse ;
	char AccessTV ;
	
	char AccessAirCond ;
	char AirCond_Degree ;
	
	char Admin_or_Guest ;
} Acess ;


Counters *PTR_COUNT ;
Acess *PTR_ACESS ;

#endif /* COMMON_CONFIG_H_ */