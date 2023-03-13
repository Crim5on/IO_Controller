# I/O Controller
I/O controller board based on ATmega328P



## Problem Definition
Design a DI/DO extension board featuring opto-coupled pins to protect the board against over-voltage from ESD (electrostatic discharge) and to improve EMC (electromagnetic compatibility) immunity. The pins shall support a voltage range of 5-30VDC with a low current load (signal only).



## Communication
* simple CDC (Communications Device Class)? serial interface
* IO board polls via serial to receive new IO states?  
Original:  
```simple CDC serial connectivity with a polling based serial protocol to receive input states and set output states```



## Facts
* 4 DI pins (opto-coupled) supporting 5-30VDC
* 4 DO pins (opto-coupled) supporting 5-30VDC (switch-through)
* Serial Communication Interface based on polling



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

