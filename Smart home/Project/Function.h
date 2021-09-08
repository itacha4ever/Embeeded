/*
 * Function.h
 *
 * Created: 10/2/2018 4:28:55 PM
 *  Author: 3laa
 */ 


#ifndef FUNCTION_H_
#define FUNCTION_H_

void Welcome_Message();
void Choose_Mod();
void Signup_Pass();
void log_in_Admin();
void log_in_Guest();
void Change_Pass();
unsigned char Enter_pass (unsigned char*);
unsigned char Compare_Pass (unsigned char*,unsigned char*,unsigned char*,unsigned char*);
unsigned char chk_pass (unsigned char pass_length,unsigned char* password);
void Try_agin();
unsigned char Enter_PinCode();
void tot_inti();


#define HIGH 1
#define LOW 0

#define Admin '1'
#define Guest '2'

#define  admin_addrs 0x10
#define block 0x05
#define NPass 0xFF
#define No_trys_add 30

static char str[100] = {0};
	
#define  SEC1 60
#define  SEC2 600

#define LED_Power DDRC = 0xFF
#define LED_PORT PORTC
#define Logout_led 4
#define Login_led 5
#define Block_led 6

#define ATR_Port PORTC
#define ROOM1 0
#define ROOM2 1
#define ROOM3 2
#define TV 3
#define AC 4



















#endif /* FUNCTION_H_ */