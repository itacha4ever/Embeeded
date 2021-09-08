/*
 * CFile1.c
 *
 * Created: 8/3/2018 6:25:08 PM
 *  Author: 3laa
 */ 
#include <avr/io.h>
#include "LED.h"

void  LED_vInit(char portname,char pinnum){
	DIO_vsetpindirection(portname,pinnum,1);
	
}
void LED_vON(char portname,char pinnum){
	DIO_vWrite(portname ,pinnum,HIGH);
}	
void LED_vOFF(char portname,char pinnum){
	DIO_vWrite(portname ,pinnum,LOW);
}
void LED_vTOGGLE(char portname,char pinnum)
{
	
	 DIO_vToggle(portname ,pinnum);
}						