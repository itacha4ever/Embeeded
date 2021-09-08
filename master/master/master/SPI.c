/*
 * SPI.c
 *
 * Created: 9/8/2018 5:04:21 PM
 *  Author: 3laa
 */ 

//#include "SPI.h"
#include "COMMON_CONFIG.h"

	void SPI_vINTMASTRE()
{
		SET_BIT(SPCR,SPR0);
		SET_BIT(SPCR,MSTR);
	
		SET_BIT(DDRB,ss);
		SET_BIT(DDRB,mosi);
		SET_BIT(DDRB,sck);
		SET_BIT(SPCR,CPOL);
		SET_BIT(SPCR,CPHA);
		SET_BIT(PORTB,ss);
		SET_BIT(SPCR,SPE);
}


	void SPI_vINTSlave()
{
		CLR_BIT(SPCR,MSTR);
		SET_BIT(DDRB,miso);
		SET_BIT(SPCR,CPOL);
		SET_BIT(SPCR,CPHA);
		SET_BIT(SPCR,SPE);
		
}


	void SPI_vTransf(char data)
{
		CLR_BIT(PORTB,ss);
	
		SPDR = data;
	
		while(!(READ_BIT_SET(SPSR,SPIF)))
	
		{
			//wait
		}
	
		SET_BIT(PORTB,ss);	
}


	char SPI_u8Recive()
{
		while(!(READ_BIT_SET(SPSR,SPIF)))
	
		{
			//wait
		}
		
		return SPDR;
	
}