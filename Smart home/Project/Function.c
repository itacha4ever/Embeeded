/*
 * Function.c
 *
 * Created: 10/2/2018 4:28:46 PM
 *  Author: 3laa
 */ 
#include "COMMON_CONFIG.h"
#define  Enter_pass KEYPAD_u8SCAN();
//This function for total initiates
void tot_inti()
{
	KEYPAD_VINIT();
	//SPI_vINTMASTRE();
	//SPI_vINTSlave();
	LCD_vint();
	//ADC_vint();
	EEPROM_vWrite(LOW,No_trys_add);
	
	
}

//This function prints a welcome message to the user
void Welcome_Message()
{
	LCD_print("Welcome");
	_delay_ms(50);

}

//This function lists the possible choices for user
void Choose_Mod()
{
	LCD_vCLEARS();
	LCD_print("(1)Admin");
	LCD_LD(1,2);
	LCD_print("(2)Guest");
	
	
	}
	
//This function asks the user to enter his desired password two times. If the passwords are
//matched, the password will be saved. Else, It won't and the user should try again.
void Signup_Pass()
{
	unsigned char Desired_Pass1 [10] = {0};
	unsigned char Desired_Pass2 [10] = {0};
	unsigned char Pass_length1 =0;
	unsigned char Pass_length2 =0;
	LCD_vCLEARS();
	LCD_LD(1,1);
	LCD_print("New Password:");
	LCD_LD(1,2);
	Pass_length1 = Enter_pass(Desired_Pass1[10]);
		LCD_print("12h23");
	LCD_vCLEARS();
	LCD_LD(1,1);
	LCD_print("Re-enter Password:");
	LCD_LD(1,2);
	Pass_length2 = Enter_pass(Desired_Pass2[10]);
	
		if (Compare_Pass(Desired_Pass1[10],Pass_length1,Desired_Pass2[10],Pass_length2))
		{
			unsigned char x=0;
			cli();
			EEPROM_vWrite(Desired_Pass1[0],admin_addrs);
			
			for(x=0;x<Pass_length1;x++)
			{
				EEPROM_vWrite(Desired_Pass1,x+1);
			}
			sei();
			
			LCD_vCLEARS();
			LCD_print("Your password is");
			LCD_LD(1,2);
			LCD_print("saved");
			_delay_ms(1000);
		}
		else
		{
			LCD_vCLEARS();
			LCD_LD(1,1);
			LCD_print("Failed operation");
			LCD_LD(1,2);
			LCD_print("Plz,Try again");
			_delay_ms(1000);
			Signup_Pass();
			
		}
	
}

//This function tells the user to enter the saved password and then checks if it is right or not
//using check_password function. And then make a decision upon the results for admin
void log_in_Admin()
{
	unsigned char InPass [10] ={0};
	unsigned char Pass_Length =0;
	LCD_vCLEARS();
	LCD_print("Enter Password");
	LCD_LD(1,2);
	Pass_Length = Enter_pass(InPass);
	if (chk_pass(Pass_Length,InPass))
	{
	
		SET_BIT(LED_PORT,Login_led);
		
	}
	
	else
	{
		Try_agin();
	}
}
//This function tells the user to enter the saved password and then checks if it is right or not
//using check_password function. And then make a decision upon the results for guest
void log_in_Guest()
{
unsigned char InPass [10] ={0};
unsigned char Pass_Length =0;
LCD_vCLEARS();
LCD_print("Enter Password");
Pass_Length = Enter_pass(InPass);
	if (chk_pass(Pass_Length,InPass))
	{
	
		SET_BIT(LED_PORT,Login_led);
	
	}

	else
	{
		Try_agin();
	}
}

//This function changes the password of user. It firstly asks to enter his old password and if it is right, It
//will ask you to enter your new password two times
void Change_Pass()
{
	unsigned char Old_Pass[10] ={0};
	unsigned char Pass_Length =0;
	
	LCD_vCLEARS();
	LCD_print("Enter Old Password");
	Pass_Length = Enter_pass(Old_Pass);
	
	if (chk_pass(Pass_Length,Old_Pass))
	{
		Signup_Pass();
	} 
	else
	{
		Change_Pass();
	}
	
}


//This function takes the password from the user
/*unsigned char Enter_pass (unsigned char*password)
{
	int count =0;
	unsigned char Keys =0;
	
	
	for (count=0; count <= 10;)
	{
		Keys = KEYPAD_u8SCAN();
		
		if (Keys == '+')
		{
			break;
		}
		else if ((Keys =='-') && (count>0))
		{
			LCD_vsenddata(' ');
			count--;
		}
		else if ((Keys =='-') && (count>0))
		{
			count =0;
		}
		else if (count !=10)
		{
			password[count++] = Keys;
			LCD_vsenddata('-');
		}
	}
	
	return count;
}*/


//This function compares password_1 and password_2 and returns '1' if they are matched and '0'
//if matching didn't occur.
unsigned char Compare_Pass (unsigned char*password1,unsigned char*password2,unsigned char*pass_length1,unsigned char*pass_length2)
{
	unsigned char x = 0;		//Just a counter variable
	if(pass_length1 != pass_length2)
	{
		
		LCD_vCLEARS();
		LCD_LD(1,1);
		LCD_print("! = ");
		_delay_ms(1000);
		return LOW;
	}
	
	else
	{
		for(x = 0; x < pass_length1; x++)
		{
			if(password1[x] != password2[x])
			{
				LCD_vCLEARS();
				LCD_LD(1,1);
				LCD_print("password1 = ");
				LCD_print(itoa((int)password1[x],(char*)str,10));
				LCD_LD(1,2);
				LCD_print("password2 = ");
				LCD_print(itoa((int)password2[x],(char*)str,10));
				_delay_ms(500);
				return LOW;
			}
			else
			{
			
				LCD_vCLEARS();
				LCD_LD(1,1);
				LCD_print("pass1 = ");
				LCD_print(itoa((int)password1[x],str,10));
				LCD_LD(1,2);
				LCD_print("pass2 = ");
				LCD_print(itoa((int)password2[x],str,10));
				_delay_ms(2000);

				continue;			//No need for it, just to make the code readable
			}
		}
		return HIGH;
	}
	
}


//This function compare the entered password with the one saved in the EEPROM. If matching occurs,
//it would return '1'. Else, It would return '0'
unsigned char chk_pass (unsigned char pass_length,unsigned char* password)
{	
	unsigned char x=0;
	
	if (EEPROM_vRead(admin_addrs)!= pass_length)
	{
		return LOW;
	}
	else
	{
		for (x=0;x<pass_length;x++)
		{
			if (password[x] != EEPROM_vRead(admin_addrs))
			{
				LCD_vCLEARS();
				LCD_print("stop");
				_delay_ms(1000);
				return LOW;
			}
		}
		return HIGH;
	}
}


//This function TRY again
void Try_agin()
{
	static unsigned char no_tril =0;
	no_tril = EEPROM_vRead(No_trys_add);
	EEPROM_vWrite(No_trys_add,++no_tril);
	
	if (EEPROM_vRead(No_trys_add) == 4)
	{
			unsigned char x =0;
			LCD_vCLEARS();
			LCD_LD(1,1);
			LCD_print("wrong pass");
			LCD_LD(1,2);
			LCD_print("try agin in");
			for(x = SEC1; x > 0; x--)
		{
			LCD_LD(14,2);
			itoa((int)x, str, 10);
			LCD_print(str);
			_delay_ms(100);
		}
			Choose_Mod();
	}
	else if (EEPROM_vRead(No_trys_add)>=10)
	{
		EEPROM_vWrite(NPass,block);
		unsigned char pin_chk =0;
		
		do 
		{
			pin_chk = Enter_PinCode();
					
		} 
			while (!pin_chk);
			LCD_vCLEARS();
			LCD_print("Successful operation");
			EEPROM_vWrite(LOW,block);
			EEPROM_vWrite(LOW,No_trys_add);
			_delay_ms(1000);
			Signup_Pass();
	}
	else
	{
		LCD_vCLEARS();
		LCD_LD(1,1);
		LCD_print("Wrong");
		LCD_LD(1,2);
		LCD_print("try again");
		_delay_ms(1000);
		Choose_Mod();
			
	}
	
	
}


//This function for block  or checks if the user enters the pin code correctly or not 
unsigned char Enter_PinCode()
{
	
	
	/*if(;;)
	{
		
	LCD_vCLEARS();
	LCD_print("LOOKED");
	LCD_LD(1,2);
	LCD_print("wait");
	_delay_ms(1000);

		for(x = SEC2; x > 0; x--)
		{
			LCD_LD(14,2);
			itoa((int)x, str, 10);
			LCD_print(str);
			_delay_ms(100);
		}
		log_in();
	}*/	
	
	/*unsigned char x =0;
	unsigned char PinCode[10] ={0};
	unsigned char Pass_length =0;
		LCD_vCLEARS();
		LCD_print("Enter pin code: ");
		LCD_LD(1,2);
		Pass_length = Enter_pass(PinCode);
		for(x = 0; x < 10; x++)
		PinCode[x] = 4;

		if(Pass_length != 10)		//pin code is 10 numbers + the ending '*' which acts as an enter.
		{
			LCD_vCLEARS();
			LCD_print(itoa((char)Pass_length,str,10));
			_delay_ms(1000);
			return LOW;
		}
		else
		{
			for(x = 0; x < 10; x++)
			{
			if(PinCode[x] != EEPROM_vRead(x+27))		//Password is stored in EEPROM from location 27 to 37
			{
			return LOW;
			}
		}
	return HIGH ;
	} */
}


//This function for Admin/Guest list 

