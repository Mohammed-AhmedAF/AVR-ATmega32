#include "Std_Types.h"
#include "Macros.h"
#include "DIO_interface.h"
#include "UART_interface.h"
#include "PREPHIRALS_interface.h"

u8 u8UserInput;

void PREPHIRALS_vidChoosePrephiral(void) {
	do {
		UART_vidSendString("1.Motor 2.LED\r");
		u8UserInput = UART_u8ReceiveByte(); //Receiving user input
		if (u8UserInput == '1') { //Motor control
			UART_vidSendString("Motor\r");	
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
		if (u8UserInput == '1') { //Turn on LED
			DIO_vidSetPinValue(DIO_PORTA,DIO_PIN0,STD_HIGH);
		}
		else if (u8UserInput == '2') { //Turn off LED
			DIO_vidSetPinValue(DIO_PORTA,DIO_PIN0,STD_LOW);
		}
	}
	while(u8UserInput != '3'); //Will return the user to prephirals choice screen
	u8UserInput = 0;

}
void PREPHIRALS_vidInit(void) {
	DIO_vidSetPinDirection(DIO_PORTA,DIO_PIN0,DIO_OUTPUT);	
}
