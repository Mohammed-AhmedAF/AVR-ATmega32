#include "Std_Types.h"
#include "Macros.h"
#include "UART_interface.h"
#include <avr/io.h>


void UART_vidInit(u8 u8Parity,u8 u8CharSize,u8 u8StopBits) {

	//Setting Transmit/Receive Enable
	SET_BIT(UCSRB,4); //Receiver Enable bit
	SET_BIT(UCSRB,3); //Transmit Enable bit


	if (u8Parity == UART_PARITY_EVEN) {
		CLEAR_BIT(UCSRC,4);
		SET_BIT(UCSRC,5);
	}
	else if (u8Parity == UART_PARITY_ODD) {
		SET_BIT(UCSRC,4);
		SET_BIT(UCSRC,5);
	}
	else if (u8Parity == UART_PARITY_DISABLED) {
		CLEAR_BIT(UCSRC,4);
		CLEAR_BIT(UCSRC,5);
	}

	//Size of data sent/received
	if (u8CharSize == UART_CSIZE_5) {
		CLEAR_BIT(UCSRC,1);
		CLEAR_BIT(UCSRC,2);
		CLEAR_BIT(UCSRB,2);
	}
	else if (u8CharSize == UART_CSIZE_6) {
		SET_BIT(UCSRC,1);
		CLEAR_BIT(UCSRC,2);
		CLEAR_BIT(UCSRB,2);
	}
	else if (u8CharSize == UART_CSIZE_7) {
		CLEAR_BIT(UCSRC,1);
		SET_BIT(UCSRC,2);
		CLEAR_BIT(UCSRB,2);
	}
	else if (u8CharSize == UART_CSIZE_8) {
		SET_BIT(UCSRC,1);
		SET_BIT(UCSRC,1);
		CLEAR_BIT(UCSRB,2);
	}
	else if (u8CharSize == UART_CSIZE_9) {
		SET_BIT(UCSRC,1);
		SET_BIT(UCSRC,1);
		SET_BIT(UCSRB,2);
	}

	//Number of stop bits
	if (u8StopBits == UART_STOPBITS_1) {
		CLEAR_BIT(UCSRC,3);
	}
	else if (u8StopBits == UART_STOPBITS_2) {
		SET_BIT(UCSRC,3);
	}
	
	//Clock polarity
	if (u8ClockPolarity == UART_CLKPOLARITY_RISING) {
		CLEAR_BIT(UCSRC,0);
	}
	else if (u8ClockPolarity == UART_CLKPOLARITY_FALLING) {
		SET_BIT(UCSRC,0);
	}
}

void UART_vidSendByte(u8 u8byteCpy) {
	while(GET_BIT(UCSRA,5) == 0);
	UDR = u8byteCpy;
}

void UART_vidReceiveByte(void) {
	while (GET_BIT(UCSRA,7) == 0);
	return UDR;
}
