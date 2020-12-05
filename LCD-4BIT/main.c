/*
 * LCD-ATMega32.c
 *
 * Created: 12/5/2020 6:35:04 PM
 * Author : Mohammed
 */ 
#include "Std_Types.h"
#include "Macros.h"

#include "DIO_interface.h"

#include <util/delay.h>
#include "LCD_interface.h"


int main(void)
{
    LCD_vidInit();
	_delay_ms(100);
	LCD_vidWriteString("Hello world!");
    while (1) 
    {

    }
}

