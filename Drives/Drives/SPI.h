/*
 * SPI.h
 *
 * Created: 9/8/2018 5:04:41 PM
 *  Author: 3laa
 */ 


#ifndef SPI_H_
#define SPI_H_

//#define F_CPU 8000000ul
//#include <util/delay.h>
//#include <avr/io.h>

void SPI_vINTMASTRE();
void SPI_vINTSlave();
void SPI_vTransf(char);
char SPI_u8Recive();

#define SET_BIT(reg,bit) reg|=(1<<bit)
#define CLR_BIT(reg,bit) reg&=(~(1<<bit))
#define TOG_BIT(reg,bit) reg^=(1<<bit)
#define READ_BIT_SET(reg,bit) ((reg&(1<<bit))>>bit)


#endif /* SPI_H_ */