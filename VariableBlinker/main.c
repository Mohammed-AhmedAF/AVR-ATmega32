#include "Macros.h"
#include "Std_Types.h"
#include "DIO_interface.h"
#include <avr/io.h>
#include <avr/interrupt.h>

u16 u16count = 0;
void main(void) {

	DIO_vidSetPinDirection(DIO_PORTB,DIO_PIN3,DIO_OUTPUT);

	/*Timer initiation*/
	/*Timer counter register configuration*/
	SET_BIT(TCCR0,0);
	CLEAR_BIT(TCCR0,1);
	CLEAR_BIT(TCCR0,2);

	/*Setting waveform*/
	CLEAR_BIT(TCCR0,3);
	CLEAR_BIT(TCCR0,6);

	/*Compare output mode*/
	CLEAR_BIT(TCCR0,4);
	CLEAR_BIT(TCCR0,5);

	/*Setting interrupt*/
	SET_BIT(SREG,7);  /*Global interrupt enable*/
	SET_BIT(TIMSK,0); /*Timer overflow enable*/
	
	while(1);
}

ISR(TIMER0_OVF_vect) {
	u16count++;
	if (u16count == 30000) {
		TOGGLE_BIT(PORTB,DIO_PIN3);
		u16count = 0;
	}
}
