#include "Macros.h"
#include "Std_Types.h"
#include "DIO_interface.h"
#include "LCD_interface.h"
#include "RTC_interface.h"
#include <util/delay.h>

RTC_t rtc;
u16 u16HoursFirstDigit;
u8 u8TestValue = 10;

void main(void) {
	
	RTC_vidInit();

	LCD_vidInit();

	rtc.u8Seconds = 0;
	rtc.u8Minutes = 58;
	rtc.u8Hours = 9;

	RTC_vidSetTime(&rtc);
	
	while(1) {
		_delay_ms(3000);
		LCD_vidSendCommand(LCD_CLEAR_SCREEN);
		LCD_vidSendCommand(LCD_RETURN_HOME);
		RTC_vidGetTime(&rtc);
		LCD_vidGoToXY(LCD_XPOS0,LCD_YPOS0);
		LCD_vidWriteNumber(rtc.u8Seconds);
		LCD_vidGoToXY(LCD_XPOS3,LCD_YPOS0);
		LCD_vidWriteNumber(rtc.u8Minutes);
		LCD_vidGoToXY(LCD_XPOS6,LCD_YPOS0);
		LCD_vidWriteNumber(rtc.u8Hours);
		LCD_vidGoToXY(LCD_XPOS10,LCD_YPOS0);
		LCD_vidWriteNumber(u8TestValue);

	}
}
