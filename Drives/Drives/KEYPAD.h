/*
 * FUNC.h
 *
 * Created: 8/17/2018 10:04:37 AM
 *  Author: 3laa
 */ 


#ifndef KEYPAD_H_
#define KEYPAD_H_

void DIO_vsetpindirection(char ,char,char );
void DIO_vpullup(char ,char,char);
void KEYPAD_VINIT();
unsigned char KEYPAD_u8SCAN();

void SEVENSEG_display(char);
void SEVENSEG_vint();

#define PORT 'D'
#define PORTT 'B'
#define PIN0 0
#define PIN1 1
#define PIN2 2
#define PIN3 3
#define PIN4 4
#define PIN5 5
#define PIN6 6
#define PIN7 7
#define HIGH 1
#define LOW 0
#define NoScan 0xff

#define SET_BIT(reg,bit) reg|=(1<<bit)
#define CLR_BIT(reg,bit) reg&=(~(1<<bit))







#endif /* FUNC_H_ */