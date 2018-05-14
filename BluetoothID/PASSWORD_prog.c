/*
 * Author: Mohammed Ahmed Abd Al Fattah Mahmoud
 * File: PASSWORD_prog.c
 * 
 */

#include "Std_Types.h"
#include "Macros.h"
#include "PASSWORD_interface.h"
#include "UART_interface.h"
#include "EEPROM_interface.h"
#include "TWI_interface.h"

u8 u8ID[10];
u8 i;
u8 element;
u8 u8Password[10];
u8 u8PasswordRe[10];
u8 u8Flag = 0;
u8 u8PasswordMatch = 0;
u8 u8UserCount = 0;
u8 u8ID_index = 0;
u8 u8Password_index = 0;
u8 u8RegisteredUsersCount = '0';

void PASSWORD_vidRegisterID(void) {
	UART_vidSendString("Enter ID (3 digits): \r");
	for (i = 0; i < PASSWORD_ID_SIZE; i++) {
		element = UART_u8ReceiveByte();
		u8ID[i] = element;
	}
}

void PASSWORD_vidRegisterPassword(void) {

	UART_vidSendString("Password (4 digits): \r");
	for (i = 0; i < PASSWORD_PASSWORD_SIZE; i++) {
		element = UART_u8ReceiveByte();
		u8Password[i] = element;
	}

	UART_vidSendString("Re-enter password: \r");
	for (i = 0; i < PASSWORD_PASSWORD_SIZE; i++) {
		element = UART_u8ReceiveByte();
		u8PasswordRe[i] = element;
	}

	//Check password match
	for (i = 0; i < PASSWORD_PASSWORD_SIZE; i++) {
		if (u8Password[i] != u8PasswordRe[i]) {
			UART_vidSendString("Passwords don't match.\r");
			break;
		}
		else if ((i == PASSWORD_PASSWORD_SIZE-1) && (u8Password[i] == u8Password[i])) {
			UART_vidSendString("Password match.\r");
			u8PasswordMatch = 1;
		}
	}
}

void PASSWORD_vidGetID(void) {
	UART_vidSendString("ID is ");
	for (i = 0; i < PASSWORD_ID_SIZE; i++) {
		UART_vidSendByte(u8ID[i]);
	}
	UART_vidSendByte('\r');
}

void PASSWORD_vidSaveData(void) {
	EEPROM_u8ReadByte(PASSWORD_REGISTERED_USERS,&u8RegisteredUsersCount);
	u8 u8Password_index = PASSWORD_PASSWORD_START+PASSWORD_ID_SIZE*u8RegisteredUsersCount;

	u8 u8ID_index = PASSWORD_ID_START+PASSWORD_PASSWORD_SIZE*u8RegisteredUsersCount;
	//Store ID
	u8 u8ID_element, u8Password_element;
	/*Saving ID*/
	for (i = 0; i < PASSWORD_ID_SIZE; i++) {
		u8ID_element = u8ID[i];
		u8Flag = EEPROM_u8WriteByte(u8ID_index+i,u8ID_element);
		if (u8Flag == 1) {
			UART_vidSendString("!\r");
		}
		else {
			UART_vidSendString("?\r");
		}
	}
	/*Saving password*/
	for (i = 0; i < PASSWORD_PASSWORD_SIZE; i++) {
		u8Password_element = u8Password[i];
		u8Flag = EEPROM_u8WriteByte(u8Password_index+i,u8Password[i]);
		if (u8Flag == 1) {
			UART_vidSendString("!\r");
		}
		else {
			UART_vidSendString("?\r");	
		}
	}
	u8Flag = EEPROM_u8ReadByte(PASSWORD_REGISTERED_USERS,&u8RegisteredUsersCount);
	if (u8Flag == 1) {
		UART_vidSendString("User count is ");
		u8RegisteredUsersCount +=1;
		UART_vidSendByte(u8RegisteredUsersCount+'0');

		//Storing the current number of registered users
		u8Flag = EEPROM_u8WriteByte(PASSWORD_REGISTERED_USERS,u8RegisteredUsersCount);
		if (u8Flag == 1) {
			UART_vidSendString("!\r");
		}	
		else {
			UART_vidSendString("!\r");
		}

	}
	else {
		UART_vidSendString("?\r");
	}
}

//Asking for ID after registration
//This function will be called by control logic in main
void PASSWORD_vidAskID(void) {
	UART_vidSendString("ID: (3 digits)");
}

//Shows the number of registered users
void PASSWORD_vidShowRegUsersCount(void) {
	u8 u8test = 0;
	u8Flag = EEPROM_u8ReadByte(PASSWORD_REGISTERED_USERS,&u8RegisteredUsersCount);
	//Can't view the registeredUsersCount
	if (u8Flag == 1) {
		u8test = u8RegisteredUsersCount;
		UART_vidSendByte(u8test+'0');
		UART_vidSendByte('\r');
	}
	else {
		UART_vidSendString("Error reading count");
	}
}

void PASSWORD_vidShowID(u8 u8UsersCountCpy) {
	u8UserCount = 0;
	u8 u8id_element;
	do {
		u8ID_index = PASSWORD_ID_START+PASSWORD_ID_SIZE*u8UserCount;
		for (i = 0; i < PASSWORD_ID_SIZE; i++) {
			EEPROM_u8ReadByte(u8ID_index+i,&u8id_element);
			UART_vidSendByte(u8id_element);
		}
		UART_vidSendByte('\r');
		u8UserCount++;
	}while(u8UserCount <  u8UsersCountCpy);
}

void PASSWORD_vidShowPassword(u8 u8UsersCountCpy) {
	u8UserCount = 0;
	u8 u8Password_element;
	do {
		u8Password_index = PASSWORD_PASSWORD_START+PASSWORD_PASSWORD_SIZE*u8UserCount;
		for (i = 0; i < PASSWORD_PASSWORD_SIZE; i++) {
			EEPROM_u8ReadByte(u8Password_index+i,&u8Password_element);
			UART_vidSendByte(u8Password_element);		
		}
		UART_vidSendByte('\r');
		u8UserCount++;
	}while (u8UserCount < u8UsersCountCpy);
}

void PASSWORD_vidShowData(void) {
	EEPROM_u8ReadByte(PASSWORD_REGISTERED_USERS,&u8RegisteredUsersCount);
	if (u8RegisteredUsersCount != 0) {
		PASSWORD_vidShowID(u8RegisteredUsersCount);
		PASSWORD_vidShowPassword(u8RegisteredUsersCount);
	}
	else {
		UART_vidSendString("No registered users.\r");
	}
}

void PASSWORD_vidEraseData(void) {
	//Resetting user count
	u8Flag = EEPROM_u8WriteByte(PASSWORD_REGISTERED_USERS,0);	
	if (u8Flag == 1) {
		UART_vidSendString("Resetting user count.\r");
	}
	else {
		UART_vidSendString("Error resetting user count.\r");
	}

}
