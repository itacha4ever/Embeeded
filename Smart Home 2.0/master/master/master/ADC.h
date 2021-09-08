/*
 * ADC.h
 *
 * Created: 9/1/2018 4:51:19 PM
 *  Author: 3laa
 */ 


#ifndef ADC_H_
#define ADC_H_

void ADC_vint();
unsigned short ADC_u16Read();
void ADC_vStartconv();
unsigned short ADC_u16Read_intr();
void ADC_vStartconvin();

#define SET_BIT(reg,bit) reg|=(1<<bit)
#define CLR_BIT(reg,bit) reg&=(~(1<<bit))
#define TOG_BIT(reg,bit) reg^=(1<<bit)
#define READ_BIT_SET(reg,bit) ((reg&(1<<bit))>>bit)





#endif /* ADC_H_ */