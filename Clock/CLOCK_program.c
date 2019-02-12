/*
 * Author: Mohamed Ahmed Abd Al-Fattah
 * Purpose: CLOCK application module
 *
 */

#include "Std_Types.h"
#include "Macros.h"
#include "DIO_interface.h"
#include "LCD_interface.h"
#include "CLOCK_interface.h"

volatile u32 u32OvFCount;
volatile u8 u8Sec;
volatile u8 u8Minute;
volatile u8 u8Hours;

#define  LCD_XPOS_SHIFT 6

void CLOCK_vidCount(void) {
	u32OvFCount++;
	if (u32OvFCount == 32250) {
		u32OvFCount = 0;
		u8Sec++;
		if (u8Sec == 60) {
			u8Sec = 0;
			u8Minute++;
			if (u8Minute == 60) {
				u8Minute = 0;
				u8Hours++;
				if (u8Hours == 23) {
					u8Hours = 0;
				}
			}
		}
		LCD_vidWriteInPlace(LCD_XPOS_SHIFT+LCD_XPOS0,u8Hours/10+'0');	
		LCD_vidWriteInPlace(LCD_XPOS_SHIFT+LCD_XPOS1,u8Hours%10+'0');
		LCD_vidWriteInPlace(LCD_XPOS_SHIFT+LCD_XPOS2,':');
		LCD_vidWriteInPlace(LCD_XPOS_SHIFT+LCD_XPOS3,u8Minute/10+'0');
		LCD_vidWriteInPlace(LCD_XPOS_SHIFT+LCD_XPOS4,u8Minute%10+'0');
		LCD_vidWriteInPlace(LCD_XPOS_SHIFT+LCD_XPOS5,':');
		LCD_vidWriteInPlace(LCD_XPOS_SHIFT+LCD_XPOS6,u8Sec/10+'0');
		LCD_vidWriteInPlace(LCD_XPOS_SHIFT+LCD_XPOS7,u8Sec%10+'0');
	}

}

void CLOCK_vidIncrementHours(void) {
	u8Hours++;
}

void CLOCK_vidIncrementMinutes(void) {
	u8Minute++;
}