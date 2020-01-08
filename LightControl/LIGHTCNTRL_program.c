#include "LIGHTCNTRL_interface.h"

void vidControlLEDSet(void)
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

void vidDriveLEDSet(void)
{
		SPI_vidTransferByte(u8Set);
		IC74595_vidControl();
}

void vidGetLEDNumber(void) {
	u8Byte = UART_u8GetReceivedByte();
	vidControlLEDSet();
}
