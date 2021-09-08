/*
 * EEPROM.h
 *
 * Created: 8/18/2018 3:28:46 PM
 *  Author: 3laa
 */ 


#ifndef EEPROM_H_
#define EEPROM_H_

void EEPROM_vWrite(char, unsigned short );
unsigned char EEPROM_vRead(unsigned short);



#define SET_BIT(reg,bit) reg|=(1<<bit)
#define CLR_BIT(reg,bit) reg&=(~(1<<bit))
#define TOG_BIT(reg,bit) reg^=(1<<bit)
#define READ_BIT_SET(reg,bit) ((reg&(1<<bit))>>bit)


#endif /* EEPROM_H_ */