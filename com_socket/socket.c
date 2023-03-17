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




void setupSerialSocket(void);



int main()
{
    // Configuration Setup

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


    // Control Modes

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
    tty.c_cc[VMIN] = 1;     // wait until 1 byte is received  
    tty.c_cc[VTIME] = 0;    // no timeout (blocking) - 0 [deciseconds]

    // Configure input and output boudrate
    cfsetispeed(&tty, B9600);
    cfsetospeed(&tty, B9600);


    // Save termios struct to linux config file
    returnValue = tcsetattr(serialPort, TCSANOW, &tty);
    if(returnValue != 0){
        printf("Error %i from tcsetattr: %s\n", errno, strerror(errno));
    }


    /* ### WRITING ### */
    uint8_t g_PinStates = 0b00000001;
    int numberOfBytesSent = write(serialPort, g_PinStates, sizeof(g_PinStates));
    if(numberOfBytesSent >= 0){
        printf("Transmitted %i bytes of data.\n", numberOfBytesSent);
    }else{
        printf("ERROR while transmitting data. (%i)\n", numberOfBytesSent);
    }



    /* ### READING ### */
    int numberOfBytesReceived = read(serialPort, g_PinStates, sizeof(g_PinStates));
    if(numberOfBytesReceived >= 0){
        printf("Received %i bytes of data.\n", numberOfBytesReceived);
    }else{
        printf("ERROR while transmitting data. (%i)\n", numberOfBytesReceived);
    }

    /* ### CLOSING ### */
    close(serialPort);


    printf("Hello World!\n");
    return EXIT_SUCCESS;
}
