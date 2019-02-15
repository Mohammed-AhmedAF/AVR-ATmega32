#ifndef _DIO_PRIVATE_H
#define _DIO_PRIVATE_H

#define DDRA *((volatile u8*) 0x3A)
#define PORTA *((volatile u8*) 0x3B)
#define PINA *((volatile u8*) 0x39)

#define DDRB *((volatile u8*) 0x37)
#define PORTB *((volatile u8*) 0x38)
#define PINB *((volatile u8*) 0x36)

#define DDRC *((volatile u8*) 0x34) 
#define PORTC *((volatile u8*) 0x35)
#define PINC *((volatile u8*) 0x33)

#define DDRD *((volatile u8*) 0x31)
#define PORTD *((volatile u8*) 0x32)
#define PIND *((volatile u8*) 0x30)

#endif
