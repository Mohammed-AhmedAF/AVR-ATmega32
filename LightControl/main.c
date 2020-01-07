#include "SETTINGS_interface.h"
#include "Std_Types.h"
#include "Macros.h"
#include "DIO_interface.h"
#include "SPI_interface.h"
#include "IC74595_interface.h"
#include "UART_interface.h"
#include "INTERRUPTS_interface.h"

void vidDriveLEDSet(void);
void vidGetLEDNumber(void);

volatile u8 u8Set = 0;
volatile u8 u8Byte = 0;
u8 u8LEDNumber = 0;
	
void main(void)
{
	UART_vidInit();

	INTERRUPTS_vidEnableInterrupt(INTERRUPTS_USART_RXC);
	INTERRUPTS_vidPutISRFunction(INTERRUPTS_USART_RXC,vidGetLEDNumber);
	INTERRUPTS_vidSetGlobalInterruptFlag();
	
	SPI_vidInitMaster();
	
	
	IC74595_vidInit();	

	
	while(1) {

		SPI_vidTransferByte(u8Set);
		IC74595_vidControl();
	}
}

void vidDriveLEDSet(void)
{
	
	switch (u8Byte)
	{
		case 'a':
			u8LEDNumber = 0;
			break;
		case 'b':
			u8LEDNumber = 1;
			break;
		case 'c':
			u8LEDNumber = 2;
			break;
		case 'd':
			u8LEDNumber = 3;
			break;
		case 'e':
			u8LEDNumber = 4;
			break;
		case 'f':
			u8LEDNumber = 5;
			break;
		case 'g':
			u8LEDNumber = 6;
			break;
		case 'h':
			u8LEDNumber = 7;
			break;
	}

	TOGGLE_BIT(u8Set,u8LEDNumber);

}

void vidGetLEDNumber(void) {
	u8Byte = UART_u8GetReceivedByte();
	vidDriveLEDSet();
}
