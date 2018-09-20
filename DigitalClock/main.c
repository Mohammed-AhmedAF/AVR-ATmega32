/*
 * Author: Mohammed Ahmed Abd Al-Fattah
 * Project: Digital Clock
 *
 */

#include "Std_Types.h"
#include "Macros.h"
#include "DIO_interface.h"
#include "LCD_interface.h"
#include "TIMER0_interface.h"
#include "INTERRUPTS_interface.h"


/*Global variables*/
volatile u8 hour = 0;
volatile u8 min = 0;
volatile u16 sec = 0;
volatile u32 u32OVFCount = 0;
volatile u8 i = 0;

void vidCount(void);
void vidInitClock(void);

void vidCount(void) {
	u32OVFCount++;
	if (u32OVFCount == 31250) {
		u32OVFCount = 0;
		sec++;
		if (sec < 60) {
			if (sec < 10){
				LCD_vidGoToXY(6,0);
				LCD_vidWriteNumber(0);
				LCD_vidGoToXY(7,0);
				LCD_vidWriteNumber(sec);
			}
			else {
				LCD_vidGoToXY(6,0);
				LCD_vidWriteNumber(sec/10);
				LCD_vidGoToXY(7,0);
				LCD_vidWriteNumber(sec%10);
			}
		}
		else {
			sec = 0;
			LCD_vidGoToXY(6,0);
			LCD_vidWriteCharacter('0');
			LCD_vidGoToXY(7,0);
			LCD_vidWriteNumber(sec);
			min++;
			LCD_vidGoToXY(4,0);
			LCD_vidWriteNumber(min);
			if (min == 59) {
				min = 0;
				hour++;
				if (hour == 24) {
					hour = 0;
				}
				else {
					LCD_vidGoToXY(0,0);
					LCD_vidWriteNumber(hour);
				}
			}
		}
	}

}

void vidInitClock(void) {
	LCD_vidSendCommand(LCD_CLEAR_SCREEN);
	LCD_vidSendCommand(LCD_RETURN_HOME);
	LCD_vidWriteCharacter('0');
	LCD_vidWriteCharacter('0');
	LCD_vidWriteCharacter(':');
	LCD_vidWriteCharacter('0');
	LCD_vidWriteCharacter('0');
	LCD_vidWriteCharacter(':');
	LCD_vidWriteCharacter('0');
	LCD_vidWriteCharacter('0');
}

void main(void) {
	/*Initialization*/
	LCD_vidInit();
	vidInitClock();
	TIMER0_vidInit(TIMER0_WGM_NORMAL,TIMER0_COM_NORMAL,TIMER0_CLK_1);
	INTERRUPTS_vidSetInterruptEnable(INTERRUPTS_TOIE_0);
	INTERRUPTS_vidSetGlobalInterruptFlag();
	INTERRUPTS_vidPutISRFunction(vidCount);
	while(1);
}
