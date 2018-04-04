#include "Std_Types.h"
#include "Macros.h"
#include "DIO_interface.h"
#include "LCD_interface.h"
#include "TIMER2_interface.h"
#include "INTERRUPTS_interface.h"
#include <avr/io.h>

void count(void);

u32 u32OVFCount = 0;
void main(void) {
	LCD_vidInit();
	DIO_vidSetPinDirection(DIO_PORTB,DIO_PIN0,DIO_OUTPUT);
	DIO_vidSetPinDirection(DIO_PORTB,DIO_PIN7,DIO_OUTPUT);
	TIMER2_vidInit(TIMER2_WGM_PWM,TIMER2_COM_TOGGLE,TIMER2_CLK_1);
	TIMER2_vidSetOCRegister(125);
	void (*ptrFunc) (void);
	ptrFunc = count;
	
	LCD_vidWriteNumber((u16)OCR2);
	INTERRUPTS_vidPutISRFunction(ptrFunc);
	INTERRUPTS_vidSetInterruptEnable(INTERRUPTS_OCIE_2);
	INTERRUPTS_vidSetGlobalInterruptFlag();

	while(1) {	
	}
}

void count(void) {
	u32OVFCount++;
	if (u32OVFCount == 32000) {			
		TOGGLE_BIT(PORTB,0);
		u32OVFCount = 0;
		TCNT2 = 192;
	}
}
