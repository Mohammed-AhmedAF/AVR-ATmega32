/*Explaining flow of code in this file*/
/*
After including driver files, defining function prototypes.
1. Pin direction is set for pins connected to LEDS.
2. LEDs are turned-on by setting the value of pin to STD_HIGH.
3. The direction of pins connected to switches is set as input.
4. A callback function is registered so that it is executed when the interrupt occurs.
5. The interrupt PCINT2 is enabled.
6. Enabling interrupt on pin change.
7. Setting global interrupt flag in SREG.
8. Inside the while loop, the condition for winning is checked.
*/
#include <avr/io.h>
#include "Std_Types.h"
#include "Macros.h"
/*DIO driver used to control LEDs and configure switch pins*/
#include "DIO_interface.h"
/*The delay library is used for making delays, used when the winning combination is achieved*/
/*to blink the LEDs*/
#include <avr/delay.h>
/*Settings: Define macros used to define the correct address of registers*/
#include "SETTINGS_interface.h"
/*Library used to control external interrupt*/
#include "ExtInterrupt_interface.h"

/*Function prototypes*/
void vidBlink(void);
void vidToggleAdjoining(u8);
void vidRunnWinningSequence(void);

/*u8LEDState: Used to hold led states*/
volatile u8 u8LEDState;

/*Macros defining switches*/
/*The hexadecimal value corresponds to the pin on port B*/
#define SW0 0x01
#define SW1 0x02
#define SW2 0x04
#define SW3 0x08
#define SW4 0x10
#define SW5 0x20
#define SW6 0x40
#define SW7 0x80

/*This function is to toggle the adjoining*/
/*It takes the led number corresponding to the pressed switch*/
void vidToggleAdjoining(u8 u8Current)
{
	/*Switched 0 and 7 are a special case*/
	if (u8Current == 0)
	{
		DIO_vidTogglePin(DIO_PORTB,u8Current+1);
		DIO_vidTogglePin(DIO_PORTB,7);
	}
	else if (u8Current == 7)
	{
		DIO_vidTogglePin(DIO_PORTB,u8Current-1);
		DIO_vidTogglePin(DIO_PORTB,0);
	}
	else
	{
		DIO_vidTogglePin(DIO_PORTB,u8Current+1);
		DIO_vidTogglePin(DIO_PORTB,u8Current-1);
	}
	
}

/*This function will be executed when the user presses any button*/
void vidBlink(void)
{
	/*The state of the whole port is checked and put in a variable*/
	/*This is done to determine the switch that was pressed.*/
	u8LEDState = PIND;
	if(u8LEDState == SW0)
	{
		/*Toggling the LED corresponding to the switch*/
		DIO_vidTogglePin(DIO_PORTB,DIO_PIN0);
		/*Toggling the adjoining LEDs*/
		vidToggleAdjoining(0);

	}
	else if (u8LEDState == SW1)
	{
		DIO_vidTogglePin(DIO_PORTB,DIO_PIN1);
		vidToggleAdjoining(1);

	}
	else if (u8LEDState == SW2)
	{
		DIO_vidTogglePin(DIO_PORTB,DIO_PIN2);
		vidToggleAdjoining(2);

	}
	else if (u8LEDState == SW3)
	{
		DIO_vidTogglePin(DIO_PORTB,DIO_PIN3);
		vidToggleAdjoining(3);

	}
	else if (u8LEDState == SW4)
	{
		DIO_vidTogglePin(DIO_PORTB,DIO_PIN4);
		vidToggleAdjoining(4);

	}
	else if (u8LEDState == SW5)
	{
		DIO_vidTogglePin(DIO_PORTB,DIO_PIN5);
		vidToggleAdjoining(5);
	}
	else if (u8LEDState == SW6)
	{
		DIO_vidTogglePin(DIO_PORTB,DIO_PIN6);
		vidToggleAdjoining(6);
	}
	else if (u8LEDState == SW7)
	{
		DIO_vidTogglePin(DIO_PORTB,DIO_PIN7);
		vidToggleAdjoining(7);
	}

}

void vidRunnWinningSequence(void)
{
	/*Blink*/
	DIO_vidSetPortValue(DIO_PORTB,0x00);
	_delay_ms(500);
	DIO_vidSetPortValue(DIO_PORTB,0xFF);
	_delay_ms(500);
	DIO_vidSetPortValue(DIO_PORTB,0x00);
	_delay_ms(500);
	DIO_vidSetPortValue(DIO_PORTB,0xFF);
}

int main(void)
{
	
	/*Setting pin direction for LEDs*/
	DIO_vidSetPinDirection(DIO_PORTB,DIO_PIN0,DIO_OUTPUT);
	DIO_vidSetPinDirection(DIO_PORTB,DIO_PIN1,DIO_OUTPUT);
	DIO_vidSetPinDirection(DIO_PORTB,DIO_PIN2,DIO_OUTPUT);
	DIO_vidSetPinDirection(DIO_PORTB,DIO_PIN3,DIO_OUTPUT);
	DIO_vidSetPinDirection(DIO_PORTB,DIO_PIN4,DIO_OUTPUT);
	DIO_vidSetPinDirection(DIO_PORTB,DIO_PIN5,DIO_OUTPUT);
	DIO_vidSetPinDirection(DIO_PORTB,DIO_PIN6,DIO_OUTPUT);
	DIO_vidSetPinDirection(DIO_PORTB,DIO_PIN7,DIO_OUTPUT);
	
	/*Lighting all LEDs at start*/
	DIO_vidSetPinValue(DIO_PORTB,DIO_PIN0,STD_HIGH);
	DIO_vidSetPinValue(DIO_PORTB,DIO_PIN1,STD_HIGH);
	DIO_vidSetPinValue(DIO_PORTB,DIO_PIN2,STD_HIGH);
	DIO_vidSetPinValue(DIO_PORTB,DIO_PIN3,STD_HIGH);
	DIO_vidSetPinValue(DIO_PORTB,DIO_PIN4,STD_HIGH);
	DIO_vidSetPinValue(DIO_PORTB,DIO_PIN5,STD_HIGH);
	DIO_vidSetPinValue(DIO_PORTB,DIO_PIN6,STD_HIGH);
	DIO_vidSetPinValue(DIO_PORTB,DIO_PIN7,STD_HIGH);	

	/*Switches pin direction and pull-up configuration*/
	DIO_vidSetPinDirection(DIO_PORTD,DIO_PIN0,DIO_INPUT);
	DIO_vidSetPinDirection(DIO_PORTD,DIO_PIN1,DIO_INPUT);
	DIO_vidSetPinDirection(DIO_PORTD,DIO_PIN2,DIO_INPUT);
	DIO_vidSetPinDirection(DIO_PORTD,DIO_PIN3,DIO_INPUT);
	DIO_vidSetPinDirection(DIO_PORTD,DIO_PIN4,DIO_INPUT);
	DIO_vidSetPinDirection(DIO_PORTD,DIO_PIN5,DIO_INPUT);
	DIO_vidSetPinDirection(DIO_PORTD,DIO_PIN6,DIO_INPUT);
	DIO_vidSetPinDirection(DIO_PORTD,DIO_PIN7,DIO_INPUT);

	
	/*External Interrupt Configuration*/
	/*Setting the function to be executed when any switch is pressed*/
	ExtInterupt_vidRegisterCallback(EXTINTER_PCINT2,vidBlink);
	
	/*Enabling interrupt for port D*/
	ExtInterrupt_vidEnableInterrupt(EXTINTER_PCINT2);
	/*Enabling interrupt on pin change for port D*/
	ExtInterrupt_vidEnablePinChangeInterrupt(EXTINTER_PIN_16);
	ExtInterrupt_vidEnablePinChangeInterrupt(EXTINTER_PIN_17);
	ExtInterrupt_vidEnablePinChangeInterrupt(EXTINTER_PIN_18);
	ExtInterrupt_vidEnablePinChangeInterrupt(EXTINTER_PIN_19);
	ExtInterrupt_vidEnablePinChangeInterrupt(EXTINTER_PIN_20);
	ExtInterrupt_vidEnablePinChangeInterrupt(EXTINTER_PIN_21);
	ExtInterrupt_vidEnablePinChangeInterrupt(EXTINTER_PIN_22);
	ExtInterrupt_vidEnablePinChangeInterrupt(EXTINTER_PIN_23);
	
	/*Enabling global interrupt*/
	INTERRUPTS_vidSetGlobalInterruptFlag();

	/*Inside the while loop, the */
	while (1)
	{
		/*When all the LEDs are off, run winning sequence*/
		/**/
		if (PORTB == 0)
		{
			vidRunnWinningSequence();
		}

	}
}

