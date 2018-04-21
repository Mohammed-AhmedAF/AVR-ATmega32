#include "Std_Types.h"
#include "Macros.h"
#include "DIO_interface.h"
#include "LCD_interface.h"

void LCD_vidCreateCustomChar(u8 *,u8);
void LCD_vidWriteCustomChar(u8);
u8 i = 0;
int main(void) {
	LCD_vidInit();

	u8 b[8] = {  0x0E,
		0x08,
		0x0E,
		0x04,
		0x04,
		0x04,
		0x04,
		0x04};

	u8 c[8] = {
		0x04,
		0x15,
		0x0A,
		0x04,
		0x0A,
		0x15,
		0x04,
		0x04,
	};

	LCD_vidCreateCustomChar(b,0);
	LCD_vidCreateCustomChar(c,1);
	LCD_vidSendCommand(0x80);
	LCD_vidWriteCharacter(' ');
	LCD_vidWriteCustomChar(0);
	LCD_vidWriteCustomChar(1);
	while(1);
}

void LCD_vidWriteCustomChar(u8 u8LocationCpy) {
	LCD_vidWriteCharacter(0x00+u8LocationCpy);
}

void LCD_vidCreateCustomChar(u8 * u8CharPtrCpy, u8 u8LocationCpy) {
	u8 i = 0;
	LCD_vidSendCommand(0x40+(u8LocationCpy*8)); //Setting to CGRAM address
	while (i != 8) {
		LCD_vidWriteCharacter(*u8CharPtrCpy++);
		i++;
	}
	LCD_vidWriteCharacter(0x00+u8LocationCpy);
}
