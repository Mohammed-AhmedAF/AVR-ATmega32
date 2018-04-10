#include "Std_Types.h"
#include "Macros.h"
#include "DIO_interface.h"
#include "ADC_interface.h"
#include "LCD_interface.h"
#include <avr/io.h>
#include <util/delay.h>

u8 u8Value = 0;
u16 u16Value = 0;
u8 u8ToChar(u8);

void main(void) {
	DIO_vidSetPortDirection(DIO_PORTB,0b11111111);
	ADC_vidInit(ADC_REF_AREF,ADC_LEFTADJUST,ADC_MUX_7,ADC_CLK_128);
	LCD_vidInit();

	while(1) {
		u8Value = ADC_u8GetValue();
		u16Value = (u16) (5*u8Value)/256;
		DIO_vidSetPortValue(DIO_PORTB,u8Value);
		u8ToChar(u8Value);
		//LCD_vidWriteNumber(u16Value);
		_delay_ms(2000);
		LCD_vidSendCommand(LCD_CLEAR_SCREEN);
	}
}

u8 u8ToChar(u8 res) {
	u8 x = 100;
	u8 u8a;
	u8 arr[3];
	u8 * message;
	for (s8 i = 0; i < 3; i++) {
		u8a = (res/x)+48;
		res = res - (res/x)*x;
		arr[i] = u8a;
		x = x/10;
	}
	message = arr;
	LCD_vidInsertSizedMessage(message,3);
	_delay_ms(500);
	LCD_vidSendCommand(LCD_CLEAR_SCREEN);
	LCD_vidSendCommand(LCD_RETURN_HOME);


}
