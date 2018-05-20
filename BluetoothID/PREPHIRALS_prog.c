#include "Std_Types.h"
#include "Macros.h"
#include "UART_interface.h"
#include "PREPHIRALS_interface.h"

void vid_ChoosePrephiral(void) {
	UART_vidSendString("1.Motor 2.LED\r");
}
