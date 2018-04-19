/**
 * Author: Mohammed Ahmed Abd Al-Fattah Mahmoud
 * Project: Remaking keypad driver
 *
 */

#include "Std_Types.h"
#include "Macros.h"
#include "DIO_interface.h"
#include "LCD_interface.h"
#include "KEYPAD_interface.h"
#include "SERVICES_interface.h"

void main(void) {
	LCD_vidInit();
	KEYPAD_vidInit();

	while(1) {
		SERVICES_vidWriteCharacter();		
	}

}
