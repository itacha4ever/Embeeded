/*
 * LCD.h
 *
 * Created: 8/17/2018 4:07:48 PM
 *  Author: 3laa
 */ 


#ifndef LCD_H_
#define LCD_H_

void SFE();
void LCD_vint();
void LCD_vSendCmd(char );
void LCD_vsenddata(char);
void LCD_vSDD(char* );

void SFE4();
void LCD4_vint();
void LCD4_vSendCmd(char );
void LCD4_vsenddata(char);
void LCD4_vSDD(char* );

#define SET_BIT(reg,bit) reg|=(1<<bit)
#define CLR_BIT(reg,bit) reg&=(~(1<<bit))
#define TOG_BIT(reg,bit) reg^=(1<<bit)
#define READ_BIT_SET(reg,bit) ((reg&(1<<bit))>>bit)


#define D0 0
#define D1 1
#define D2 2
#define D3 3
#define D4 4
#define D5 5
#define D6 6
#define D7 7
#define EN_LCD 3
#define RW_LCD 2
#define RS_LCD 1

char temp;



#endif /* LCD_H_ */