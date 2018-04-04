#include "Std_Types.h"
#include "Macros.h"
#include "DIO_interface.h"
#include "LCD_interface.h"
#include <avr/interrupt.h>
#include "TIMER0_interface.h"
#include "INTERRUPTS_interface.h"
#include <avr/io.h>

void count(void);

u32 u32OVFCount = 0;
void main(void) {
	LCD_vidInit();
	DIO_vidSetPinDirection(DIO_PORTB,DIO_PIN0,STD_INPUT);
	DIO_vidSetPinDirection(DIO_PORTB,DIO_PIN3,DIO_OUTPUT);
	TIMER0_vidSetOCRegister(100);
	LCD_vidWriteNumber((u16)OCR0);
	TIMER0_vidInit(TIMER0_WGM_FPWM,TIMER0_COM_CLEAR,TIMER0_CLK_1);
	void (*ptrFunc) (void);
	ptrFunc = count;

	INTERRUPTS_vidPutISRFunction(ptrFunc);
	INTERRUPTS_vidSetInterruptEnable(INTERRUPTS_TOIE_0);
	INTERRUPTS_vidSetGlobalInterruptFlag();

	while(1) {	
	}
}

void count(void) {
	u32OVFCount++;
	if (u32OVFCount == 32000) {			
		TOGGLE_BIT(PORTB,0);
		u32OVFCount = 0;
	}
}
