#include "Std_Types.h"
#include "Macros.h"
#include "UART_interface.h"
#include "PREPHIRALS_interface.h"

void PREPHIRALS_vidChoosePrephiral(void) {
	UART_vidSendString("1.Motor 2.LED\r");
}


