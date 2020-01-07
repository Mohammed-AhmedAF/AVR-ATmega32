/*
 * IC74595_interface.h
 *
 * Created: 7/17/2019 4:24:39 PM
 *  Author: Admin
 */ 


#ifndef _IC74595_INTERFACE_H_
#define _IC74595_INTERFACE_H_

#define IC74595_LATCH_PORT DIO_PORTB
#define IC74595_LATCH_PIN DIO_PIN1
#define IC74595_OUTENABLE_PORT DIO_PORTB
#define IC74595_OUTENABLE_PIN DIO_PIN0

struct strctIC595 {
	u8 u8LatchPort;
	u8 u8LatchPin;
	u8 u8OEPort;
	u8 u8OEPin;
	} ;

/*Function definition*/
void IC74595_vidInit(void);
void IC74595_vidControl(void);
void IC74595_vidInitExtended(struct strctIC595 IC595Data);
void IC74595_vidControlExtended(struct strctIC595 IC595Data);



#endif /* IC74595_INTERFACE_H_ */
