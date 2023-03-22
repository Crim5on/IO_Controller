# I/O Controller
I/O controller board based on ATmega328P


## Problem Definition
Design a DI/DO extension board featuring opto-coupled pins to protect the board against over-voltage. The pins shall support a voltage range of 5-30VDC with a low current load (signal only).


## Facts
* 4 DI pins (opto-coupled) supporting 5-30VDC (read-through)
* 4 DO pins (opto-coupled) supporting 5-30VDC (switch-through)
* Serial Communication Interface Client for Linux


## Communication
Pin states can be read and written to using a serial communication client that is shiped with this repository. The directory ```linuxSerialClient``` contains a C++ file that serves a working example code, demonstrating how the serial client can be used on a Linux system. To build it, simply run ```Make ioexample.run``` and start the binary.


## Makefile Usage

Build Everything
```make```

Only Compile Example Code
```make ioexample```

Upload Compiled Code to IO Board 
```make upload```

Clean Up Compiled Files 
```make clean```





# Development Environment


## Set Up AVR Toolchain

make sure arduino driver is installed 
```sudo apt install arduino```

check distribution:
```cat /etc/*-release | grep PRETTY_NAME```

under Ubuntu / Debian:
```sudo apt install -y gcc-avr binutils-avr avr-libc avrdude make```

under Fedora / Red Hat:
```sudo dnf install -y avr-gcc avr-binutils avr-libc avrdude make```


## Find Arduino Port

```sudo dmesg``` 

plug USB device in and run cmd again 

```sudo dmesg``` 

check for the last entry to find something like this: 

```[16208.532075] usb 1-1: New USB device found, idVendor=1a86, idProduct=7523, bcdDevice= 2.54```

