#include "Std_Types.h"
#include "Macros.h"
#include "DIO_interface.h"
#include "KEYPAD_interface.h"

void KEYPAD_vidInit(void) {
	DIO_vidSetPinDirection(ROW0_PORT,ROW0_PIN,DIO_OUTPUT);
	DIO_vidSetPinDirection(ROW1_PORT,ROW1_PIN,DIO_OUTPUT);
	DIO_vidSetPinDirection(ROW2_PORT,ROW2_PIN,DIO_OUTPUT);
	DIO_vidSetPinDirection(ROW3_PORT,ROW3_PIN,DIO_OUTPUT);

	DIO_vidSetPinDirection(COL0_PORT,COL0_PIN,DIO_INPUT);
	DIO_vidSetPinValue(COL0_PORT,COL0_PIN,STD_HIGH);
	DIO_vidSetPinDirection(COL1_PORT,COL1_PIN,DIO_INPUT);
	DIO_vidSetPinValue(COL1_PORT,COL1_PIN,STD_HIGH);
	DIO_vidSetPinDirection(COL2_PORT,COL2_PIN,DIO_INPUT);
	DIO_vidSetPinValue(COL2_PORT,COL2_PIN,STD_HIGH);
	DIO_vidSetPinDirection(COL3_PORT,COL3_PIN,DIO_INPUT);
	DIO_vidSetPinValue(COL3_PORT,COL3_PIN,STD_HIGH);
}

u8 x = 0;
u8 KEYPAD_u8GetKey(void) {
	DIO_vidSetPinValue(ROW0_PORT,ROW0_PIN,STD_LOW);
	DIO_vidSetPinValue(ROW1_PORT,ROW1_PIN,STD_HIGH);
	DIO_vidSetPinValue(ROW2_PORT,ROW2_PIN,STD_HIGH);
	DIO_vidSetPinValue(ROW3_PORT,ROW3_PIN,STD_HIGH);

	x = 0;
	x |= (DIO_u8GetPinValue(COL0_PORT,COL0_PIN) << 0);
	x |= (DIO_u8GetPinValue(COL1_PORT,COL1_PIN) << 1);
	x |= (DIO_u8GetPinValue(COL2_PORT,COL2_PIN) << 2);
	x |= (DIO_u8GetPinValue(COL3_PORT,COL3_PIN) << 3);

	switch(x) {
		case 0x07:
			return '/';
		case 0x0B:
			return 3;
		case 0x0D:
			return 2;
		case 0x0E:
			return 1;
	}
	/*2nd*/
	DIO_vidSetPinValue(ROW0_PORT,ROW0_PIN,STD_HIGH);
	DIO_vidSetPinValue(ROW1_PORT,ROW1_PIN,STD_LOW);
	DIO_vidSetPinValue(ROW2_PORT,ROW2_PIN,STD_HIGH);
	DIO_vidSetPinValue(ROW3_PORT,ROW3_PIN,STD_HIGH);

	x = 0;
	x |= (DIO_u8GetPinValue(COL0_PORT,COL0_PIN) << 0);
	x |= (DIO_u8GetPinValue(COL1_PORT,COL1_PIN) << 1);
	x |= (DIO_u8GetPinValue(COL2_PORT,COL2_PIN) << 2);
	x |= (DIO_u8GetPinValue(COL3_PORT,COL3_PIN) << 3);

	switch(x) {
		case 0x07:
			return '*';
		case 0x0B:
			return 6;
		case 0x0D:
			return 5;
		case 0x0E:
			return 4;
	}

	/*3d*/
	DIO_vidSetPinValue(ROW0_PORT,ROW0_PIN,STD_HIGH);
	DIO_vidSetPinValue(ROW1_PORT,ROW1_PIN,STD_HIGH);
	DIO_vidSetPinValue(ROW2_PORT,ROW2_PIN,STD_LOW);
	DIO_vidSetPinValue(ROW3_PORT,ROW3_PIN,STD_HIGH);

	x = 0;
	x |= (DIO_u8GetPinValue(COL0_PORT,COL0_PIN) << 0);
	x |= (DIO_u8GetPinValue(COL1_PORT,COL1_PIN) << 1);
	x |= (DIO_u8GetPinValue(COL2_PORT,COL2_PIN) << 2);
	x |= (DIO_u8GetPinValue(COL3_PORT,COL3_PIN) << 3);

	switch(x) {
		case 0x07:
			return '-';
		case 0x0B:
			return 9;
		case 0x0D:
			return 8;
		case 0x0E:
			return 7;
	}

	/*4th*/
	DIO_vidSetPinValue(ROW0_PORT,ROW0_PIN,STD_HIGH);
	DIO_vidSetPinValue(ROW1_PORT,ROW1_PIN,STD_HIGH);
	DIO_vidSetPinValue(ROW2_PORT,ROW2_PIN,STD_HIGH);
	DIO_vidSetPinValue(ROW3_PORT,ROW3_PIN,STD_LOW);

	x = 0;
	x |= (DIO_u8GetPinValue(COL0_PORT,COL0_PIN) << 0);
	x |= (DIO_u8GetPinValue(COL1_PORT,COL1_PIN) << 1);
	x |= (DIO_u8GetPinValue(COL2_PORT,COL2_PIN) << 2);
	x |= (DIO_u8GetPinValue(COL3_PORT,COL3_PIN) << 3);

	switch(x) {
		case 0x07:
			return '+';
		case 0x0B:
			return ',';
		case 0x0D:
			return 0;
		case 0x0E:
			return '#';
			
	}

	return 0xFF;
}
