/*
 * main.c
 *
 *  Created on: Dec 21, 2017
 *      Author: EngOm
 */


#include "FreeRTOS.h"
#include "task.h"
#include "Std_Types.h"
#include "Macros.h"
#include "DIO_interface.h"


void LED_blink(void * pv);
xTaskHandle LED_Handle;

int main(void)
{
	DIO_vidSetPinDirection(DIO_PORTA,DIO_PIN0,1);
	xTaskCreate(LED_blink,"LED_blinking",40,NULL,1,&LED_Handle);
	vTaskStartScheduler();
	return 0;
}

void LED_blink(void * pv) {

	portTickType LastCount;
	const portTickType periodicity = 500;
	LastCount = xTaskGetTickCount();

	while(1) {
		TOGGLE_BIT(PORTA,0);

		vTaskDelayUntil(&LastCount,periodicity);

	}
}
