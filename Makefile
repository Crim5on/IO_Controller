## 
# Makefile for the Arduino SMD feauturing the ATmega328P microcontroller.
#
# Notes for Makefile Noobs:
#
#	All makefile rules are structured like this:
# 		target:	prerequisites
#		<TAB> 	recipe
#
#	$@ means target
#	$^ means all prerequesites
#
##


# specify compiler
CC = avr-gcc

# specify programmer
PROGRAMMER = arduino

# overrideing baudrate
BAUDRATE = 57600		# Arduino Nano
# BAUDRATE = 115200		# Arduino Uno


# define mcu
MCU_MODEL = ATmega328P

# define compiler flags
CFLAGS ?= -Os -DF_APU=16000000UL -mmcu=atmega328p -Wall -Wextra -Werror -std=c99

# define linker flags
LDFLAGS ?= -mmcu=atmega328p

# define USB path to Arduino
#ARDUINO_USB ?= /dev/ttyACM0
ARDUINO_USB ?= /dev/ttyUSB0


# final hexfile that can be flashed
all: main.hex socket

main.hex: main.run
	@echo "generating hexfile .."
	avr-objcopy -O ihex -R .eeprom main.run main.hex

main.run: main.o hal/pin.o hal/serial.o
	@echo "linking compiled files to main.run .."
	$(CC) $(LDFLAGS) -o $@ $^

main.o: main.c
	@echo "compiling main.c .."
	$(CC) $(CFLAGS) -c -o $@ $<

hal/pin.o: hal/pin.c hal/pin.h
	@echo "compiling pin.c .."
	$(CC) $(CFLAGS) -c -o $@ $<

hal/serial.o: hal/serial.c hal/serial.h
	@echo "compiling serial.c .."
	$(CC) $(CFLAGS) -c -o $@ $<

upload: main.hex
	@echo "flashing hex file to microcontroller .."
	avrdude -F -V -c ${PROGRAMMER} -p ${MCU_MODEL} -P ${ARDUINO_USB} -b ${BAUDRATE} -U flash:w:main.hex  

socket: serialInterface/socket.c
	@echo "compiling serial interface .."
	gcc -Wall -Wextra -Werror -std=gnu99 -o serialInterface/socket.o serialInterface/socket.c

clean:
	@echo "cleaning up .."
	rm -rf *.o **/*.o *.run **/*.run *.hex **/*.hex

# define all targets that are not files
.PHONY: clean upload all