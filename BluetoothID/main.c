#include "Std_Types.h"
#include "Macros.h"
#include "DIO_interface.h"
#include "UART_interface.h"
#include "PASSWORD_interface.h"
#include "EEPROM_interface.h"

extern u8 u8PasswordMatch;
void vidInit(void);

int main(void) {
	vidInit();
	while(1) {
		PASSWORD_vidRegisterID();
		PASSWORD_vidGetID();
		PASSWORD_vidRegisterPassword();
		if (u8PasswordMatch == 1) {
			UART_vidSendString("Saving..\r");
			PASSWORD_vidSaveData();
		}
	}
}

void vidInit(void) {
	UART_vidInit();
	EEPROM_vidInit();
}

