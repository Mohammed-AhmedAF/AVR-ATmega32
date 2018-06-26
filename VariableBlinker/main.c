#include "Macros.h"
#include "Std_Types.h"
#include "DIO_interface.h"
#include <avr/io.h>
#include <avr/interrupt.h>

u16 u16count = 0;
u16 u16topCount = 0;
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

	/*External interrupt*/
	SET_BIT(GICR,6); //External interrupt request enable

	/*Interrupt sense control*/
	CLEAR_BIT(MCUCR,0);  /*Low level generates interrupt request*/
	CLEAR_BIT(MCUCR,1); 
	
	while(1);
}

ISR(TIMER0_OVF_vect) {
	u16count++;
	if (u16count == u16topCount) {
		TOGGLE_BIT(PORTB,DIO_PIN3);
		u16count = 0;
	}
}

//ISR for external interrupt 0;
ISR(INT0_vect) {
	if(u16topCount == 10000) {
		u16topCount = 30000;
	}
	else {
		u16topCount = 10000;
	}
}
