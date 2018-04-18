/*
 * Author: Mohammed Ahmed Abd Al-Fattah Mahmoud Kamel
 * File: main.c
 */

#include "Std_Types.h"
#include "Macros.h"
#include "LCD_interface.h"
#include "KEYPAD_interface.h"
#include "SERVICES_interface.h"

int main(void) {
	LCD_vidInit();
	LCD_vidSendCommand(LCD_CLEAR_SCREEN);
	LCD_vidWriteCharacter('W');
	KEYPAD_vidInit();

	while(1) {
		SERVICES_vidWriteCharacter();
	}
}
