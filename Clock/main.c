/*
 * Author: Mohamed Ahmed Abd Al-Fattah
 * Purpose; Clock with alarm
 *
 */

#include "Std_Types.h"
#include "Macros.h"
#include "DIO_interface.h"
#include "TIMER0_interface.h"
#include "INTERRUPTS_private.h"
#include "INTERRUPTS_interface.h"
#include "LCD_interface.h"
#include "CLOCK_interface.h"

void main(void) {

	TIMER0_vidInit(TIMER0_COM_NORMAL,TIMER0_WGM_NORMAL,TIMER0_CLK_1);
	INTERRUPTS_vidSetInterruptEnable(INTERRUPTS_TOIE_0);
	INTERRUPTS_vidPutISRFunction(CLOCK_vidCount);
	_Int_EN();
	LCD_vidInit();

	LCD_vidGoToXY(LCD_XPOS0,1);
	while(1) {
		LCD_vidGoToXY(1,2);
		LCD_vidWriteCharacter('1');
		LCD_vidWriteCharacter('A');
	}
}
