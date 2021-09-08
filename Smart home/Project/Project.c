/*
 * Project.c
 *
 * Created: 10/2/2018 4:38:08 PM
 *  Author: 3laa
 */ 


#include <avr/io.h>
#include "Function.h"
#include "COMMON_CONFIG.h"

int main(void)
{ 
	LED_Power;
	tot_inti();
	
	
	
    while(1)
    {
		//Check firstly if the lock is permanently locked or not
		if (EEPROM_vRead(block)==NPass)
		{
			unsigned char chack = 0;
			do 
			{
				chack = Enter_PinCode();
			} while (!chack);
			
				LCD_vCLEARS();
				LCD_print("Successful");
				EEPROM_vWrite(LOW,block);
				EEPROM_vWrite(LOW,No_trys_add);
				_delay_ms(1000);
			
		}
		
       //Print Hello message on screen
      Welcome_Message();
	 	  
	  Choose_Mod();
	  	  unsigned char key ;
			key = KEYPAD_u8SCAN();
	   while (key == 0xff)
	   {
		   key = KEYPAD_u8SCAN();
		}
	  
	  CLR_BIT(LED_PORT,Login_led);
	  CLR_BIT(LED_PORT,Block_led);
	  SET_BIT(LED_PORT,Logout_led);
	  
	  
	  if (key == Admin)
	  {
		  LCD_print("hi");
		  CLR_BIT(LED_PORT,Logout_led);
		  //Signup_Pass();
		  log_in_Admin();
	  }
	  else if (key == Guest)
	  {
		  Signup_Pass();
		  log_in_Guest();
	  }
	  key = KEYPAD_u8SCAN();
	  
	 /*do 
	 {
		 
		 Choose_Mod();
		 choice = KEYPAD_u8SCAN();
	 } while (choice != Admin && choice != Guest);
	 
	 
	 CLR_BIT(LED_PORT,Login_led);
	 CLR_BIT(LED_PORT,Block_led);
	 SET_BIT(LED_PORT,Logout_led);
	 
		if (choice = Admin)
		 {
			 Signup_Pass();
			//log_in_Admin();
		}
		/*else if (choice = Guest)
		 {
			 Signup_Pass();
			 log_in_Guest();
		 }*/
		

 }

}