/*
 * Function.c
 *
 * Created: 10/21/2018 5:53:03 PM
 *  Author: 3laa
 */ 



#include "COMMON_CONFIG.h"

void tot_inti()
{
	KEYPAD_VINIT();
	SPI_vINTMASTRE();
	//SPI_vINTSlave();
	LCD_vint();
	ADC_vint();
	TIMER_vInt();
	
	
}
//This function prints a welcome message to the user
void Welcome_Message()
{
	LCD_vSDD("Welcome");
	LCD_vCLEARS();
	
}


char LCD_StrtDis()
{
	char arr1 = "0 : Guest Mode" ;
	char arr2 = "1 : Admin Mode" ;
	char *ptr1 = arr1 ;
	char *ptr2 = arr2 ;
	char key ;
	
	
	LCD_vSendCmd(0x01);
	LCD_vSDD(ptr1);
	LCD_vMOVECur(2,1);
	LCD_vSDD(ptr2);
	
	/* take from keypad 0 or 1 */
	/* Wait until a key pressed */
	while(KEYPAD_u8SCAN() == NoScan);
	key = KEYPAD_u8SCAN();
	
	PTR_COUNT->pw_count = 0 ;
	while( (PTR_COUNT->pw_count) < 250 );
	return key ;
}


char * LCD_PassDis1()
{
	char arr0 = "Enter Password" ;
	char *ptr0 = arr0 ;
	char pass[4] ;
	char *Pw_ptr = pass ;
	char x;
	
	
	LCD_vSendCmd(0x01);
	LCD_vSDD(ptr0);
	LCD_vMOVECur(2,1);
	
	for(x = 0 ; x < 4 ; ++x)
	{	
		/* WAIT UNTILL A KEY TO BE PRESSED */
		while(KEYPAD_u8SCAN() == NoScan);
		
		/* SEND THE PRESSED KEY TO AN ARRAY OF 4 CHAR */
		pass[x] =  KEYPAD_u8SCAN();
		
		/* SEND THE PRESSED KEY TO THE LCD */
		LCD_vsenddata( pass[x] );
		
		if(x != 3){
			/*	DELAY OF * SECURITY SYMPOL	*/
			PTR_COUNT->pw_count = 0 ;
			while( (PTR_COUNT->pw_count) < 500 );
		}
		
		LCD_vMOVECur(2, x+1);
		LCD_vsenddata('*');
	
	}
	/*  WAIT 250ms AFTER I SENDD THE LAST *	*/
	PTR_COUNT->pw_count = 0 ;
	while( (PTR_COUNT->pw_count) < 250 );
	
	return Pw_ptr ;
}


char * LCD_PassDis2()
{
	char pass[4] ;
	char *Pw_ptr = pass ;
	char x;
	
	
	LCD_vMOVECur(2,1);
	
	for(x = 0 ; x < 4 ; ++x)
	{
		while( KEYPAD_u8SCAN() == NoScan);
		
		pass[x] =  KEYPAD_u8SCAN(); ;
		LCD_vsenddata( pass[x] );
		
		if(x != 3)
		{
			/*	DELAY OF * SECURITY SYMPOL	*/
			PTR_COUNT->pw_count = 0 ;
			while( (PTR_COUNT->pw_count) < 500 );
		}
		
		LCD_vMOVECur(2 , x+1);
		LCD_vsenddata('*');
	}
	return Pw_ptr ;
}


//This function for Try again

char TryAgain(char Blocked)
{
	char arr1[] = "Failed Once";
	char arr2[] = "Failed Twice";
	char arr3[] = "BLOCKED";
	char *BLK_ptr ;
	
	switch(Blocked)
	{
		case 1:
		BLK_ptr = arr1;
		LCD_vSendCmd(0x01);
		LCD_vSDD(BLK_ptr);
		return Password_inFun(LCD_PassDis2());
		break;
		
		case 2:
		BLK_ptr = arr2 ;
		LCD_vSendCmd(0x01);
		LCD_vSDD(BLK_ptr);
		return Password_inFun(LCD_PassDis2());
		break;
		
		case 3:
		BLK_ptr = arr3 ;
		LCD_vSendCmd(0x01);
		LCD_vSDD(BLK_ptr);
		return stop;
		break;
	}
}

//This function for if the password correct or not
char Check_Password_Correct ()
{
	char BlockTime = 0 ;
	char Pass ;
	Pass = Password_inFun(LCD_PassDis1());

	again:
	
	if(Pass == EEPROM_vRead(admin_addrs))
	{
		return HIGH;
	}
	else
	{
		++BlockTime ;
		if(BlockTime < 3)
		{
		
			
			/*	WAITING FOR NEXT SCREEN	*/
			PTR_COUNT->keypad_count = 0;
			while(PTR_COUNT->keypad_count < Q_SEC);
			
			Pass = TryAgain(BlockTime);
			
			/*	THIS DELAY TO NOT INTERFERE WITH THE ACCESS FUNCTION	*/
			PTR_COUNT->keypad_count = 0;
			while(PTR_COUNT->keypad_count < Q_SEC);
			
		
			
			goto again;
		}
		else
		{
			Pass = TryAgain(BlockTime);
			/*	BLOCKED	*/
			return LOW ;
		}
	}
}


/* BLOCKING DISPLAY	*/
void BlockPower()
{
	char arr0 [] = "BLOCKED" ;
	char *ptr = arr0 ;
	LCD_vSDD(ptr);
}

/* RETURN BLOCK PASS OR FAIL BY CHECKING THE BLOCK ADDRESS IN EEPROM	*/
void Block(char block)
{
	if(block == LOW){
		EEPROM_vWrite(LOW , BLock_Addrs);
	}
	else if(block == HIGH){
		EEPROM_vWrite(HIGH , BLock_Addrs);
	}
}


/* CHECK IF NO PASSWORD  IN EEPROM	*/

char Check_NoPass()
{
	if(EEPROM_vRead(admin_addrs) == CLEAR)
	{
		return HIGH ;
	}
	else
	{
		return LOW ;
	}
}

/* DISPLAY SET PASSWORD , TAKE IT AND SAVE IT IN EEPROM */

void Set_Pass()
{
	char arr0[] = "Set Password" ;
	char *ptr0 = arr0 ;
	char pass[4] ;
	char *Pw_ptr = pass ;
	char x;

	
	LCD_vSendCmd(0x01);
	LCD_vSDD(ptr0);
	LCD_vMOVECur(2,1);
	
	for(x = 0 ; x < 4 ; ++x){
		while( KEYPAD_u8SCAN() == NoScan);
		
		pass[x] =  KEYPAD_u8SCAN(); ;
		LCD_vsenddata( pass[x] );
		
		if(x != 3){
			
			/*	THIS DELAY TO NOT INTERFERE WITH THE ACCESS FUNCTION	*/
			PTR_COUNT->keypad_count = 0;
			while(PTR_COUNT->keypad_count < Q_SEC);
		}
		
		LCD_vMOVECur(2 , x+1);
		LCD_vsenddata('*');
	}
	/*	THIS DELAY TO NOT INTERFERE WITH THE ACCESS FUNCTION	*/
	PTR_COUNT->keypad_count = 0;
	while(PTR_COUNT->keypad_count < HALF_SEC);
	
	//_delay_ms(250);	/* DELAY	*/
	EEPROM_vWrite(Password_inFun(Pw_ptr) , admin_addrs);
}


/*	DISPLAY FIRST ACCESS TO ROOM 1 AND ROOM 2	*/

char Access_Display1()
{
	char arr0[] = "(0)Room1" ;
	char arr1[] = "(1)Room2";
	char arr2[] = "(-)Next";
	
	char *ptr0 = arr0 ;
	char *ptr1 = arr1 ;
	char *ptr2 = arr2 ;
	
	char key ;
	
	/* Just the shape of Displaying	*/
	LCD_vSendCmd(0x01);
	LCD_vSDD(ptr0);
	LCD_vMOVECur(1,10);
	
	LCD_vSDD(ptr1);
	LCD_vMOVECur(2,1);
	
	LCD_vSDD(ptr2);
	LCD_vMOVECur(2,8);
	
	/* take from keypad 0 or 1 or 2 */
	/* Wait until a key pressed */
	while( KEYPAD_u8SCAN() == NoScan);	
	key =  KEYPAD_u8SCAN();
	
	/*	THIS DELAY TO NOT INTERFERE WITH THE ACCESS FUNCTION	*/
	PTR_COUNT->keypad_count = 0;
	while(PTR_COUNT->keypad_count < Q_SEC);
	

	return key ;
}


/* DISPLAY SECOND ACCESS TO ROOM 3 , TV AND AIRCONDTION	*/

char Access_Display2()
{
	char arr0[] = "(2)Room3" ;
	char arr1[] = "(3)TV";
	char arr2[] = "(4)AirCondtion";
	
	char *ptr0 = arr0 ;
	char *ptr1 = arr1 ;
	char *ptr2 = arr2 ;
	
	char key ;

	/* Just the shape of Displaying	*/
	
	LCD_vSendCmd(0x01);
	LCD_vSDD(ptr0);
	LCD_vMOVECur(1,10);
	
	LCD_vSDD(ptr1);
	LCD_vMOVECur(2,1);
	
	LCD_vSDD(ptr2);
	LCD_vMOVECur(2,14);
	
	/* take from keypad 0 or 1 or 2 */
	/* Wait untill a key pressed */
	while(KEYPAD_u8SCAN() == NoScan);	
	key = KEYPAD_u8SCAN();
	
	/*	THIS DELAY TO NOT INTERFERE WITH THE ACCESS FUNCTION	*/
	PTR_COUNT->keypad_count = 0;
	while(PTR_COUNT->keypad_count < Q_SEC);
	
	return key ;
}


/* DISPLAYING WHICH ROOM USER ACCESSING AT THE MOMENT */

char Rooms_Access_Display(char RoomNumber)
{
	char arr0[] = "ROOM 1" ;
	char arr1[] = "(=)Menu";
	char arr2[] = "(*)Logout";
	char arr3[] = "ROOM 2" ;
	char arr4[] = "ROOM 3" ;
	
	short *ptr0  ;
	char *ptr1 = arr1 ;
	char *ptr2 = arr2 ;
	
	char key;
	
	/* Just the shape of Displaying	*/
	switch(RoomNumber)
	{
		case ROOM1 :
		ptr0 = arr0 ;
		break ;
		
		case ROOM2 :
		ptr0 = arr3 ;
		break ;
		
		case ROOM3 :
		ptr0 = arr4 ;
		break ;
	}
	
	LCD_vSendCmd(0x01);
	LCD_vMOVECur(1,6);
	LCD_vSDD(ptr0);
	LCD_vMOVECur(2,1);
	
	LCD_vSDD(ptr1);
	LCD_vMOVECur(2,8);
	
	LCD_vSDD(ptr2);
	LCD_vMOVECur(2,16);
	
	/* take from keypad 0 or 1 */
	/* Wait until a key pressed */
	while(KEYPAD_u8SCAN() == NoScan);	
	key =KEYPAD_u8SCAN();
	
	/*	THIS DELAY TO NOT INTERFERE WITH THE ACCESS FUNCTION	*/
	PTR_COUNT->keypad_count = 0;
	while(PTR_COUNT->keypad_count < Q_SEC);
	
	//_delay_ms(250);
	if(key == MENU)
	{
		return HIGH ;
	}
	else if(key == LOUT)
	{
		return LOW ;
	}
}


/* DISPLAY OF TV ON OR OFF CHOICES	*/

void TVM()
{
	char arr0[] = "1:TV ON";
	char arr1[] = "2:TV OFF";
	char arr2[] = "0:Menu";
	char *ptr0 = arr0 ;
	char *ptr1 = arr1 ;
	char *ptr2 = arr2 ;
	
	
	
	LCD_vSendCmd(0x01);
	LCD_vSDD(ptr2);
	LCD_vMOVECur(1,2);
	
	LCD_vSDD(ptr0);
	LCD_vMOVECur(2 ,9);

	LCD_vSDD(ptr1);
	LCD_vMOVECur(1,8);
	
}


/* ASKING IF USER WANTS TV ON OR OFF	*/

char TV_ON_OFF(){
	TVM();
	char key ;
	
	
	/* take from keypad 0 or 1 */
	/* Wait until a key pressed */
	while(KEYPAD_u8SCAN() == NoScan);	
	key = KEYPAD_u8SCAN();
	
	/*	THIS DELAY TO NOT INTERFERE WITH THE ACCESS FUNCTION	*/
	PTR_COUNT->keypad_count = 0;
	while(PTR_COUNT->keypad_count < Q_SEC);
	

	if(key == K_ON){
		return ON ;
	}
	else if(key == K_OFF){
		return OFF ;
	}
	else if(key == MENU){
		return MENU ;
	}
}

/* DISPLAY OF TV ACCESSING SCREEN	*/

char TV_Access()
{
	char arr0[] = "TV ON";
	char arr1[] = "(=)Menu";
	char arr2[] = "(*)Logout" ;
	char *ptr0 = arr0 ;
	char *ptr1 = arr1 ;
	char *ptr2 = arr2 ;
	char key ;

	LCD_vSendCmd(0x01);
	LCD_vMOVECur(6 , 1);
	LCD_vSDD(ptr0);
	LCD_vMOVECur(2,1);
	
	LCD_vSDD(ptr1);
	LCD_vMOVECur(2,8);
	
	LCD_vSDD(ptr2);
	LCD_vMOVECur(2,16);
	
	/* take from keypad 0 or 1 */
	/* Wait untill a key pressed */
	while(KEYPAD_u8SCAN() == NoScan);	
	key = KEYPAD_u8SCAN();
	
	/*	THIS DELAY TO NOT INTERFERE WITH THE ACCESS FUNCTION	*/
	PTR_COUNT->keypad_count = 0;
	while(PTR_COUNT->keypad_count < Q_SEC);
	
	
	if(key == MENU)
	{
		return HIGH ;
	}
	else if(key == LOUT)
	{
		return LOW ;
	}
}

/* DISPLAY OF AIRCONDTION CHOICES FOR USER TO USE	*/

void AC_disp()
{
	char arr0[] = "(1)AC ON";
	char arr1[] = "(2)AC OFF";
	char arr2[] = "(=)Menu";
	char *ptr0 = arr0 ;
	char *ptr1 = arr1 ;
	char *ptr2 = arr2 ;
	
	
	LCD_vSendCmd(0x01);
	LCD_vSDD(ptr2);
	LCD_vMOVECur(2 , 1);
	
	LCD_vSDD(ptr0);
	LCD_vMOVECur(2 , 9);

	LCD_vSDD(ptr1);
	LCD_vMOVECur(1 , 8);
	
}

/* CHOOSING WHICH FEATURE IN AIRCONDTION YOU WANNA USE	*/

char AC_On()
{
	AC_disp();
	char key ;

	
	/* take from keypad 0 or 1 */
	/* Wait until a key pressed */
	while(KEYPAD_u8SCAN() == NoScan);	
	key = KEYPAD_u8SCAN();
	
	/*	THIS DELAY TO NOT INTERFERE WITH THE ACCESS FUNCTION	*/
	PTR_COUNT->keypad_count = 0;
	while(PTR_COUNT->keypad_count < Q_SEC);
	
	//_delay_ms(250);
	if(key == K_ON)
	{
		return ON ;
	}
	else if(key == K_OFF)
	{
		return OFF ;
	}
	else if(key == MENU)
	{
		return MENU ;
	}
}

char AC_Access()
{
	char arr0[] = "AC ON";
	char arr1[] = "(=)Menu";
	char arr2[] = "(*)Logout" ;
	char *ptr0 = arr0 ;
	char *ptr1 = arr1 ;
	char *ptr2 = arr2 ;
	char key;
	
	LCD_vSendCmd(0x01);
	LCD_vMOVECur(1,6);
	LCD_vSDD(ptr0);
	LCD_vMOVECur(2,1);
	
	LCD_vSDD(ptr1);
	LCD_vMOVECur(2,8);
	
	LCD_vSDD(ptr2);
	LCD_vMOVECur(2,16);
	
	/* take from keypad 0 or 1 */
	while(KEYPAD_u8SCAN() == NoScan);	/* Wait untill a key pressed */
	key= KEYPAD_u8SCAN();
	
	/*	THIS DELAY TO NOT INTERFERE WITH THE ACCESS FUNCTION	*/
	PTR_COUNT->keypad_count = 0;
	while(PTR_COUNT->keypad_count < Q_SEC);
	

	if(key == MENU){
		return HIGH ;
	}
	else if(key == LOUT){
		return LOW ;
	}
}


/* SETTING TEMPERATURE OF AIRCONDTION	*/
void AC_TEMP_SET()
{
	char arr0[] = "Enter Degree";
	char *ptr0 = arr0 ;
	
	
	LCD_vSendCmd(0x01);
	LCD_vSDD(ptr0);
	LCD_vMOVECur(2,1);
	
}

/* GETTING DESIRED TEMPERATURE FROM USER	*/

char * AC_TEMP_Degree(void)
{
	AC_TEMP_SET();
	
	char temp[2] ;
	char *degree_ptr = temp ;
	char x;
	
	
	for(x = 0 ; x < 2 ; ++x){
		while(KEYPAD_u8SCAN() == NoScan);
		
		temp[x] = KEYPAD_u8SCAN() ;
		LCD_vsenddata( temp[x] );
		
		PTR_COUNT->keypad_count = 0;
		while(PTR_COUNT->keypad_count < Q_SEC);
	}
	while(KEYPAD_u8SCAN() != ENTER);
	
	PTR_COUNT->keypad_count = 0;
	while(PTR_COUNT->keypad_count < Q_SEC);

	return degree_ptr ;
}

/* CONVERT TEMPERATURE SO THAT ADC CAN HANDLE IT	*/

char AC_Degree(char *degree_ptr)
{
	char Degree ;
	
	Degree = ( ((*(degree_ptr + 0)) - ('0') ) * 10 ) + ( (*(degree_ptr+1)) - ('0') ) ;
	
	return Degree ;
}


/* GETTING GUEST PASSWORD	*/
char Guest_Pass (char * pw_ptr)
{
	char pass = 0 ;
	pass = ( (*(pw_ptr+0)) - ('0') ) + ( (*(pw_ptr+1)) - ('0') ) + ( (*(pw_ptr+2)) - ('0') ) + ( (*(pw_ptr+3)) - ('0') ) ;
	
	return pass ;
}


/* CHECK GUEST PASSWORD	*/

char Chk_Guest_Pass (void)
{
	char Pass = Guest_Pass(LCD_PassDis1());
	
	if(Pass == EEPROM_vRead(GUEST_addrs))
	{
		return HIGH ;
	}
	else
	{
		return LOW ;
	}
}


/* DISPLAY FIRST ACCESS OF ROOM 1 , 2 AND 3	 .. THE ONLY ACCESSABLE FEATURES FOR GUEST	*/

char Guest_Access_Display (void)
{
	char arr0[] = "(0)Room1" ;
	char arr1[] = "(1)Room2";
	char arr2[] = "(2)Room3";
	
	char *ptr0 = arr0 ;
	char *ptr1 = arr1 ;
	char *ptr2 = arr2 ;
	
	char key ;
	
	/* Just the shape of Displaying	*/
	
	LCD_vSendCmd(0x01);
	LCD_vSDD(ptr0);
	LCD_vMOVECur(1, 10);
	
	LCD_vSDD(ptr1);
	LCD_vMOVECur(2,1);
	
	LCD_vSDD(ptr2);
	LCD_vMOVECur(2,8);
	
	/* take from keypad 0 or 1 or 2 */
	/* Wait untill a key pressed */
	while(KEYPAD_u8SCAN() == NoScan);
	key = KEYPAD_u8SCAN();
	
	/*	THIS DELAY TO NOT INTERFERE WITH THE ACCESS FUNCTION	*/
	PTR_COUNT->keypad_count = 0;
	while(PTR_COUNT->keypad_count < Q_SEC);
	
	//_delay_ms(250);
	return key ;
}


