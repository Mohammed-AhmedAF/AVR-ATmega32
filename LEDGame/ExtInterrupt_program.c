/*
 * ExtInterrupt_program.c
 *
 * Created: 9/23/2021 2:19:05 PM
 *  Author: Mohammed
 */ 
#include "Macros.h"
#include "Std_Types.h"
#include "ExtInterrupt_interface.h"
#include "ExtInterrupt_private.h"
#include <avr/interrupt.h>

/*Array holding pointer to functions, these function are executed when interrupts occur*/
void (*ptrFunc[3]) (void);

/*Enabling interrupt on pin change*/
void ExtInterrupt_vidEnablePinChangeInterrupt(u8 u8PinID)
{
	if (u8PinID < 8)
	{
	 SET_BIT(PCMSK0,u8PinID);
	}
	else if (u8PinID < 15)
	{
		SET_BIT(PCMSK1,u8PinID-8);
	}
	else
	{
		SET_BIT(PCMSK2,u8PinID-16);
	}
}

/*Enabling interrupt for port*/
void ExtInterrupt_vidEnableInterrupt(u8 u8InterruptID)
{
	switch(u8InterruptID)
	{
		case EXTINTER_PCINT0:
		SET_BIT(PCICR,EXTINTER_PCINT0);
		break;
		case EXTINTER_PCINT1:
		SET_BIT(PCICR,EXTINTER_PCINT1);
		break;
		case EXTINTER_PCINT2:
		SET_BIT(PCICR,EXTINTER_PCINT2);
		break;
	}
}

/*Use this function to select the function to be executed when an interrupt occurs*/
void ExtInterupt_vidRegisterCallback(u8 u8InterruptTrig,void (*ptFunc) (void))
{
	switch(u8InterruptTrig)
	{
		case EXTINTER_PCINT0:
		ptrFunc[EXTINTER_PCINT0] = ptFunc;
		break;
		case EXTINTER_PCINT1:
		ptrFunc[EXTINTER_PCINT1] = ptFunc;
		break;
		case EXTINTER_PCINT2:
		ptrFunc[EXTINTER_PCINT2] = ptFunc;
		break;
	}
}

/*Setting the global interrupt flag in SREG*/
void INTERRUPTS_vidSetGlobalInterruptFlag(void)
{
	SET_BIT(SREG,7);
}

ISR(PCINT2_vect) {
	ptrFunc[2]();
}