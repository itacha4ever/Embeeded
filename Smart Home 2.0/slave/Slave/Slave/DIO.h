/*
 * DIO.h
 *
 * Created: 8/3/2018 3:53:33 PM
 *  Author: 3laa
 */ 


#ifndef DIO_H_
#define DIO_H_

void DIO_vsetpindirection(char,char,char);
void DIO_vWrite(char,char,char);
void DIO_vToggle(char,char);
char DIO_vRead (char,char);
void DIO_vpullup(char,char,char);
void DIO_vPORTSET(char,char);

#define SET_BIT(reg,bit) reg|=(1<<bit)
#define CLR_BIT(reg,bit) reg&=(~(1<<bit))
#define TOG_BIT(reg,bit) reg^=(1<<bit)
#define READ_BIT_SET(reg,bit) ((reg&(1<<bit))>>bit)

#endif /* DIO_H_ */