/*
 * FUNC.c
 *
 * Created: 8/17/2018 10:04:22 AM
 *  Author: 3laa
 */ 
//#include <avr/io.h>
//#include "KEYPAD.h"
//#include <util/delay.h>
//#include "DIO.h"
#include "COMMON_CONFIG.h"

	void KEYPAD_VINIT()
{
		DIO_vsetpindirection(PORT,PIN0,1);
		DIO_vsetpindirection(PORT,PIN1,1);
		DIO_vsetpindirection(PORT,PIN2,1);
		DIO_vsetpindirection(PORT,PIN3,1);
		DIO_vsetpindirection(PORT,PIN4,0);
		DIO_vsetpindirection(PORT,PIN5,0);
		DIO_vsetpindirection(PORT,PIN6,0);
		DIO_vsetpindirection(PORT,PIN7,0);
	
		DIO_vWrite(PORT ,PIN4,HIGH);
		DIO_vWrite(PORT ,PIN5,HIGH);
		DIO_vWrite(PORT ,PIN6,HIGH);
		DIO_vWrite(PORT ,PIN7,HIGH);
}

	unsigned char KEYPAD_u8SCAN() 
{		
		char row,col;
	
			for(row=0; row<4;row++) 
			{
				DIO_vWrite(PORT ,PIN0,HIGH);
				DIO_vWrite(PORT ,PIN1,HIGH);
				DIO_vWrite(PORT ,PIN2,HIGH);
				DIO_vWrite(PORT ,PIN3,HIGH);
				DIO_vWrite(PORT ,row,LOW);
		 

				for (col=0;col<4;col++)
				{
					char KEYPAD[4][4]={{'7','8','9','/'},{'4','5','6','*'},{'1','2','3','-'},{'o','0','=','+'}};
						
					char temp =	 DIO_vRead (PORT ,(col +4));
					
						if (temp==0)
						{
			 				 return KEYPAD[row][col];
			 			}	
				}
	
			}
			
	
		return NoScan;
}



	void SEVENSEG_vint()
{
	
		DIO_vsetpindirection(PORTT,PIN0,1);
		DIO_vsetpindirection(PORTT,PIN1,1);
		DIO_vsetpindirection(PORTT,PIN2,1);
		DIO_vsetpindirection(PORTT,PIN3,1);
		DIO_vsetpindirection(PORTT,PIN4,1);
		DIO_vsetpindirection(PORTT,PIN5,1);
		DIO_vsetpindirection(PORTT,PIN6,1);
		DIO_vsetpindirection(PORTT,PIN7,1);
}
	


	void SEVENSEG_display(char dig)
{
		DIO_vPORTSET(PORT, dig);
}