/*
 * TimerPWM.c
 *
 * Created: 9/15/2018 3:33:50 PM
 *  Author: 3laa
 */ 
//#include "TimerPWM.h"
#include "COMMON_CONFIG.h"

	void TimerPWM_vint()
{
		OCR0 =1; 
		
		/*choose mode*/
		SET_BIT(TCCR0,WGM01);
		SET_BIT(TCCR0,WGM00);
		
		/*sent inverter mode*/
		SET_BIT(TCCR0,COM01);
		CLR_BIT(TCCR0,COM00);
		 
		/*outpou for PWM wave*/
		SET_BIT(DDRB,PIN);
	 
		/*choose prescale clock put it at the end*/
		SET_BIT(TCCR0,CS00);
		CLR_BIT (TCCR0,CS01);
		SET_BIT(TCCR0,CS02);
	 
		/*globel interupt*/
		sei ();
		/*set timer conter*/
		SET_BIT(TIMSK,TOIE0);
	 	
}


	void TimerPWM_SetDC(float val)
{
		OCR0 =val*256;
}

