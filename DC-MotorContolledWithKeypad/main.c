
/* Name: Mohamed Ahmed Abd Al-Fattah Mahmoud
 * Date: 4-4-2018 (First completion)
 * Update: Make a DC motor speed controller using
 * keypad and LCD.
 */

#include "Std_Types.h"
#include "Macros.h"
#include "DIO_interface.h"
#include "LCD_interface.h"
#include "KEYPAD_interface.h"
#include "SERVICES_interface.h"
#include "INTERRUPTS_interface.h"
#include "TIMER1_interface.h"

void vidInit(void);
void vidSelectSpeed(void);

u16 u16Count;
u16 u16Speeds_Array[5] = {700,600,500,400,300};
void (*ptrFunc) (void);

int main(void) {	
	LCD_vidInit();
	KEYPAD_vidInit();
	vidInit();

	while(1) {
		vidSelectSpeed();	
	}
	return 0;
}

void vidInit(void) {
	DIO_vidSetPinDirection(DIO_PORTD,DIO_PIN5,DIO_OUTPUT); //Output pin for OC1A
	TIMER1_vidInit(TIMER1_WGM_FPWM_OCR,TIMER1_COM1A_CLEAR,TIMER1_COM1B_NORMAL,TIMER1_CLK_1);
	TIMER1_vidSetOCRA(600);
}

void vidSelectSpeed(void) {
	do {
		SERVICES_vidWriteCharacter(1);
		if (u8keyPressed == '1') {
			TIMER1_vidSetOCRA(u16Speeds_Array[0]);
		}
		else if (u8keyPressed == '2') {
			TIMER1_vidSetOCRA(u16Speeds_Array[1]);
		}
		else if (u8keyPressed == '3') {
			TIMER1_vidSetOCRA(u16Speeds_Array[2]);
		}
		else if (u8keyPressed == '4') {
			TIMER1_vidSetOCRA(u16Speeds_Array[3]);
		}
		else if (u8keyPressed == '5') {
			TIMER1_vidSetOCRA(u16Speeds_Array[4]);
		}
	}while(1);
	//TIMER1_vidSetOCRA(u16Speads_Array[4]);
}
