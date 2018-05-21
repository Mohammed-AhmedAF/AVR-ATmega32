#include "Std_Types.h"
#include "Macros.h"
#include "DIO_interface.h"
#include "UART_interface.h"
#include "PREPHIRALS_interface.h"
#include "TIMER1_interface.h"

u16 u16Speeds_Array[6] = {700,600,500,400,300,200};
u8 u8UserInput;

void PREPHIRALS_vidChoosePrephiral(void) {
	do {
		UART_vidSendString("1.Motor 2.LED\r");
		u8UserInput = UART_u8ReceiveByte(); //Receiving user input
		if (u8UserInput == '1') { //Motor control
			PREPHIRALS_vidControlMotor();	
		}
		else if (u8UserInput == '2') { //LED control
			PREPHIRALS_vidControlLED();
		}
		else  {
			UART_vidSendString("Invalid choice\r");	
		}
	}
	while(u8UserInput != '3'); //Will return the user to the main screen
}

void PREPHIRALS_vidControlLED(void) {
	UART_vidSendString("1. Turn on.\r");
	UART_vidSendString("2. Turn off.\r");
	do {
		u8UserInput = UART_u8ReceiveByte();
		if (u8UserInput == PREPHIRALS_LEDON) { //Turn on LED
			DIO_vidSetPinValue(DIO_PORTA,DIO_PIN0,STD_HIGH);
		}
		else if (u8UserInput == PREPHIRALS_LEDOFF) { //Turn off LED
			DIO_vidSetPinValue(DIO_PORTA,DIO_PIN0,STD_LOW);
		}
	}
	while(u8UserInput != '3'); //Will return the user to prephirals choice screen
	u8UserInput = 0;

}

void PREPHIRALS_vidControlMotor(void) {
	do {
		u8UserInput = UART_u8ReceiveByte();
		if (u8UserInput == '1') {
			TIMER1_vidSetOCRA(u16Speeds_Array[0]);
		}
		else if (u8UserInput == '2') {
			TIMER1_vidSetOCRA(u16Speeds_Array[1]);
		}
		else if (u8UserInput == '3') {
			TIMER1_vidSetOCRA(u16Speeds_Array[2]);
		}
		else if (u8UserInput == '4') {
			TIMER1_vidSetOCRA(u16Speeds_Array[3]);
		}
		else if (u8UserInput == '5') {
			TIMER1_vidSetOCRA(u16Speeds_Array[4]);
		}
		else if (u8UserInput == '6') {
			TIMER1_vidSetOCRA(u16Speeds_Array[5]);
		}
	}while(u8UserInput != '9');	
}

void PREPHIRALS_vidInit(void) {
	DIO_vidSetPinDirection(DIO_PORTA,DIO_PIN0,DIO_OUTPUT);	
	DIO_vidSetPinDirection(DIO_PORTD,DIO_PIN5,DIO_OUTPUT); //Output pin for OC1A
	TIMER1_vidInit(TIMER1_WGM_FPWM_OCR,TIMER1_COM1A_CLEAR,TIMER1_COM1B_NORMAL,TIMER1_CLK_1);
	TIMER1_vidSetOCRA(600);

}
