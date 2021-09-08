/*
 * master.c
 *
 * Created: 10/21/2018 5:50:54 PM
 *  Author: 3laa
 */ 


#include "COMMON_CONFIG.h"

int main(void)
{
	/*******	INITILAIZATIONS		***********/
	tot_inti();
	
	/*******************************************/
	
	/*	WRITING CONST PASSWORD ZERO ON GUEST PASSWORD ADDRESS IN EEPROM	*/
	EEPROM_vWrite(stop , GUEST_addrs);
	
	
	Counters c1 ;
	Acess a1 ;
	
	PTR_COUNT = &c1 ;
	PTR_ACESS = &a1 ;
	
	/* POWER FOR INDICACTORS LEDS */
	LED_Power;
	
	/*	MAKING SURE TO STAY IN BLOCK STATE IF USER CUT THE POWER	*/
	
	/*	RAEDING THE ADDRESS OF BLOCK STATE AT EEPROM	
	PTR_COUNT->BlockAdressCounter = EEPROM_vRead(Blocked_count) ;

	if( PTR_COUNT->BlockAdressCounter < FIVE_MINUTES )
	{
		((PTR_COUNT->BlockCount1) =( PTR_COUNT->BlockAdressCounter *TICK)) ;
		((PTR_COUNT->EEPROM_count) = (PTR_COUNT->BlockAdressCounter)) ;
		
		/* BLOCK DISPLAY 
		BlockPower();
		goto Power_OFF ;
	} BLOCK DISPLAY */
	/****************************************************************/
	
	while(1)
	{
		Welcome_Message();
		
		Logout:
		CLR_BIT( LED_PORT , Login_led);	/* LOG IN LED OFF */
		SET_BIT( LED_PORT , Logout_led);	/* LOG OUT LED ON */
		
		/*	START DISPLAY OF CHOOSING ADMIN OR GUEST	*/
		PTR_ACESS->Admin_or_Guest = LCD_StrtDis();
		
		/* CHECK IF THE USER CHOOSED ADMIN OR GUEST */
		if(PTR_ACESS->Admin_or_Guest == Admin){
			
			/* CHECK IF THERE'S AN OLD PASSWORD OR NOT */
			if(Check_NoPass() == PASS){
				Set_Pass();					/* SET YOUR NEW PASSWORD */
				goto acess ;
			}
			
			else if(Check_NoPass() == FAIL){	/* IF THERE'S A PASSWORD	*/
			
			/* ASKING THE PASSWORD FOR THREE ATEMPTS THEN BLOCK IT FOR 15 MINS	*/
			EnterPw:	
			Block(Check_Password_Correct());
			
			/*	WRONG PASSWORD 3 TIMES = BLOCK >> */
			if(EEPROM_vRead(BLock_Addrs) == FAIL){
				/* BLOCKING CODE HERE */
				
				PTR_COUNT->BlockCount1 = 0 ;
				PTR_COUNT->EEPROM_count = 0 ;
				
				
				Power_OFF:
				/* SHUTTING DOWN THE KEYPAD		*/			
				keypad = stop ;
				
				SET_BIT( LED_PORT , Block_led);	/* BLOCKED LED ON */
				CLR_BIT( LED_PORT , Logout_led);	/* LOG OUT LED OFF */
				
				/*	WAIT UNTILL 15 MINS OF BLOCKING ARE OVER	*/
				
				while( (PTR_COUNT->BlockCount1) < FIVE_MIN ){
					
					/* EACH 10 sec INCREMENT THE VALUE IN EEPROM	*/
					
					if((PTR_COUNT->BlockCount1 % TICK) == 1){
						(PTR_COUNT->EEPROM_count) += 1 ;
						EEPROM_vWrite(PTR_COUNT->EEPROM_count , Blocked_count);
					}
				/*	RAEDING THE ADDRESS OF BLOCK STATE AT EEPROM	*/
				PTR_COUNT->BlockAdressCounter = EEPROM_vRead(Blocked_count) ;

				if( PTR_COUNT->BlockAdressCounter < FIVE_MINUTES )
				{
					((PTR_COUNT->BlockCount1) =( PTR_COUNT->BlockAdressCounter *TICK)) ;
					((PTR_COUNT->EEPROM_count) = (PTR_COUNT->BlockAdressCounter)) ;
					
					/* BLOCK DISPLAY */
					BlockPower();
					goto Power_OFF ;
				}
				}
				
				/* AFTER BLOCKING CLEAR THE EEPROM AGAIN	*/
				
				EEPROM_vWrite(CLEAR , Blocked_count) ;
				
				/*************************************************/
				
				CLR_BIT( LED_PORT , Block_led);	/* BLOCKED LED OFF */
				SET_BIT( LED_PORT , Logout_led);	/* LOG OUT LED ON */
				
				/* TURNING THE KEYPAD ON AGAIN		*/
				keypad = keyon ;
				
				goto EnterPw ;
				
			}
			
			else{	/* ACCESSING THE HOUSE AS ADMIN	*/
			
			SET_BIT( LED_PORT , Login_led);	/* LOG IN LED ON */
			CLR_BIT( LED_PORT , Logout_led);	/* LOG OUT LED OFF */
			
			acess:
			/* GETTING FIRST CHOICE FROM USER	*/
			
			PTR_ACESS->FirstAcessRead = Access_Display1();
			if (PTR_ACESS->FirstAcessRead != NEXT){
				
				/*	ROOM1 and ROOM2	*/
				
				switch(PTR_ACESS->FirstAcessRead){
					case ROOM1:
					/*		SENDING ROOM1 TO SLAVE	*/
					SPI_vTransf(ROOM1);
					
					/* DISPLAY OF ACCESSING ROOM 1 */
					PTR_ACESS->AccessHouse = Rooms_Access_Display(ROOM1);
					
					/*	MENU CHOICE		*/
					if(PTR_ACESS->AccessHouse == PASS){
						goto acess ;
					}
					/*	LOGOUT HOUSE CHOICE	*/
					else if(PTR_ACESS->AccessHouse == FAIL){
						SPI_vTransf(LOGOUT_SLAVE);
						_delay_ms(5);	/* WAIT TILL IT FINISHES TRANSMITTING */
						goto Logout ;
					}
					break;
					
					case ROOM2:
					/*		SENDING ROOM2 TO SLAVE		*/
					SPI_vTransf(ROOM2);
					
					/* DISPLAY OF ACCESSING ROOM 2 */
					PTR_ACESS->AccessHouse = Rooms_Access_Display(ROOM2);
					
					/*	MENU CHOICE		*/
					if(PTR_ACESS->AccessHouse == PASS){
						goto acess2 ;
					}
					/*	LOGOUT HOUSE CHOICE	*/
					else if(PTR_ACESS->AccessHouse == FAIL){
						SPI_vTransf(LOGOUT_SLAVE);
						_delay_ms(5);	/* WAIT TILL IT FINISHES TRANSMITTING */
						goto Logout ;
					}
					break;
				}
			}
			
			else if(PTR_ACESS->FirstAcessRead == NEXT){
				/* GETTING SECOND CHOICE FROM USER	*/
				
				PTR_ACESS->SecondAcessRead = Access_Display2();
				
				/*	ROOM3 , AIRCONDITION and T.V	*/

				switch(PTR_ACESS->SecondAcessRead){
					case ROOM3:
					/*		ROOM3 CODE		*/
					
					/*		SENDING ROOM3 TO SLAVE		*/
					SPI_vTransf(ROOM3);
					
					/* DISPLAY OF ACCESSING ROOM 3 */
					PTR_ACESS->AccessHouse = Rooms_Access_Display(ROOM3);
					
					/*	MENU CHOICE		*/
					if(PTR_ACESS->AccessHouse == PASS){
						goto acess ;
					}
					/*	LOGOUT HOUSE CHOICE	*/
					else if(PTR_ACESS->AccessHouse == FAIL){
						SPI_vTransf(LOGOUT_SLAVE);
						_delay_ms(5);	/* WAIT UNTILL IT FINISHES TRANSMITTING	 */
						goto Logout ;
					}
					
					break;
					
					case TV:
					/*		TV CODE		*/
					SPI_vTransf(TV);
					
					/*	ASKING IS TV ON OR OFF	*/
					Tv_menu:							
					PTR_ACESS->AccessTV = TV_ON_OFF();
					
					/*	MENU ACCESS		*/
					if(PTR_ACESS->AccessTV == MENU){
						goto acess ;
					}
					
					/*	OPEN TV		*/
					else if(PTR_ACESS->AccessTV == ON){
						SPI_vTransf(ON);
						
						/*	TV ON DISPLAY	*/
						PTR_ACESS->AccessTV = TV_Access();
						
						/*	BACK TO MENU	*/
						if(PTR_ACESS->AccessTV == PASS){
							goto acess ;
						}
						
						/* LOGOUT FROM THE HOUSE	*/
						else if(PTR_ACESS->AccessTV == FAIL){
							SPI_vTransf(LOGOUT_SLAVE);
							_delay_ms(5);
							goto Logout ;
						}
					}
					
					/*	CLOSE TV	*/
					else if(PTR_ACESS->AccessTV == OFF){
						SPI_vTransf(OFF);
						
						goto Tv_menu ;
					}
					break;
					
					
					case AC:
					/*		AIRCONDITION CODE		*/
					SPI_vTransf(AC);
					
					/*	DISPLAY AIRCONDTION FEATURES	*/
					AirCond_menu:					
					PTR_ACESS->AccessAirCond = AC_On();
					
					/*	MENU ACCESS		*/
					if(PTR_ACESS->AccessAirCond == MENU){
						goto acess ;
					}
					
					/*	OPEN AIR_COND		*/
					else if(PTR_ACESS->AccessAirCond == ON){
						SPI_vTransf(ON);
						
						/*	GETTING TEMPERATURE DEGREE FROM USER	*/
						PTR_ACESS->AirCond_Degree = AC_Degree(AC_TEMP_Degree());
						
						/*	SEND IT TO THE SLAVE	*/
						SPI_vTransf(PTR_ACESS->AirCond_Degree);
						
						/*	ACCESSING AIRCONDITION DISPLAY	*/
						PTR_ACESS->AccessAirCond = AC_Access();
						
						/*	BACK TO MENU	*/
						if(PTR_ACESS->AccessAirCond == PASS){
							SPI_vTransf(MENU);
							goto acess ;
						}
						
						/* LOGOUT FROM THE HOUSE	*/
						else if(PTR_ACESS->AccessAirCond == FAIL){
							SPI_vTransf(LOGOUT_SLAVE);
							_delay_ms(5);
							goto Logout ;
						}
					}
					
					/*	CLOSE AIR_COND	*/
					else if(PTR_ACESS->AccessAirCond == OFF){
						SPI_vTransf(OFF);
						
						goto AirCond_menu ;
					}
					
					break;
				}
			}
			
		}
	}
}






/*************************** GUEST ******************************/





else if(PTR_ACESS->Admin_or_Guest == Guest){
	
	/*	CHECK THE ENTERED PASSWORD	*/
	if(Chk_Guest_Pass() == PASS){
		
		/* ACCESSING THE HOUSE AS GUEST	HAVE ACCESS TO THE ROOMS ONLY	*/
		
		SET_BIT( LED_PORT , Login_led);	/* LOG IN LED ON */
		CLR_BIT( LED_PORT , Logout_led);	/* LOG OUT LED OFF */
		
		acess2:
		/* GETTING FIRST CHOICE FROM USER	*/
		PTR_ACESS->FirstAcessRead = Access_Display1();
		
		/*	ROOM1 and ROOM2	*/
		
		switch(PTR_ACESS->FirstAcessRead){
			case ROOM1:
			/*		SENDING ROOM1 TO SLAVE	*/
			SPI_vTransf(ROOM1);
			
			/* ACCESSING ROOM 1 DISPLAY	*/
			PTR_ACESS->AccessHouse = Rooms_Access_Display(ROOM1);
			
			/*	MENU CHOICE		*/
			if(PTR_ACESS->AccessHouse == PASS){
				goto acess2 ;
			}
			/*	LOGOUT HOUSE CHOICE	*/
			else if(PTR_ACESS->AccessHouse == FAIL){
				SPI_vTransf(LOGOUT_SLAVE);
				_delay_ms(5);	/* WAIT TILL IT FINISHES TRANSMITTING */
				goto Logout ;
			}
			break;
			
			case ROOM2:
			/*		SENDING ROOM2 TO SLAVE		*/
			SPI_vTransf(ROOM2);
			
			/* ACCESSING ROOM 2 DISPLAY	*/
			PTR_ACESS->AccessHouse = Rooms_Access_Display(ROOM2);
			
			/*	MENU CHOICE		*/
			if(PTR_ACESS->AccessHouse == PASS){
				goto acess2 ;
			}
			/*	LOGOUT HOUSE CHOICE	*/
			else if(PTR_ACESS->AccessHouse == FAIL){
				SPI_vTransf(LOGOUT_SLAVE);
				_delay_ms(5);
				goto Logout ;
			}
			break;
			
			case ROOM3:
			
			
			/*		SENDING ROOM3 TO SLAVE		*/
			SPI_vTransf(ROOM3);
			
			/* ACCESSING ROOM 3 DISPLAY	*/
			PTR_ACESS->AccessHouse = Rooms_Access_Display(ROOM3);
			
			/*	MENU CHOICE		*/
			if(PTR_ACESS->AccessHouse == PASS){
				goto acess2 ;
			}
			/*	LOGOUT HOUSE CHOICE	*/
			else if(PTR_ACESS->AccessHouse == FAIL){
				SPI_vTransf(LOGOUT_SLAVE);
				_delay_ms(5);
				goto Logout ;
			}
			
			break;
		}
	}
	
	/* IF PASSWORD WRONG ( NOT ZERO ) JUST LOGOUT TO GUEST OR ADMIN CHOICE */
	else {
		goto Logout ;
	}
}
    }
}

/* NOTE THAT TIMER0 TICK = 10ms		*/
ISR(TIMER0_COMP_vect){
	PTR_COUNT ->keypad_count += 1;
	PTR_COUNT->pw_count += 1;
	
}

/*	NOTE THAT TIMER1 TICK = 100ms	*/
ISR(TIMER1_COMPA_vect){
	PTR_COUNT->BlockCount1 +=1 ;
}


ISR(SPI_STC_vect){
	SET_BIT(PORTB , ss);
}