/*
 * ADC LM35.c
 *
 * Created: 7/25/2020 1:50:24 PM
 * Author : Mohammed
 */ 

#include <util/delay.h>
#include "Std_Types.h"
#include "Macros.h"
#include "DIO_interface.h"
#include "ADC_interface.h"
#include "LCD_interface.h"


int main(void)
{
    /* Replace with your application code */
	
	DIO_vidSetPinDirection(DIO_PORTA,DIO_PIN0,DIO_INPUT);
	
	ADC_vidInit(ADC_REF_AVCC,ADC_RIGHTADJUST,ADC_MUX_0,ADC_CLK_2);	
	
	LCD_vidInit();
	
	u8 u8Val = 0;	
	
    while (1) 
    {
		LCD_vidSendCommand(LCD_CLEAR_SCREEN);
		LCD_vidSendCommand(LCD_RETURN_HOME);
		u8Val = ADC_u16GetValue();
		LCD_vidWriteNumber(u8Val*0.488);
		
    }
}

