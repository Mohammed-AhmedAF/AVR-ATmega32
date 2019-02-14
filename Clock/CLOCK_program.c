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

/*Global variables modified in ISR*/
volatile u8 u8AlarmFlag = 1;
volatile u32 u32OvFCount;
volatile u8 u8Sec = 0;
volatile u8 u8Minute = 33;
volatile u8 u8Hours = 2;
volatile u8 u8AlarmMinute = 3;

/*This macro will be changed according to 
 *the clock source provided to timer and
 *the timer MAX count.
 * */
#define CLOCK_SEC_OVFCOUNT 31250

/*This macro is used to shift the clock digits
 *on LCD row.
 * */
#define  LCD_XPOS_SHIFT 6

void CLOCK_vidCount(void) {
	u32OvFCount++;
	if (u32OvFCount == CLOCK_SEC_OVFCOUNT) {
		u32OvFCount = 0;
		u8Sec++;
		if (u8Sec == 60) {
			u8Sec = 0;
			u8Minute++;
			if (u8AlarmFlag == 1) {
				CLOCK_vidCheckAlarm();
			}
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
#ifdef CLOCK_AMPM_SWITCH
		if (u8Hours <= 12) {
			LCD_vidWriteInPlace(LCD_XPOS_SHIFT+LCD_XPOS9,'A');
			LCD_vidWriteInPlace(16,'M');
		}
		else {
			LCD_vidWriteInPlace(LCD_XPOS_SHIFT+LCD_XPOS9,'P');
			LCD_vidWriteInPlace(LCD_XPOS_SHIFT+LCD_XPOS10,'M');
		}
#endif
	}

}

void CLOCK_vidIncrementHours(void) {
	u8Hours++;
}

void CLOCK_vidIncrementMinutes(void) {
	u8Minute++;
}

void CLOCK_vidCheckAlarm(void) {
	if (u8Minute == u8AlarmMinute) {
		LCD_vidWriteInPlace(LCD_XPOS_SHIFT+LCD_XPOS11,'A');
	}
}
