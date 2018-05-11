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
		UART_vidSendString("1) Enter ID, 2) Register ID, 3) Show count\r");
		switch(UART_u8ReceiveByte()){
			case '1':
				PASSWORD_vidAskID();
				break;
			case '2':
				PASSWORD_vidRegisterID();
				PASSWORD_vidGetID();
				PASSWORD_vidRegisterPassword();
				if (u8PasswordMatch == 1) {
					UART_vidSendString("Saving..\r");
					PASSWORD_vidSaveData();
				}
				break;
			case '3':
				PASSWORD_vidShowRegUsersCount();
				break;
		}
	}
}
void vidInit(void) {
	UART_vidInit();
	EEPROM_vidInit();
}

