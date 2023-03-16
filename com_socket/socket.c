/** comunication socket for IO controller (MWE) */

// C library headers
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

// Linux headers
#include <fcntl.h>      // Contains file controls like O_RDWR
#include <errno.h>      // Error integer and strerror() function
#include <termios.h>    // Contains POSIX terminal control definitions
#include <unistd.h>     // write(), read(), close()

// bit manipulation helpers
#define BIT_FIELD_SET(field, bitmask) (field |= bitmask)
#define BIT_FIELD_CLR(field, bitmask) (field &= ~bitmask)


#define COMPORT "/dev/ttyUSB0"

/* Error Codes:
    2   "No such file or directory"
    13  "Permission denied"
*/

//NOTE: working on -> https://blog.mbedded.ninja/programming/operating-systems/linux/linux-serial-ports-using-c-cpp/





void setupSerialSocket(void);



int main()
{
    // CHAPTER 5.) Configuration Setup

    // open serial port
    int serialPort = open(COMPORT, O_RDWR);
    if(serialPort < 0){
        printf("Error %i from open: %s\n", errno, strerror(errno));
    }

    // termios struct
    struct termios tty;
    // read existing settings into struct - put serialPort state into tty struct
    int returnValue = tcgetattr(serialPort, &tty);
    if(returnValue != 0){
        printf("Error %i from tcgetattr: %s\n", errno, strerror(errno));
    }


    // CHAPTER 6.) Control Modes

    // NOTE: macros cannot be used as mac
    // configure comunication settings to 8N1
    BIT_FIELD_CLR(tty.c_cflag, CSIZE);   // reset all size bits
    BIT_FIELD_SET(tty.c_cflag, CS8);     // set 8 data bits
    BIT_FIELD_CLR(tty.c_cflag, PARENB);  // clear parity bit flag (No parity)
    BIT_FIELD_CLR(tty.c_cflag, CSTOPB);  // clear (2nd) stop bit (-> 1 stop bit)
    //tty.c_cflag &= ~CSIZE;      // reset all size bits
    //tty.c_cflag |= CS8;         // set 8 data bits
    //tty.c_cflag &= ~PARENB;     // clear parity bit flag (No parity)
    //tty.c_cflag &= ~CSTOPB;     // clear (2nd) stop bit (-> 1 stop bit)
    
    BIT_FIELD_CLR(tty.c_cflag, CRTSCTS);    // disable RTS/CTS hardware flow control
    BIT_FIELD_SET(tty.c_cflag, CREAD);      // enable READ (to read from serial)
    BIT_FIELD_SET(tty.c_cflag, CLOCAL);     // enable ignore ctrl lines


    // CHAPTER 7.) Local Modes






    // CHAPTER 8.) Input Modes


    // CHAPTER 9.) Output Modes



    printf("Hello World!\n");
    return EXIT_SUCCESS;
}
