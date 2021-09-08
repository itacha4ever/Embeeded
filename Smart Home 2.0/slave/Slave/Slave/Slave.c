/*
 * Slave.c
 *
 * Created: 10/24/2018 1:22:47 AM
 *  Author: 3laa
 */ 


#include <avr/io.h>
#include "COMMON_CONFIG.h"
int main(void)
{
   HOUSE_PORT = HOUSE_POWER ;		/* POWER FOR THE HOUSE	*/
   SENSOR_PORT = SENSOR_READ ;		/* SENSOR INTERFACE WITH THE HOUSE	*/
   
   Option O1 ;
   ptr_option = &O1 ;
   
   while(1)
   {
	   /*	RECIVEING WHICH FEATURE THE USER WANNA OPEN	*/
	   ptr_option->Recieve = SPI_u8Recive();
	   
	   switch(ptr_option->Recieve){
		   case ROOM1:
		   /* ACCESSING ROOM 1	*/
		   SET_BIT(ATR_Port , ROOM1_PIN);
		   break;
		   
		   case ROOM2:
		   /* ACCESSING ROOM 2	*/
		   SET_BIT(ATR_Port , ROOM2_PIN);
		   break;
		   
		   case ROOM3:
		   /* ACCESSING ROOM 3	*/
		   SET_BIT(ATR_Port , ROOM3_PIN);
		   break;
		   
		   
		   case LOGOUT_SLAVE:
		   /*	CLOSE THE HOUSE	*/
		   logout:			
		   
		   ATR_Port = stop ;
		   cli();	/* INTERRUPTS OFF */
		   break ;
		   
		   
		   case TV:
		   /*	ACCESSING TV	*/
		   Tv_access:	
		   	ptr_option->Tv_State = SPI_u8Recive();
		   
		   /* CHECK IF USER WANNA ON OR OFF TV	*/
		   if(ptr_option->Tv_State == ON){
			   /* TV ON	*/
			   vTv_ON();
			   
			   /*	IF USER WANNA LOGOUT	*/
			   if(SPI_u8Recive() == LOGOUT_SLAVE){
				   goto logout;
			   }

		   }
		   else if(ptr_option->Tv_State == OFF){
			   /* TV OFF	*/
			   vTv_ON();
			   goto Tv_access ;
		   }
		   break;
		   
		   
		   case AC:
		   /* ACCESSING AIRCONDTION	*/
		   AirCond_Access:
		   /* ASKING IF USER WANTS IT ON OR OFF	*/
		   ptr_option->AirCond_State =SPI_u8Recive();
		   
		   if(ptr_option->AirCond_State == ON){
			   sei();	/* INTERRUPTS ON	*/
			   
			   /*	RECIVEING DESIRED TEMPERATURE DEGREE FROM USER	*/
			   ptr_option->AirCondDegree = SPI_u8Recive();
			   
			   /* IF ON START CONVERTING THE TEMPERATURE SENSOR READ TO BINARY	..	THE ISR CONTROLS THE COMPARE STAGE */
			   ADC_vStartconvin();
			   
			   /* LOGOUT IF USER WANTS TO	*/
			   if(SPI_u8Recive() == LOGOUT_SLAVE){
				   goto logout;
			   }

		   }
		   /* CLOSE AIRCONDTION	*/
		   else if(ptr_option->AirCond_State == OFF){
			   cli();		/* INTERRUPTS OFF	*/
			   vAirCond_OFF();
		   }
		   
		   break;
		   
	   }
   }
}



/*	ADC INTTERRUPT	*/

ISR(ADC_vect){
	
	/*	READING ADC CONVERTED VALUE	*/
	ptr_option->ADC_read = ADC_u16Read_intr();
	
	/* COMPARE DESIRED TEMPERATURE DEGREE WITH THE SENSOR READING	*/
	vAirCond_ON(ptr_option->AirCondDegree);
	
	ADC_vStartconvin();
}
