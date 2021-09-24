/*
 * ExtInterrupt_interface.h
 *
 * Created: 9/23/2021 2:19:29 PM
 *  Author: Mohammed
 */ 


#ifndef EXTINTERRUPT_INTERFACE_H_
#define EXTINTERRUPT_INTERFACE_H_

void ExtInterrupt_vidEnablePinChangeInterrupt(u8 u8PinID);
void ExtInterupt_vidRegisterCallback(u8 u8InterruptTrig,void (*ptFunc) (void));
void INTERRUPTS_vidSetGlobalInterruptFlag(void);
void ExtInterrupt_vidEnableInterrupt(u8);

#define EXTINTER_PIN_0 0
#define EXTINTER_PIN_1 1
#define EXTINTER_PIN_2 2
#define EXTINTER_PIN_3 3
#define EXTINTER_PIN_4 4
#define EXTINTER_PIN_5 5
#define EXTINTER_PIN_6 6
#define EXTINTER_PIN_7 7
#define EXTINTER_PIN_8 8
#define EXTINTER_PIN_9 9
#define EXTINTER_PIN_10 10
#define EXTINTER_PIN_11 11
#define EXTINTER_PIN_12 12
#define EXTINTER_PIN_13 13
#define EXTINTER_PIN_14 14
#define EXTINTER_PIN_15 15
#define EXTINTER_PIN_16 16
#define EXTINTER_PIN_17 17
#define EXTINTER_PIN_18 18
#define EXTINTER_PIN_19 19
#define EXTINTER_PIN_20 20
#define EXTINTER_PIN_21 21
#define EXTINTER_PIN_22 22
#define EXTINTER_PIN_23 23
#define EXTINTER_PIN_24 24
#define EXTINTER_PIN_25 25
#define EXTINTER_PIN_26 26
#define EXTINTER_PIN_27 27

#define EXTINTER_PCINT0 0
#define EXTINTER_PCINT1 1
#define EXTINTER_PCINT2 2

#endif /* EXTINTERRUPT_INTERFACE_H_ */