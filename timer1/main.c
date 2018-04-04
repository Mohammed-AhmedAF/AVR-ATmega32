
/* Name: Mohamed Ahmed Abd Al-Fattah Mahmoud
 * Date: 4-4-2018 (First completion)
 */

#include "Std_Types.h"
#include "Macros.h"
#include "DIO_interface.h"
#include "INTERRUPTS_interface.h"
#include "TIMER1_interface.h"

void vidToggleLED(void);

u16 u16Count;
void (*ptrFunc) (void);
int main(void) {
	DIO_vidSetPinDirection(DIO_PORTD,DIO_PIN5,DIO_OUTPUT); //Output pin for OC1A
	TIMER1_vidInit(TIMER1_WGM_FPWM_OCR,TIMER1_COM1A_NORMAL,TIMER1_COM1B_NORMAL,TIMER1_CLK_1);

	DIO_vidSetPinValue(DIO_PORTD,DIO_PIN5,STD_HIGH);

	TIMER1_vidSetOCRA(256);
	INTERRUPTS_vidSetInterruptEnable(INTERRUPTS_OCIEA_1);
	INTERRUPTS_vidPutISRFunction(vidToggleLED);
	INTERRUPTS_vidSetGlobalInterruptFlag();
	while(1);

	return 0;

}

void vidToggleLED(void) {
	u16Count++;
	if (u16Count == 32000) {
		TOGGLE_BIT(PORTD,5);
		u16Count == 0;
	}
}
