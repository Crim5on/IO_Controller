# I/O Controller
I/O controller board based on ATmega328P


## Problem Definition
Design a DI/DO extension board featuring opto-coupled pins to protect the board against over-voltage. The pins shall support a voltage range of 5-30VDC with a low current load (signal only).


## Facts
* 4 DI pins (opto-coupled) supporting 5-30VDC (read-through)
* 4 DO pins (opto-coupled) supporting 5-30VDC (switch-through)
* Serial Communication Interface Client for Linux


## Communication
Pin states can be read and written to using a serial communication client that is shiped with this repository. The directory ```linuxSerialClient/``` contains a C++ file that serves a working example code, demonstrating how the serial client can be used on a Linux system. To build it, simply run ```make ioexample.run``` and start the binary.


## Makefile Usage

Build Everything: ```make```

Only Compile Example Code: ```make ioexample.run```

Upload Compiled Code to IO Board: ```make upload```

Clean Up Compiled Files: ```make clean```





# Development Environment


## Set Up AVR Toolchain

Make Sure Arduino Driver is Installed: 
```sudo apt install arduino```

Check Linux Distribution: 
```cat /etc/*-release | grep PRETTY_NAME```

If on Ubuntu / Debian: 
```sudo apt install -y gcc-avr binutils-avr avr-libc avrdude make```

If on Fedora / Red Hat: 
```sudo dnf install -y avr-gcc avr-binutils avr-libc avrdude make```


## Find Arduino Port

With the Arduino NOT plugged in, type ```sudo dmesg``` and hit enter. Then connect the Arduino to your computer and run ```sudo dmesg``` again to see what has changed. Check the last lines to find something like this: 

```[16792.214255] usb 1-1.1: ch341-uart converter now attached to ttyUSB0```

This means that the Arduino is now connected to port "/dev/ttyUSB0". Note that under Ubuntu (and some other distros) there is a pre-installed application called BRLTTY that causes USB serial device detection to fail. This can be resoved by simply uninstalling BRLTTY. (You're Welcome!) 

