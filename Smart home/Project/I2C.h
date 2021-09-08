/*
 * I2C.h
 *
 * Created: 9/14/2018 5:18:09 PM
 *  Author: 3laa
 */ 


#ifndef I2C_H_
//#define F_CPU 8000000UL
//#include <util/delay.h>

#define F_SCL 400000UL // SCL frequency
#define Prescaler 1
#define TWBR_val ((((F_CPU / F_SCL) / Prescaler) - 16 ) / 2)
#define RW_I2C 0

void TWI_vMasterInt();
void TWI_MasterTrans(char,char);
void TWI_Start();
void TWI_MSendAdrrs(char);
void TWI_MSendData(char);
void TWI_MStop();

char TWI_Read();
char TWI_Slaveavilb();
void TWI_vSlvint(char);


#define SET_BIT(reg,bit) reg|=(1<<bit)
#define CLR_BIT(reg,bit) reg&=(~(1<<bit))
#define TOG_BIT(reg,bit) reg^=(1<<bit)
#define READ_BIT_SET(reg,bit) ((reg&(1<<bit))>>bit)




#endif /* I2C_H_ */