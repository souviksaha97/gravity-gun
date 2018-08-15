/* 
 * File:   PIC18_Serial.h
 * Author: GOPAL
 *
 * Created on January 15, 2017, 12:53 PM
 */

#ifndef PIC18_SERIAL_H
    #define	PIC18_SERIAL_H  extern
#else
    #define PIC18_SERIAL_H
#endif	/* PIC18_SERIAL_H */

#define Sizeof_Serial_rcvBuffer  128

PIC18_SERIAL_H unsigned char Serial_rcvBuffer[Sizeof_Serial_rcvBuffer];
PIC18_SERIAL_H unsigned char Serial_rxtail;
PIC18_SERIAL_H unsigned char Serial_rxhead;

PIC18_SERIAL_H void PIC18_Serial_Init(void);
PIC18_SERIAL_H unsigned char PIC18_Serial_avail(void);
PIC18_SERIAL_H unsigned char PIC18_Serial_getchar(void);
//PIC18_SERIAL_H void putchar(unsigned char buf);
PIC18_SERIAL_H void PIC18_Serial_putString(unsigned char *buf,unsigned char len);




