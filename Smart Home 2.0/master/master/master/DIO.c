


 /*
 * DIO.c
 *
 * Created: 8/3/2018 3:53:21 PM
 *  Author: 3laa
 
 */ 
 
 
// #include <avr/io.h>
// #include "DIO.h"
 #include "COMMON_CONFIG.h"
 
	void DIO_vsetpindirection(char portname ,char pinnum,char dir)
{
		 switch (portname)
		 {
			 case 'A':
			 case 'a':
			 
					if (dir==1)
					{
						SET_BIT(DDRA,pinnum);
						// DDRA |= (1<<pinnum);
					}
					
					else
					{
						CLR_BIT(DDRA,pinnum);
						//DDRA &=(~(1<<pinnum));
					} 
					
					break;
			
			case 'B':
			case 'b':
			
					if (dir==1)
					{
						SET_BIT(DDRB,pinnum);	
						//DDRB |= (1<<pinnum);
					}
					
					else
					{
						 CLR_BIT(DDRB,pinnum);
						 //DDRB &=(~(1<<pinnum));
					}
					
					break;
					
		 	case 'C':
			case 'c':
			
					if (dir==1)
					{
						SET_BIT(DDRC,pinnum);
						//DDRC |= (1<<pinnum);
					}
			
					else
					{
						CLR_BIT(DDRC,pinnum);
						//DDRC &=(~(1<<pinnum));
					}
					
					break;	
					 
			case 'D':
			case 'd':
			
					if (dir==1)
					{
						SET_BIT(DDRD,pinnum);
						//DDRD |= (1<<pinnum);
					}
			
					else
					{
						CLR_BIT(DDRD,pinnum);
						//DDRD &=(~(1<<pinnum));
					}
					
					break;
			 
		}			 
} 
		
	void DIO_vWrite(char portname ,char pinnum,char res)
{
		switch (portname)
	{
			case 'A':
			case 'a': 
				if (res==1)
			{
				SET_BIT(PORTA,pinnum);
				//PORTA |= (1<<pinnum);
			}
				
			else
			{
				CLR_BIT(PORTA,pinnum);
				//PORTA &=(~(1<<pinnum));
			}
			break;
			
		case 'B':
		case 'b':
			if (res==1)
			{
				SET_BIT(PORTB,pinnum);
				//PORTB |= (1<<pinnum);
			}
			
			else
			{
				CLR_BIT(PORTB,pinnum);
				//PORTB &=(~(1<<pinnum));
			}
			break;
		
		case 'C':
		case 'c':
			if (res==1)
			{
				SET_BIT(PORTC,pinnum);
				//PORTC |= (1<<pinnum);
			}
		
			else
			{
				CLR_BIT(PORTC,pinnum);
				//PORTC &=(~(1<<pinnum));
			}
			break;
			
		case 'D':
		case 'd':
			if (res==1)
			{
				SET_BIT(PORTD,pinnum);
				//PORTD |= (1<<pinnum);
			}
	
			else
			{
				CLR_BIT(PORTD,pinnum);
				//PORTD &=(~(1<<pinnum));
			}
			break;

	}			 
}		
		
		
void DIO_vToggle(char portname ,char pinnum)
{
		switch(portname)
	{
		
		case'A':
		case'a':
		
			TOG_BIT(PORTA,pinnum);
			//PORTA ^=(1<<pinnum);
			break;
		
		case'B':
		case'b':
		
			TOG_BIT(PORTB,pinnum);
			//PORTB ^=(1<<pinnum);
			break;
		
		case'C':
		case'c':
		
			TOG_BIT(PORTC,pinnum);
			//PORTC ^=(1<<pinnum);
			break;
		
		case'D':
		case'd':
		
			TOG_BIT(PORTD,pinnum);
			//PORTD ^= (1<<pinnum);
			break;		
	}		
}		
			 		 
	char DIO_vRead (char portname ,char pinnum)
{
	char x=0;
	
		switch(portname)
		{
			case'A':
			case'a':
			
				x= READ_BIT_SET(PINA,pinnum);
				//x=(((PINA&(1<<(pinnum)))>>(pinnum)));
				break;
		
			case'B':
			case'b':
				
				x= READ_BIT_SET(PINB,pinnum);
				//x=(((PINB&(1<<(pinnum)))>>(pinnum)));
				break;
		
			case'C':
			case'c':
				
				x= READ_BIT_SET(PINC,pinnum);
				//x=(((PINC&(1<<(pinnum)))>>(pinnum)));
				break;
		
			case'D':
			case'd':
				
				x= READ_BIT_SET(PIND,pinnum);
				//x=(((PIND&(1<<(pinnum)))>>(pinnum)));
				break;
		}
	
				return x;	
}	
		
		
	void DIO_vpullup(char portname ,char pinnum,char conn)
{
		switch (portname)
		{
			case 'A':
			case 'a':
				if (conn==1)
				{
					SET_BIT(PORTA,pinnum);
					//PORTA |= (1<<pinnum);
				}
				
				else
				{
					CLR_BIT(PORTA,pinnum);
					//PORTA &=(~(1<<pinnum));
				}	
				
				break;
				
			case 'B':
			case 'b':
				if (conn==1)
				{
					SET_BIT(PORTB,pinnum);
					//PORTB |= (1<<pinnum);
				}
				
				else
				{
					CLR_BIT(PORTB,pinnum);
					//PORTB &=(~(1<<pinnum));
				}
				
				break;
				
			case 'C':
			case 'c':
				
				if (conn==1)
				{
					SET_BIT(PORTC,pinnum);
					//PORTC |= (1<<pinnum);
				}
				
				else
				{
					CLR_BIT(PORTC,pinnum);
					//PORTC &=(~(1<<pinnum));
				}
				
				break;
				
			case 'D':
			case 'd':
				
				if (conn==1)
				{
					SET_BIT(PORTD,pinnum);
					//PORTD |= (1<<pinnum);
				}
				
				else
				{
					CLR_BIT(PORTD,pinnum);
					//PORTD &=(~(1<<pinnum));
				}
				
				break;
		}			 
}
				
	void DIO_vPORTSET(char portName , char val)				
{
		switch(portName)
		{
				case 'A':
				
					PORTA = val;	
					break;
					
				case 'B':
				
					PORTB = val;
					break;
					
				case 'C':
					PORTC = val;
					break;
					
				case 'D':
					PORTD = val;
					break;
				
		}
}
		

		
		
		
		
				  