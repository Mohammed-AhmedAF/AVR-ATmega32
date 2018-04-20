#include "Std_Types.h"
#include "Macros.h"
#include "DIO_interface.h"
#include "LCD_interface.h"

u8 i = 0;
int main(void) {
	LCD_vidInit();

	u8 b[8] = { 0x04,
	  0x0E,
	  0x15,
	  0x04,
	  0x04,
	  0x15,
	  0x0E,
	  0x04};
	LCD_vidSendCommand(0x40);
	while(i != 8) {	
		LCD_vidWriteCharacter(b[i]);	
		i++;
	} 
	LCD_vidSendCommand(0b10000000); //Setting address to DDRAM
	LCD_vidWriteCharacter(0x00); // Selecting the first special character
	while(1);
}
