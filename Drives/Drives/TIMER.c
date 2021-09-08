/*
 * TIMER.c
 *
 * Created: 8/18/2018 4:57:16 PM
 *  Author: 3laa
 */ 
//#include <avr/io.h>
//#include "TIMER.h"
//#include <avr/interrupt.h>
#include "COMMON_CONFIG.h"

	void TIMER_vInt()
{
		/*choose mode*/
		CLR_BIT (TCCR0,WGM00);
		SET_BIT (TCCR0,WGM01);
	
		/*choose prescale clock put it at the end*/
		SET_BIT(TCCR0,CS00);
		CLR_BIT (TCCR0,CS01);
		SET_BIT(TCCR0,CS02);
	
		/*choose ocr0*/
		OCR0 =78;
	
		/*globel interupt*/
		sei ();
	
		/*set timer conter*/
		SET_BIT(TIMSK,OCIE0);
	
}