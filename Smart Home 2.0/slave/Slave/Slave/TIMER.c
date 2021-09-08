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
	
		/*choose ocr0*/
		OCR0 =78;
		
		/*choose mode*/
		CLR_BIT (TCCR0,WGM00);
		SET_BIT (TCCR0,WGM01);
	
		/*choose prescale clock put it at the end*/
		SET_BIT(TCCR0,CS00);
		CLR_BIT (TCCR0,CS01);
		SET_BIT(TCCR0,CS02);
	
		
	
		/*globel interupt*/
		sei ();
	
		/*set timer conter*/
		SET_BIT(TIMSK,OCIE0);
	
}






void Timer1_vInit_16bit(void){
	
	cli();	/* disableing interrupts	*/
	
	/* putting number to where the timer return to zero ( TICK = 100 ms ) */
	OCR1A = 781;
	
	sei(); /* global I bit to enable interrupt */
	
	/* choosing which mode to apply "CTC Mode" */
	CLR_BIT(TCCR1A,WGM10);
	CLR_BIT(TCCR1A,WGM11);
	
	SET_BIT(TCCR1B , WGM12);
	CLR_BIT(TCCR1B , WGM13);
	
	/* choosing which Prescaler "1024" factor */
	SET_BIT(TCCR1B,CS12);
	SET_BIT(TCCR1B,CS10);
	CLR_BIT(TCCR1B,CS11);
	
	
	
	
	SET_BIT(TIMSK,OCIE1A);  /* Enable Timer Compare match Interrupt */
	
}