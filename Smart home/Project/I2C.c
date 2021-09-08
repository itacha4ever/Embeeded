/*
 * I2C.c
 *
 * Created: 9/14/2018 5:17:47 PM
 *  Author: 3laa
 */ 
//#include "I2C.h"
//#include <avr/io.h>
#include "COMMON_CONFIG.h"
/*	incopmlete

	void TWI_vMasterInt()
{
	TWBR = (char)TWBR_val;

}*/
/*	void TWI_MasterTrans(char address, char data)
{
	//start
	TWCR = 0X00;
	SET_BIT(TWCR,TWINT); //set falg
	SET_BIT(TWCR,TWEN);  //enable I2c
	SET_BIT(TWCR,TWSTA);
	while(!(READ_BIT_SET(TWCR,TWINT)))
	{
		
	}
	if ((TWSR &0xF8)==0x08)
	{	
		//send addrs
		TWDR= address <<1;
		SET_BIT(TWCR,TWINT);
		while(!(READ_BIT_SET(TWCR,TWINT))){} //wait
		
		if ((TWSR &0xF8)==0x18)
		{			
			//send data
			TWDR = data;
			SET_BIT(TWCR,TWEN);
			SET_BIT(TWCR,TWINT);
			while(!(READ_BIT_SET(TWCR,TWINT))){} //wait
			if ((TWSR &0xF8)==0x28)
			{	
				DDRA = 0XFF;		
				//stop
				SET_BIT(TWCR,TWSTO);
				//SET_BIT(TWCR,TWINT);
			}		
	 
			else
			{
				
				//stop
				SET_BIT(TWCR,TWEN);
				//SET_BIT(TWCR,TWINT);
				
				SET_BIT(TWCR,TWSTO);
				
			}
		}	
	    else
		{
		 // Address not acked   
		    //stop
		    SET_BIT(TWCR,TWSTO);
			SET_BIT(TWCR,TWINT);
		}
	}		
		 else{
			 
			 //stop
			 SET_BIT(TWCR,TWSTO);
		 SET_BIT(TWCR,TWINT);
		 
		 }
	
		}*/			
/*void TWI_vSlvint(char address){
	
	TWAR =address<<1;	
	SET_BIT(TWCR,TWINT); // say slave addr
	SET_BIT(TWCR,TWEN); //
	SET_BIT(TWCR,TWEA); // send ack	
	
}

char TWI_Slaveavilb(){
	
	SET_BIT(TWCR,TWINT);
	while(!(READ_BIT_SET(TWCR,TWINT))){}
		if ((TWSR &0xF8)==0x60){
			return 1;
		}
			else{return 0;}
				
		
	
}

char TWI_Read(){
	DDRA = 0XFF;
	SET_BIT(TWCR,TWINT);
	SET_BIT(TWCR,TWEN);
	SET_BIT(TWCR,TWEA);
	while(!(READ_BIT_SET(TWCR,TWINT))){}
	DDRB = 0XFF;
	return TWDR;
}*/

	void TWI_vMasterInt()
{
		TWBR = (char)TWBR_val;

}
	void TWI_MasterTrans(char address, char data)
{
		TWI_Start();
		TWI_MSendAdrrs(address);
		TWI_MSendData(data);
		TWI_MStop();

	
}

	void TWI_Start()
{
		/*start*/
		TWCR = 0x00;
		SET_BIT(TWCR,TWINT); //set falg
		SET_BIT(TWCR,TWEN);  //enable I2c
		SET_BIT(TWCR,TWSTA);
		while(!(READ_BIT_SET(TWCR,TWINT)))
		{
			//wait
		}
		
		if ((TWSR &0xF8)==0x08)
		{
			
		}
		else
		{
			
		}
			
			
}			


	void TWI_MSendAdrrs(char address)
{
		/*send addrs*/
		TWDR= address <<1;
		SET_BIT(TWCR,TWINT);
		
		while(!(READ_BIT_SET(TWCR,TWINT)))
		{
			//wait
		} 

		if ((TWSR &0xF8)==0x18)
		{
			
		}
		
		else
		{
			
		}


}	


	void TWI_MSendData(char data)
{
		/*send data*/
		TWDR = data;
		SET_BIT(TWCR,TWINT);
		while(!(READ_BIT_SET(TWCR,TWINT)))
		{
			//wait
		} 
		
		if ((TWSR &0xF8)==0x28)
		{
			
		}
		
		else
		{
			
		}

}	
	
		
	void TWI_MStop()
{
		/*stop*/
		SET_BIT(TWCR,TWSTO);
		SET_BIT(TWCR,TWINT);
}
				
					
	void TWI_vSlvint(char address)
{
	
		TWAR =address<<1;	
		SET_BIT(TWCR,TWINT); // say slave addr
		SET_BIT(TWCR,TWEN); //
		SET_BIT(TWCR,TWEA); // send ack	
	
}


	char TWI_Slaveavilb()
{
	
		SET_BIT(TWCR,TWINT);
		
		while(!(READ_BIT_SET(TWCR,TWINT)))
		{
			
		}
			
		if ((TWSR &0xF8)==0x60)
		{
			return 1;
		}
		
		else
		{
			return 0;
		}
				
		
	
}


	char TWI_Read()
{
		DDRA = 0XFF;
		SET_BIT(TWCR,TWINT);
		SET_BIT(TWCR,TWEN);
		SET_BIT(TWCR,TWEA);
		while(!(READ_BIT_SET(TWCR,TWINT)))
		{
			
		}
		DDRB = 0XFF;
		return TWDR;
}