#
# Author: Mohammed Ahmed Abd Al-Fattah
# File: Makefile
# Purpose: This is a makefile used to compile and load AVR projects.
# The particular microcontroller I am using this file with is the 
# AVR Atmega32.
#

MAIN = main.c
CC = avr-gcc
SRC = $(MAIN) DIO_program.c TIMER0_program.c LCD_I2C_program.c INTERRUPTS_program.c TWI_program.c PCF8574_program.c
MICROCNTRL = atmega32
CFLAGS = -mmcu=$(MICROCNTRL) -I . -O3

PRO = avrdude
PROGRAMMER_TYPE = usbasp

%.i :%.c
	$(CC) $< $(CFLAGS) -E -o $@

%.asm : %.i
	$(CC) $< $(CFLAGS) -S -o $@

%.o : %.c
	$(CC) $< $(CFLAGS) -o $@


.PHONY : build
build:
	$(CC) $(SRC) $(CFLAGS) -o main.o

.PHONY : generate_ctags
	ctags -R

#rule to generate hex file
.PHONY : build-hex
build-hex:
	avr-objcopy -O ihex main.o .main.hex

#Added pwd to distinguish between two or more similar projects being
#developed at the moment. The pwd command itself is not shown when
#making the project, this is done by prepending the command with @
.PHONY : load
load: clean generate_ctags build
	@pwd
	$(PRO) -p $(MICROCNTRL) -c $(PROGRAMMER_TYPE) -U flash:w:main.o
	rm -f *.o *.i

.PHONY : flash
flash :
	$(PRO) -V -v -p $(MICROCNTRL) -c $(PROGRAMMER_TYPE) -U flash:w:main.o

.PHONY : load-no-erase
load-no-erase: clean build
	@pwd
	@(PRO) -p $(MICROCONTROL) -c $(PROGRAMMER_TYPE) -D -U flash:w:main.o
	rm -f *.o *.i

.PHONY : convert
convert: clean
	unix2dos *

.PHONY : reconvert
reconvert : clean
	dos2unix * 

.PHONY : burn_fuses
burn_fuses:
	$(PRO) -p m32 -c $(PROGRAMMER_TYPE) -U lfuse:w:0xD4:m
	$(PRO) -p m32  -c $(PROGRAMMER_TYPE) -U hfuse:w:0xD9:m

.PHONY : clean
clean:
	rm -f *.o *.i

