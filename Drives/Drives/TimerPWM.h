/*
 * TimerPWM.h
 *
 * Created: 9/15/2018 3:34:20 PM
 *  Author: 3laa
 */ 


#ifndef TIMERPWM_H_
#define TIMERPWM_H_
//#include <avr/io.h>
//#include <avr/interrupt.h>

void TimerPWM_vint();
void TimerPWM_SetDC(float);
#define PIN 3

#define SET_BIT(reg,bit) reg|=(1<<bit)
#define CLR_BIT(reg,bit) reg&=(~(1<<bit))
#define TOG_BIT(reg,bit) reg^=(1<<bit)
#define READ_BIT_SET(reg,bit) ((reg&(1<<bit))>>bit)




#endif /* TIMERPWM_H_ */