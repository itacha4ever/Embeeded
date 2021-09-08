/*
 * EEPROM.c
 *
 * Created: 8/18/2018 3:29:01 PM
 *  Author: 3laa
 */ 
//#include <avr/io.h>
//#include "EEPROM.h"
#include "COMMON_CONFIG.h"
	void EEPROM_vWrite(char data, unsigned short addrs)
{
		while (READ_BIT_SET(EECR,EEWE)==1)
		{
			/*to wait the first wirte instruction */
		} 
		
		EEDR= data;
		
		EEAR=addrs;
		
		SET_BIT(EECR,EEMWE);
		SET_BIT(EECR,EEWE);
	
		
}

	unsigned char EEPROM_vRead(unsigned short addrs)
{ 
 		while (READ_BIT_SET(EECR,EEWE)==1)
		 {
			 /*to check no one write while i read*/
		 }
			  
		EEAR = addrs;
		SET_BIT(EEDR,EERE);
		return EEDR;
}