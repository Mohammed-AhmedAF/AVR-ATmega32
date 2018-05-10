#ifndef _PASSWORD_INTERFACE_H
#define _PASSWORD_INTERFACE_H


#define PASSWORD_PASSWORD_SIZE 4
#define PASSWORD_ID_SIZE 3

void PASSWORD_vidGetID(void);
void PASSWORD_vidRegisterID(void);
void PASSWORD_vidRegisterPassword(void);
void PASSWORD_vidSaveData(void);
void PASSWORD_vidAskID(void);

#endif
