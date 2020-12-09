/*
 * UARTCPP.cpp
 *
 * Created: 12/9/2020 11:28:16 AM
 * Author : Mohammed
 */ 

#include <avr/io.h>
#include "Std_Types.h"
#include "Macros.h"
#include "DIO_interface.h"
#include "TIMER0_interface.h"
#include "INTERRUPTS_interface.h"

u16 u16OVFCount = 0;

void vidBlink(void)
{
	u16OVFCount++;
	if (u16OVFCount == 31250)
	{
		u16OVFCount = 0;
		DIO_vidTogglePin(DIO_PORTD,DIO_PIN2);
	}
}


int main(void)
{
    /* Replace with your application code */
	
	DIO_vidSetPinDirection(DIO_PORTD,DIO_PIN2,DIO_OUTPUT);
	DIO_vidSetPinValue(DIO_PORTD,DIO_PIN2,STD_HIGH);
	
	TIMER0_vidInit(TIMER0_WGM_NORMAL,TIMER0_COM_NORMAL,TIMER0_CLK_1);
	
	INTERRUPTS_vidPutISRFunction(INTERRUPTS_TIMER0_OVF,vidBlink);
	INTERRUPTS_vidEnableInterrupt(INTERRUPTS_TIMER0_OVF);
	INTERRUPTS_vidSetGlobalInterruptFlag();
	
    while (1) 
    {
    }
}

