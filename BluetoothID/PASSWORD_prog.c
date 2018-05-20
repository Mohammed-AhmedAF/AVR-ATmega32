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
u8 i,j;
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

	UART_vidSendString("Saving..\r");
	//Loading userCount to be used for indexing the ID and password being saved
	EEPROM_u8ReadByte(PASSWORD_REGISTERED_USERS,&u8RegisteredUsersCount);
	u8 u8Password_index = PASSWORD_PASSWORD_START+PASSWORD_PASSWORD_SIZE*u8RegisteredUsersCount;

	u8 u8ID_index = PASSWORD_ID_START+PASSWORD_ID_SIZE*u8RegisteredUsersCount;
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
			UART_vidSendString("?\r");
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
		UART_vidSendString("User count is ");
		UART_vidSendByte(u8test+'0');
		UART_vidSendByte('\r');
	}
	else {
		UART_vidSendString("Error reading count\r");
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
void PASSWORD_vidLogin(void) {
	u8 u8UserIndex;
	u8UserIndex = PASSWORD_u8AskID();
	if (u8UserIndex != -1) { //User ID is registered
		PASSWORD_u8AskPassword(u8AskIDSuccess);
	}
}

u8 PASSWORD_u8AskID(void) {
	//Displaying a message
	EEPROM_u8ReadByte(PASSWORD_REGISTERED_USERS,&u8RegisteredUsersCount);
	u8 u8ID_entered[PASSWORD_ID_SIZE];
	//Ask user for ID
	UART_vidSendString("ID:  \r");
	for (i = 0; i < PASSWORD_ID_SIZE; i++) {
		u8ID_entered[i] = UART_u8ReceiveByte();
	}
	for (i = 0; i < u8RegisteredUsersCount;i++) {
		//Loading ID from EEPROM
		u8ID_index = PASSWORD_ID_START + PASSWORD_ID_SIZE*i;
		for (j = 0; j < PASSWORD_ID_SIZE; j++) {
			EEPROM_u8ReadByte(u8ID_index+j,&u8ID[j]);
		}
		//Checking entered ID with ID loaded from EEPROM
		for (j = 0; j < PASSWORD_ID_SIZE; j++) {
			if (u8ID[j] != u8ID_entered[j]) {
				break;
			}
			if (u8ID[PASSWORD_ID_SIZE-1] == u8ID_entered[PASSWORD_ID_SIZE-1]) {
				UART_vidSendString("ID found\r");	
				return i; //Return the ID index
			}
		}
	}
	UART_vidSendString("ID not found\r");
	return PASSWORD_IDNOTFOUND;
}

u8 PASSWORD_u8AskPassword(u8 u8UserIndexCpy) { 
	u8 u8PasswordChar_registered;
	//Asking user to enter password
	UART_vidSendString("Password: \r");
	for (i = 0; i < PASSWORD_PASSWORD_SIZE; i++) {
		u8Password[i] = UART_u8ReceiveByte();					
	}
	//Comparing the entered password to registered password
	u8Password_index = PASSWORD_PASSWORD_START + PASSWORD_PASSWORD_SIZE*u8UserIndexCpy;
	for (i = 0; i < PASSWORD_PASSWORD_SIZE; i++) {
		EEPROM_u8ReadByte(u8Password_index+i,&u8PasswordChar_registered);
		if (u8Password[i] != u8PasswordChar_registered) {
			UART_vidSendString("Wrong password\r");
			return PASSWORD_WRONGPASSWORD;
		}
		else if (u8Password[PASSWORD_PASSWORD_SIZE-1]==u8PasswordChar_registered) {
			UART_vidSendString("Login successful\r");
			return PASSWORD_CORRECTPASSWORD;
		}
	}
}
