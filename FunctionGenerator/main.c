/*
 * Author: Mohamed Ahmed Abd Al-Fattah
 * Purpose: Function generator
 * */

#include "Std_Types.h"
#include "Macros.h"
#include "DIO_private.h"
#include "DIO_interface.h"
#include "TIMER0_interface.h"
#include "INTERRUPTS_interface.h"

/*Macro functions that help the programmer understand code*/
/*I am using a PNP transistor so the BASE is off when current flows into it*/
#define BASE_OFF(PORT,PIN) SET_BIT(PORT,PIN)
#define BASE_ON(PORT,PIN) CLEAR_BIT(PORT,PIN)

#define UP 1
#define DOWN 0

void vidCount(void);

volatile u32 u32OVFCount;
volatile u8 u8Flag;
volatile u8 u8DownCount;

void main(void) {
	/*Initiation*/
	u32OVFCount = 0;
	u8Flag = UP;
	u8DownCount = 0;

	DIO_vidSetPinDirection(DIO_PORTA,DIO_PIN0,DIO_OUTPUT);

	TIMER0_vidInit(TIMER0_WGM_NORMAL,TIMER0_COM_NORMAL,TIMER0_CLK_1);

	INTERRUPTS_vidSetInterruptEnable(INTERRUPTS_TOIE_0);
	INTERRUPTS_vidPutISRFunction(vidCount);
	INTERRUPTS_vidSetGlobalInterruptFlag();

	while(1);
}

/*50% Duty cycle*/
void vidCount(void) {
	u32OVFCount++;
	if (u32OVFCount == 40) {
		if (u8Flag == UP) {
			BASE_OFF(PORTA,DIO_PIN0);
			u8DownCount++;
			if (u8DownCount == 14) {
				u8Flag = DOWN;
				u8DownCount = 0;
			}
		}
		else {
			u8Flag = UP;
			BASE_ON(PORTA,DIO_PIN0);
		}
		u32OVFCount = 0;
	}
}
