/*
 * Function.h
 *
 * Created: 10/21/2018 5:53:14 PM
 *  Author: 3laa
 */ 


#ifndef FUNCTION_H_
#define FUNCTION_H_
#include "COMMON_CONFIG.h"

void Welcome_Message();
char * LCD_PassDis1();
char * LCD_PassDis2();
char LCD_StrtDis();
char TryAgain(char);
char Check_Password_Correct ();
void BlockPower();
void Block(char);
char Check_NoPass();
void Set_Pass();
char Access_Display1();
char Access_Display2();
char Rooms_Access_Display(char);
void TVM();
char TV_ON_OFF();
char TV_Access();
void AC_disp();
char AC_Access();
char AC_On();
void AC_TEMP_SET();
char * AC_TEMP_Degree(void);
char AC_Degree(char *);
char Chk_Guest_Pass (void);
char Guest_Pass (char *);
char Guest_Access_Display (void);
void tot_inti();
void Set_Pass1();
char Check_Password_Correct2 ();




/***********************************************************************/
/*slave functions */

void vTv_ON (void);

void vTv_OFF (void);

void vAirCond_ON (char);

void vAirCond_OFF (void);




#endif /* FUNCTION_H_ */