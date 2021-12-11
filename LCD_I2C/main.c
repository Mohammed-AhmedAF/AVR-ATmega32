/*
 * LCD-IC.c
 *
 * Created: 12/4/2021 11:05:18 PM
 * Author : Mohammed
 */ 

#include <avr/io.h>
#include "Macros.h"
#include "Std_Types.h"
#include "DIO_interface.h"
#include "TWI_interface.h"
#include "PCF8574_interface.h"
#include "LCD_I2C_interface.h"
#include "TIMER0_interface.h"
#include "INTERRUPTS_interface.h"
#include <util/delay.h>

volatile u16 u16Count = 0;
volatile u8 i = 0;
void vidCount(void)
{
	u16Count++;
	if (u16Count == 41000)
	{
		i++;
		LCD_I2C_vidSendCommand(LCD_I2C_CLEAR_SCREEN);
		LCD_I2C_vidSendCommand(LCD_I2C_RETURN_HOME);
		LCD_I2C_vidSendNumber(i);
		u16Count = 0;
	}
}

int main(void)
{
	TWI_vidInit();
	
	LCD_I2C_vidInit();
	
	LCD_I2C_vidSendString((u8*)"Moscow calls!\0");
	DIO_vidSetPinDirection(DIO_PORTA,DIO_PIN0,DIO_OUTPUT);
	DIO_vidSetPinValue(DIO_PORTA,DIO_PIN0,DIO_PIN0);
	
	TIMER0_vidInit(TIMER0_WGM_NORMAL,TIMER0_COM_NORMAL,TIMER0_CLK_1);

	INTERRUPTS_vidEnableInterrupt(INTERRUPTS_TIMER0_OVF);
	INTERRUPTS_vidPutISRFunction(INTERRUPTS_TIMER0_OVF,vidCount);
	INTERRUPTS_vidSetGlobalInterruptFlag();

    /* Replace with your application code */
    while (1) 
    {
		

    }
}

