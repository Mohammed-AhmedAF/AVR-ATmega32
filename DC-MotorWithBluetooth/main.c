
/*Name: Mohamed Ahmed Abd Al-Fattah Mahmoud
 * Date: 28-4-2018 (First completion)
 * Update: Make a DC motor speed controller with Bluetooth.
 * There are six speeds (1,2,3,4,5,6).
 * Send the key corresponding to the speed to make
 * the DC motor rotate on that spead.
 */

#include "Std_Types.h"
#include "Macros.h"
#include "DIO_interface.h"
#include "INTERRUPTS_interface.h"
#include "TIMER1_interface.h"
#include "UART_interface.h"

void vidInit(void);
void vidSelectSpeed(void);

u16 u16Speeds_Array[6] = {700,600,500,400,300,200};
u8 u8keyPressed;

int main(void) {	
	vidInit();
	while(1) {
		vidSelectSpeed();	
	}
	return 0;
}

void vidInit(void) {
	/*Timer Initiation*/
	DIO_vidSetPinDirection(DIO_PORTD,DIO_PIN5,DIO_OUTPUT); //Output pin for OC1A
	TIMER1_vidInit(TIMER1_WGM_FPWM_OCR,TIMER1_COM1A_CLEAR,TIMER1_COM1B_NORMAL,TIMER1_CLK_1);
	TIMER1_vidSetOCRA(600);
	/*UART initiation*/
	UART_vidInit();
}

void vidSelectSpeed(void) {
	do {
		u8keyPressed = UART_u8ReceiveByte();
		switch(u8keyPressed) {
			case '1':
				TIMER1_vidSetOCRA(u16Speeds_Array[0]);
				break;
			case '2':
				TIMER1_vidSetOCRA(u16Speeds_Array[1]);
				break;
			case '3':
				TIMER1_vidSetOCRA(u16Speeds_Array[2]);
				break;
			case '4':
				TIMER1_vidSetOCRA(u16Speeds_Array[3]);
				break;
			case '5':
				TIMER1_vidSetOCRA(u16Speeds_Array[4]);
				break;
			case '6':
				TIMER1_vidSetOCRA(u16Speeds_Array[5]);
				break;
			case '7':
				TIMER1_vidSetOCRA(u16Speeds_Array[6]);
				break;
		}	
	}while(1);
}
