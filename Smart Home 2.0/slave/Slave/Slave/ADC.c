/*
 * ADC.c
 *
 * Created: 9/1/2018 4:51:34 PM
 *  Author: 3laa
 */ 

//#include <avr/io.h>
//#include <avr/interrupt.h>
//#include "ADC.h"
#include "COMMON_CONFIG.h"


	void ADC_vint()
{
	
		/*enable ADC*/
		SET_BIT(ADCSRA,ADEN);
	
		/* choose Vref*/
		SET_BIT(ADMUX,REFS0);
		CLR_BIT(ADMUX,REFS1);
	
		/* chose clock*/
		SET_BIT(ADCSRA,ADPS2);
		SET_BIT(ADCSRA,ADPS1);
		SET_BIT(ADCSRA,ADPS0);
	
		/*global interrupt */
		sei();
		/*set interrupt*/
		SET_BIT(ADCSRA,ADIE);
	
}


	unsigned short ADC_u16Read()
{
	
		short reading=0;
		/* request new conversion*/
		SET_BIT(ADCSRA,ADSC);
	
		/*wait for ADIF table*/
		while(READ_BIT_SET(ADCSRA,ADIF)==0)
		{
			//wait
		}
				
		/* read bits*/
		reading |=ADCL;
		reading |=(short)(ADCH<<8);
		
		return reading;
	
}


	void ADC_vStartconvin()
{
		/* request new conversion*/
		SET_BIT(ADCSRA,ADSC);
}
	
	unsigned short ADC_u16Read_intr()
{
		short reading=0;
		
		/* read bits*/
		reading |=ADCL;
		reading |=(short)(ADCH<<8);
	
		return reading;
}