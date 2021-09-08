/*
 * LCD4.c
 *
 * Created: 8/17/2018 6:48:02 PM
 *  Author: 3laa
 */ 
//#include "LCD.h"
//#include <avr/io.h>
//#include <util/delay.h>
//#define  F_CPU 8000000ul
#include "COMMON_CONFIG.h"
	void SFE4()
{
	
		SET_BIT(PORTB,RS_LCD);
		_delay_ms(100);
		CLR_BIT(PORTB,RS_LCD);
		_delay_ms(100);
	
}

	void LCD4_vint()
{
		DDRA =0xf0;
		DDRB |=0x0e;
		CLR_BIT(PORTB,RW_LCD);
		LCD4_vSendCmd(0x33);
		LCD4_vSendCmd(0x32);
		LCD4_vSendCmd(0x28);
		LCD4_vSendCmd(0x01);
		LCD4_vSendCmd(0x0e);
		_delay_ms(20);
	
	
}

	void LCD4_vSendCmd(char cmd)
{
		CLR_BIT (PORTB,RS_LCD);
		PORTA &=0x0f;
		PORTA |=(cmd& 0xf0);
		SFE4();
		PORTA &=0x0f;
		PORTA |= (cmd<<4);
		SFE4();
}

	void LCD4_vsenddata(char data)
{
		SET_BIT (PORTB,RS_LCD);
		PORTA &=0x0f;
		PORTA |=(data& 0xf0);
		SFE4();
		PORTA &=0x0f;
		PORTA |= (data<<4);
		SFE4();
}

	void LCD4_vSDD(char *NM)
{
	
		while(*NM !='\0')
		{
			LCD4_vsenddata(*NM);
			NM++;
		
		}
}


	void LCD4_vCLEARS()
{	
		LCD_vSendCmd (CLR_DIS);
		_delay_ms(2000);
		LCD4_LD(1,1);
		
		
}

	void LCD4_vMOVECur(char row,char col)
{
		char temp;
		
			if (row==1)
			{
				temp =0x80+col-1; 
			}
	
			else if (row==2)
			{
		
				temp =0xC0+col-1;
			}
	
		LCD4_vSendCmd(temp);
}


void LCD4_print(char *str)
{
	unsigned char i = 0;
			
	while(str[i] != 0)
	{
		LCD4_vsenddata(str[i]);
		i++;
	}
}


void LCD4_LD(unsigned char x, unsigned char y)
{
unsigned char firstcharAdr[] = {0x80, 0xC0, 0x94, 0xD4};
LCD4_vSendCmd(firstcharAdr[y-1] + x - 1);
 _delay_us(100);
}