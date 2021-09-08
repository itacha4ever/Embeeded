/*
 * LCD.c
 *
 * Created: 8/17/2018 4:07:33 PM
 *  Author: 3laa
 */ 
//#include "LCD.h"
//#include <avr/io.h>
//#include <util/delay.h>
//#define  F_CPU 8000000ul
#include "COMMON_CONFIG.h"
	void SFE()
{
	
		SET_BIT(PORTB,EN_LCD);
		_delay_ms(20);
		CLR_BIT(PORTB,EN_LCD);
		_delay_ms(20);
}

	void LCD_vint()
{
		DDRA =0xff;
		DDRB |=0x07;
		CLR_BIT(PORTB,RW_LCD);
		LCD_vSendCmd(0x38);
		LCD_vSendCmd(0x01);
		LCD_vSendCmd(0x0e);
		_delay_ms(20);
	
	
}

	void LCD_vSendCmd(char cmd)
{
		PORTA =cmd;
		CLR_BIT (PORTB,RS_LCD);
		SFE();
}
	
	
	void LCD_vsenddata(char data)
{
	  PORTA = data;
	  SET_BIT(PORTB,RS_LCD);
	  SFE();
}
	
	void LCD_vSDD(char *NM)
{
				
		while((*NM) !='\0')
		{
			LCD_vsenddata(*NM);
			NM++;
		
		}
}
	
	
	void LCD_vCLEARS()
{
		_delay_ms(1000);
		LCD_vSendCmd (CLR_DIS);
		
		LCD_LD(1,1);
	
}	

	void LCD_vMOVECur(char row,char col)
{	
		char temp;
	
			if (1==row)
			{
				temp =0x80 + (col-1); 
			}
		
			else if (2==row)
			{
				temp =0xC0 + (col-1);
			}
	
		LCD_vSendCmd(temp);
}

	
	void LCD_print(char *str)
	{
		unsigned char i = 0;
		
		while(str[i] != 0)
		{
			LCD_vsenddata(str[i]);
			i++;
		}
	}


	void LCD_LD(unsigned char col, unsigned char row)
	{
	unsigned char firstcharAdr[] = {0x80, 0xC0, 0x94, 0xD4};
	LCD_vSendCmd(firstcharAdr[row-1] + col - 1);
	_delay_us(100);
}




