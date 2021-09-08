/*
 * UART.h
 *
 * Created: 9/7/2018 3:47:36 PM
 *  Author: 3laa
 */ 


#ifndef UART_H_
#define UART_H_
#define F_OSC 8000000ul
//#define F_CPU 8000000ul
//#include <util/delay.h>
//#include <avr/interrupt.h>

void UART_vSendData(char data);
char UART_u8ReceiveData();
void UART_vInit(long baud);
#define SET_BIT(reg,bit) reg|=(1<<bit)
#define CLR_BIT(reg,bit) reg&=(~(1<<bit))
#define TOG_BIT(reg,bit) reg^=(1<<bit)
#define READ_BIT_SET(reg,bit) ((reg&(1<<bit))>>bit)



#endif /* UART_H_ */