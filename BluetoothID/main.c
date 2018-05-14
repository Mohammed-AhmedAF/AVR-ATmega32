/*
 * Author: Mohammed Ahmed Abd Al-Fattah
 * File: main.c
 * 
 */


#include "Std_Types.h"
#include "Macros.h"
#include "DIO_interface.h"
#include "UART_interface.h"
#include "PASSWORD_interface.h"
#include "EEPROM_interface.h"

extern u8 u8PasswordMatch;
u8 u8UserChoice = 0;
void vidInit(void);

int main(void) {
	vidInit();
	while(1) {
		UART_vidSendString("1) Show ID, 2) Register ID, 3) Show count");
		UART_vidSendString("4) Erase data 5) Login");
		UART_vidSendByte('\r');
		u8UserChoice = UART_u8ReceiveByte(); //Receiving user choice
		switch(u8UserChoice){
			case '1': //Show ID
				PASSWORD_vidShowData();
				break;
			case '2': //Register ID
				PASSWORD_vidRegisterID();
				PASSWORD_vidGetID();
				PASSWORD_vidRegisterPassword();
				if (u8PasswordMatch == 1) {
					UART_vidSendString("Saving..\r");
					PASSWORD_vidSaveData();
				}
				break;
			case '3': //Show currently registered users
				PASSWORD_vidShowRegUsersCount();
				break;
			case '4':
				PASSWORD_vidEraseData();
				break;
			case '5': //Login
				PASSWORD_vidLogin();
				break;
			default:
				UART_vidSendString("Invalid choice\r");
		}
	}
	return 0;
}

void vidInit(void) {
	UART_vidInit();
	EEPROM_vidInit();
}

