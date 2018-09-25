/*
 * Author: Mohammed Ahmed Abd Al-Fattah
 * Project: Digital Clock for AVR Atmega32 
 *
 */

#include "Std_Types.h"
#include "Macros.h"
#include "DIO_interface.h"
#include "LCD_interface.h"
#include "TIMER0_interface.h"
#include "INTERRUPTS_interface.h"
#include "KEYPAD_interface.h"
#include "SERVICES_interface.h"

#define SHIFT 4

/*Global variables*/
volatile u8 hour = 0;
volatile u8 min = 58;
volatile u16 sec = 0;
volatile u32 u32OVFCount = 0;
volatile u8 i = 0;
volatile u8 Flag = 0;
volatile u8 u8AlarmMin = 5;

/*Function prototypes*/
void vidCount(void);
void vidInitClock(void);
void vidIncrementHour(void);
void vidIncrementMinute(void);
void vidCheckMinute(u8);
void vidSetAlarm(void);

void vidCount(void) {
	u32OVFCount++;
	if (u32OVFCount == 31250) {
		u32OVFCount = 0;
		sec++;
		if (sec < 60) {
			/*Writing seconds*/
			LCD_vidGoToXY(6+SHIFT,0);
			LCD_vidWriteNumber(sec/10);
			LCD_vidGoToXY(7+SHIFT,0);
			LCD_vidWriteNumber(sec%10);

		}
		else {
			sec = 0;
			LCD_vidGoToXY(6+SHIFT,0);
			LCD_vidWriteCharacter('0');
			LCD_vidGoToXY(7+SHIFT,0);
			LCD_vidWriteNumber(sec);
			min++;
			vidCheckMinute(min);	
			if (min < 60) {
				/*Writing minutes*/
				LCD_vidGoToXY(3+SHIFT,0);
				LCD_vidWriteNumber(min/10);
				LCD_vidGoToXY(4+SHIFT,0);
				LCD_vidWriteNumber(min%10);
			}
			else  {
				min = 0;
				LCD_vidGoToXY(3+SHIFT,0);
				LCD_vidWriteNumber(min/10);
				LCD_vidGoToXY(4+SHIFT,0);
				LCD_vidWriteNumber(min%10);
				hour++;
				if (hour < 24) {
					/*Writing hours*/
					LCD_vidGoToXY(0+SHIFT,0);
					LCD_vidWriteNumber(hour/10);
					LCD_vidGoToXY(1+SHIFT,0);
					LCD_vidWriteNumber(hour%10);
				}
				else {
					hour = 0;
					LCD_vidGoToXY(0+SHIFT,0);
					LCD_vidWriteNumber(hour/10);
					LCD_vidGoToXY(1+SHIFT,0);
					LCD_vidWriteNumber(hour%10);
				}
			}
		}
	}

}


void main(void) {
	/*Initialization*/
	LCD_vidInit();
	vidInitClock();

	/*Setting External Interrupt pin direction as Input*/
	DIO_vidSetPinDirection(DIO_PORTD,DIO_PIN2,DIO_INPUT);
	DIO_vidSetPinValue(DIO_PORTD,DIO_PIN2,STD_HIGH);
	DIO_vidSetPinDirection(DIO_PORTD,DIO_PIN3,DIO_INPUT);
	DIO_vidSetPinValue(DIO_PORTD,DIO_PIN3,STD_HIGH);

	/*Setting Timer 0, used for counting*/
	TIMER0_vidInit(TIMER0_WGM_NORMAL,TIMER0_COM_NORMAL,TIMER0_CLK_1);
	/*Setting interrupt for Timer 0*/
	INTERRUPTS_vidSetInterruptEnable(INTERRUPTS_TOIE_0);
	INTERRUPTS_vidPutISRFunction(vidCount,INTERRUPTS_USUAL);

	/*Setting External Interrupt 0, used for incrementing hours*/
	INTERRUPTS_vidSetInterruptEnable(INTERRUPTS_INT_0); 
	INTERRUPTS_vidPutISRFunction(vidIncrementHour,INTERRUPTS_INT_0);
	INTERRUPTS_vidSetSenseControl(INTERRUPTS_INT_0,INTERRUPTS_SC_FALLING);

	/*Setting External Interrupt 1, used for incrementing minutes*/
	INTERRUPTS_vidSetInterruptEnable(INTERRUPTS_INT_1);
	INTERRUPTS_vidPutISRFunction(vidIncrementMinute,INTERRUPTS_INT_1);
	INTERRUPTS_vidSetSenseControl(INTERRUPTS_INT_1,INTERRUPTS_SC_FALLING);
	
	/*Setting global interrupt flag*/	
	INTERRUPTS_vidSetGlobalInterruptFlag();

	while(1) {
	}
}

void vidIncrementHour(void) {
	hour++;
	if (hour > 24) {
		hour = 0;
	}
	LCD_vidGoToXY(0+SHIFT,0);
	LCD_vidWriteNumber(hour/10);
	LCD_vidGoToXY(1+SHIFT,0);
	LCD_vidWriteNumber(hour%10);
}

void vidIncrementMinute(void) {
	min++;
	if (min > 59) {
		min = 0;
	}
	LCD_vidGoToXY(3+SHIFT,0);
	LCD_vidWriteNumber(min/10);
	LCD_vidGoToXY(4+SHIFT,0);
	LCD_vidWriteNumber(min%10);
}


void vidInitClock(void) {
	LCD_vidSendCommand(LCD_CLEAR_SCREEN);
	LCD_vidSendCommand(LCD_RETURN_HOME);
	LCD_vidWriteInPlace(0+SHIFT,'0');
	LCD_vidWriteInPlace(1+SHIFT,'0');
	LCD_vidWriteInPlace(2+SHIFT,':');
	LCD_vidWriteInPlace(3+SHIFT,min/10+'0');
	LCD_vidWriteInPlace(4+SHIFT,min%10+'0');
	LCD_vidWriteInPlace(5+SHIFT,':');
	LCD_vidWriteInPlace(6+SHIFT,'0');
	LCD_vidWriteInPlace(7+SHIFT,'0');
}

void vidCheckMinute(u8 u8MinCpy) {
	if (u8AlarmMin == u8MinCpy) {
		DIO_vidSetPinValue(DIO_PORTD,DIO_PIN7,STD_HIGH);
	}
}

void vidSetAlarm(void) {
	LCD_vidSendCommand(LCD_CLEAR_SCREEN);
	LCD_vidSendCommand(LCD_RETURN_HOME);
	LCD_vidWriteString("Minutes: \0");	
	LCD_vidGoToXY(0,1);
	LCD_vidWriteString("Hours: \0");
	LCD_vidGoToXY(10,0);
	SERVICES_vidWriteCharacter();

}
