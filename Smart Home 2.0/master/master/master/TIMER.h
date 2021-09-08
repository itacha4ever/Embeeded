/*
 * TIMER.h
 *
 * Created: 8/18/2018 4:57:03 PM
 *  Author: 3laa
 */ 


#ifndef TIMER_H_
#define TIMER_H_
void TIMER_vInt();

#define SET_BIT(reg,bit) reg|=(1<<bit)
#define CLR_BIT(reg,bit) reg&=(~(1<<bit))
#define TOG_BIT(reg,bit) reg^=(1<<bit)
#define READ_BIT_SET(reg,bit) ((reg&(1<<bit))>>bit)
void Timer1_vInit_16bit(void);
#endif /* TIMER_H_ */