/* 
 * File:   LCD.h
 * Author: GOPAL
 *
 * Created on February 4, 2017, 9:12 AM
 */

#ifndef LCD_H
#define	LCD_H

#ifdef	__cplusplus
extern "C" {
#endif

void Lcd_Init(void);
void Display_Lcd (unsigned char  *arr,unsigned char cur_posn);
void Lcd_Char (unsigned char charval,unsigned char cur_posn);

#ifdef	__cplusplus
}
#endif

#endif	/* LCD_H */

