// switch on back light -->0xBF
/*********************************************************************************************************************
LATC.0 -->D0
LATC.1 -->D1
LATC.2 -->D2
LATC.3 -->D3
LATC.4 -->EN
LATC.5 -->R/S	0 command , 1 data
LATC.6 -->
LATC.7 -->
*********************************************************************************************************************/
#include<xc.h>
#include "PIC18_Serial.h"


#define _XTAL_FREQ  16000000L

void Delay_ms(int count )
{
    for(;count !=0;count--)
        __delay_ms(1);
}
void Lcd_Dat(unsigned char lcd_char)
{
	LATCbits.LATC5=1;
	__delay_us(20);
	LATC &= 0xF0;
	LATC |= (lcd_char>>4) & 0x0F;
	__delay_us(20);
	LATCbits.LATC4=1;
	__delay_us(20);
	LATCbits.LATC4=0;
	__delay_us(20);

	
	LATC &= 0xF0;
	LATC |= (lcd_char) & 0x0F;
	__delay_us(20);
	LATCbits.LATC4=1;
	__delay_us(20);
	LATCbits.LATC4=0;
	__delay_us(20);
}


void Lcd_Cmd(unsigned char lcd_char)
{
	LATCbits.LATC5=0;
	__delay_us(20);
	LATC &= 0xF0;
	LATC |= (lcd_char>>4) & 0x0F;
	__delay_us(20);
	LATCbits.LATC4=1;
	__delay_us(20);
	LATCbits.LATC4=0;
	__delay_us(20);

	
	LATC &= 0xF0;
	LATC |= (lcd_char) & 0x0F;
	__delay_us(20);
	LATCbits.LATC4=1;
	__delay_us(20);
	LATCbits.LATC4=0;
	__delay_us(20);

}


void Lcd_Init(void)
{
    TRISC &= 0xC0;
    
	LATCbits.LATC5=0;
	LATC &= 0xF0;
	LATC |= 0x03;
	__delay_us(100);

    LATCbits.LATC4=1;
	__delay_us(100);
	LATCbits.LATC4=0;
	__delay_ms(10);

	LATCbits.LATC4=1;
	__delay_us(100);
	LATCbits.LATC4=0;
	Delay_ms(50);

	LATCbits.LATC4=1;
	__delay_us(100);
	LATCbits.LATC4=0;
	Delay_ms(50);;


	LATC &= 0xF0;
	LATC |= 0x02;
	__delay_us(100);
	LATCbits.LATC4=1;
	__delay_us(100);
	LATCbits.LATC4=0;
	Delay_ms(50);


	Lcd_Cmd(0x28);
	Delay_ms(500);
	Lcd_Cmd(0x0c);
	Delay_ms(500);
	Lcd_Cmd(0x06);
	Delay_ms(500);

	Lcd_Cmd(0x01);
	Delay_ms(1000);

}


void Display_Lcd (unsigned char  *arr,unsigned char cur_posn)
{
        char ovr;
	unsigned char  count ;
	Lcd_Cmd(cur_posn);
	__delay_us(10);

	for(count=0;count<16;count++)
	{
	   if(arr[count]==0)
	   {
	   	ovr=1;
	   	break;
	   }
	   Lcd_Dat(arr[count]);
	}
	if(!ovr)
	{
       
		Lcd_Cmd(0xc0);
		for(count=16;count<32;count++)
		{
	  		if(arr[count]==0)
		    	 break;
			Lcd_Dat(arr[count]);
    	}
    }
	ovr=0;
}

void Lcd_Char (unsigned char charval,unsigned char cur_posn)
{
	Lcd_Cmd(cur_posn);
	__delay_us(500);
    Lcd_Dat(charval);
}




