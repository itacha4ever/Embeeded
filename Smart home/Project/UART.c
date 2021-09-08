/*
 * UART.c
 *
 * Created: 9/7/2018 3:47:23 PM
 *  Author: 3laa
 */ 
//#include "UART.h"
//#include <avr/io.h>
//#include <avr/interrupt.h>
//#include <util/delay.h>
#include "COMMON_CONFIG.h"

	void UART_vInit(long baud)
{
		/*1 - Choose baud rate that will be used by sender and receiver by writing to UBRRL/UBRRH*/
		short rate =(F_OSC/(16*baud));
		UBRRL =(char) rate;
		UBRRH = (char) (rate>>8);
		
		/*2 - Enable UART Sender & Receiver*/
		SET_BIT(UCSRB,TXEN);
		SET_BIT(UCSRB,RXEN);

		/*3 - Choose asynchronous or synchronous from UCSRC.*/
		CLR_BIT(UCSRC,UMSEL);

		/*4 - Choose number of data bits to be sent from UCSRC We will work with 8 bits.*/
		SET_BIT(UCSRC,UCSZ0);
		SET_BIT(UCSRC,UCSZ1);
		CLR_BIT(UCSRC,UCSZ2);
	
		sei(); /*enable Interrupt */
	
		SET_BIT(UCSRB,RXCIE); /*enable Interrupt receiving  */
	
		SET_BIT(UCSRB,TXCIE); /*enable Interrupt transmit  */


}


	void UART_vSendData(char data)
{	
		/*Put data to transmit buffer*/
		UDR = data;

		/*Wait for Transmit buffer to be empty*/
		while(!(READ_BIT_SET(UCSRA,TXC)))
		{
			/*wait until transmit done*/
		}
}


	char UART_u8ReceiveData()
{
		while(!(READ_BIT_SET(UCSRA,RXC)))
		{
			/*Wait for receive buffer to be filled with data*/
		}
	
		/*Receive data from Data Buffer*/
		return UDR;
}