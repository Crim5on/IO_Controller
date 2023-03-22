#pragma once
/** HEADER ONLY IMPLEMENTATION TO SET UP SERIAL COMUNICATION UNDER LINUX */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <fcntl.h>      // Contains file controls like O_RDWR
#include <errno.h>      // Error integer and strerror() function
#include <termios.h>    // Contains POSIX terminal control definitions
#include <unistd.h>     // write(), read(), close()

// bit manipulation helpers
#define BIT_FIELD_SET(field, bitmask) (field |= bitmask)
#define BIT_FIELD_CLR(field, bitmask) (field &= ~bitmask)



/** @returns initialised serial port handle */
int initialiseSerialConnection (const char* comPort)
{
    int returnValue;

    const int serialPortHandle = open(comPort, O_RDWR);
    if(serialPortHandle < 0){
        perror("ERROR from open()");
        return -1;
    }

    struct termios tty;
    // put serialPortHandle state into tty struct
    returnValue = tcgetattr(serialPortHandle, &tty);
    if(returnValue != 0){
        perror("ERROR from tcgetattr()");
        return -1;
    }

    // configure comunication settings to 8N1
    BIT_FIELD_CLR(tty.c_cflag, CSIZE);      // reset all size bits
    BIT_FIELD_SET(tty.c_cflag, CS8);        // set 8 data bits
    BIT_FIELD_CLR(tty.c_cflag, PARENB);     // clear parity bit flag (No parity)
    BIT_FIELD_CLR(tty.c_cflag, CSTOPB);     // clear (2nd) stop bit (-> 1 stop bit)
    BIT_FIELD_CLR(tty.c_cflag, CRTSCTS);    // disable RTS/CTS hardware flow control
    BIT_FIELD_SET(tty.c_cflag, CREAD);      // enable READ (to read from serial)
    BIT_FIELD_SET(tty.c_cflag, CLOCAL);     // enable ignore ctrl lines

    // Local Flags
    BIT_FIELD_CLR(tty.c_lflag, ICANON);     // disable canonical mode
    BIT_FIELD_CLR(tty.c_lflag, ECHO);       // disable echo
    BIT_FIELD_CLR(tty.c_lflag, ECHOE);      // disable erasure
    BIT_FIELD_CLR(tty.c_lflag, ECHONL);     // disable linebreak echo
    BIT_FIELD_CLR(tty.c_lflag, ISIG);       // disable signal characters

    // Input Flags
    BIT_FIELD_CLR(tty.c_iflag, (IXON|IXOFF|IXANY));      // disable sw flow ctrl
    // disable special handling of bytes
    BIT_FIELD_CLR(tty.c_iflag, (PARMRK|IGNBRK|ISTRIP|ICRNL|BRKINT|INLCR|IGNCR));

    // Output Flags
    BIT_FIELD_CLR(tty.c_oflag, OPOST);      // disable special handling of bytes
    BIT_FIELD_CLR(tty.c_oflag, ONLCR);      // disable conversion of \n to \r

    // Configure Blocking and Timeout Read Options
    tty.c_cc[VMIN] = 1;                     // wait until 1 byte is received  
    tty.c_cc[VTIME] = 0;                    // no timeout (blocking) - 0 [deciseconds]

    // Configure input and output boudrate
    cfsetispeed(&tty, B9600);
    cfsetospeed(&tty, B9600);

    // Save termios struct to linux config file
    returnValue = tcsetattr(serialPortHandle, TCSANOW, &tty);
    if(returnValue != 0){
        perror("ERROR from tcsetattr()");
        return -1;
    }

    tcflush(serialPortHandle, TCIOFLUSH);   // flush input and output
    return serialPortHandle;
}
