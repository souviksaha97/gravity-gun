/*
 * File:   Project.c
 * Author: fsociety
 *
 * Created on 14 April, 2018, 10:03 AM
 */

/*
 * CCP1/RC2 is bottom sensor
 * CCP2/RC1 is top sensor
 */

#include <xc.h>
#include <stdio.h>
#include <math.h>
#include "LCD.h"
#include "PIC18_Serial.h"

#define CCP1 TRISCbits.RC2
#define CCP2 TRISCbits.RC1


#define _XTAL_FREQ 16000000L

unsigned char messages[5][16] ={ "GO PAWAR RANGERS",
                                 "<<<<<<<<>>>>>>>>",
                                 "  !INITIALIZED! ",
                                 "FALL TIME IN S  ",
                                 "GRAV. ACC (g) IS"
                                };


double hexToDec(unsigned char, unsigned char);
void ccp_Init(void);
void ser_Init(void);
void SerTx(unsigned char[]);

int count=0;

void main(void) @ 0x200
{
    ser_Init();
    SerTx(messages[0]);
    SerTx(messages[1]);
    SerTx(messages[2]);
    ccp_Init();
    while(1);
}

void ser_Init(void)
{
    TXSTA = 0x20;
    SPBRG = 25;
    TXSTAbits.TXEN = 1;
    RCSTAbits.SPEN = 1;
}

void ccp_Init(void)
{
    CCP1 = 1;
    CCP2 = 1;
    CCP1CON = 0x05;
    CCP2CON = 0x05;
    T3CON = 0x00;
    PIE1bits.CCP1IE=1; 
    PIE2bits.CCP2IE=1;
    PIE1bits.TMR1IE = 1;
    T1CON = 0x30;
    TMR1H = 0;
    TMR1L = 0;
    PIR1bits.CCP1IF = 0;
    PIR2bits.CCP2IF = 0;
    PIR1bits.TMR1IF = 0;
    RCONbits.IPEN = 0;  
    INTCONbits.PEIE = 1;
    INTCONbits.GIE=1;
}

static void interrupt isr(void) 
{   
    if (PIR2bits.CCP2IF == 1) // sensor on top
    {
        T1CONbits.TMR1ON = 1;
    }
    if (PIR1bits.CCP1IF == 1 && PIR2bits.CCP2IF == 1) // bottom sensor hit
    {
        T1CONbits.TMR1ON = 0;
        //SerTx("XX");
        unsigned char buff[16];
        unsigned char buff1[16];
        double time = hexToDec(CCPR1H, CCPR1L);
        double gVal = 1/(pow(time, 2));
        sprintf(buff1, "%.3f", gVal);
        sprintf(buff, "%.5f", time);
        SerTx(buff);
        SerTx(buff1);
        //SerTx(count);
        PIE1bits.CCP1IE=0; //
        PIE2bits.CCP2IE=0;
        PIE1bits.TMR1IE = 0;
        Lcd_Init();
        Display_Lcd("                ", 0x80);
        Display_Lcd("                ", 0xC0);
        Display_Lcd(messages[3], 0x80);
        Display_Lcd(buff, 0xC0);
        _delay(10000000);
        Display_Lcd("                ", 0x80);
        Display_Lcd("                ", 0xC0);
        Display_Lcd(messages[4], 0x80);
        Display_Lcd(buff1, 0xC0);
        
    }
    else if (PIR1bits.CCP1IF == 1 && PIR2bits.CCP2IF == 0)
    {
        SerTx("!!Try again!!");
        Lcd_Init();
        Display_Lcd("Try again!", 0x80);
    }
        
    if (PIR1bits.TMR1IF == 1)
    {
        //SerTx("//");
            PIR1bits.TMR1IF = 0;
            TMR1L = 0;
            TMR1H = 0;
            count = count+1;
        //SerTx(count);
    }
}   

double hexToDec(unsigned char hiByte, unsigned char loByte)
{
    double convOutput = (hiByte*256)+loByte;
    
    if (convOutput < 0)
        convOutput = 65536+convOutput;
    
    int i = 0;
    char bitVal = 0;
    int value = 0;
    
    double decOutput = (65535*count) + convOutput;
    
    double finalTime = decOutput*(2e-6);//
    return finalTime;
}

void SerTx(unsigned char text[])
{
    for (int i = 0; i < 17; i++)
    {
        while(PIR1bits.TXIF == 0);
            TXREG = text[i];
    }
}
