#ifndef _PASSWORD_INTERFACE_H
#define _PASSWORD_INTERFACE_H


#define PASSWORD_PASSWORD_SIZE 4
#define PASSWORD_ID_SIZE 3
#define PASSWORD_PASSWORD_START 50 //The address of the first character in the first password
#define PASSWORD_ID_START 10
void PASSWORD_vidGetID(void);
void PASSWORD_vidRegisterID(void);
void PASSWORD_vidRegisterPassword(void);
void PASSWORD_vidSaveData(void);
void PASSWORD_vidAskID(void);

#endif