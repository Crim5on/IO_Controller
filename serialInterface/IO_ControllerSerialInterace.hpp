#pragma once

#include <iostream>
#include <stdint.h>

#include "serialSocket.h"
#include "../utils/bit.h"

// NOTE: global pin states in one byte
//  [b7][b6][b5][b4]    [b3][b2][b1][b0] 
//  [D2][D3][D4][D5]    [A0][A1][A2][A3] 
//      < output >          < input >




// TODO: make singleton.

class IO_ControllerSerialInterface
{
    private:
        uint8_t g_PinStates;
        int serialPortHandle;
        void updatePinStates(void);

    public:
        IO_ControllerSerialInterface();
        ~IO_ControllerSerialInterface();

        /** @returns logical state of input pin */
        bool readPinState(uint8_t pin);

        /** sets logical state of output pin */
        void writePinState(uint8_t pin, bool state);
};


IO_ControllerSerialInterface::IO_ControllerSerialInterface()
{
    g_PinStates = 0b00000000;
    serialPortHandle = ioControllerSetupSerialSocket();

    if(serialPortHandle < 0){
        std::cerr << "ERROR while opening serial port!" << std::endl;
        std::cerr << "errNo.: " << errno << " msg: " << strerror(errno) << std::endl;
    }
    else{
        std::cout << "Serial Connection Open." << std::endl;
    }
}


IO_ControllerSerialInterface::~IO_ControllerSerialInterface()
{
    close(serialPortHandle);
    std::cout << "Serial Connection Closed." << std::endl;
}


void IO_ControllerSerialInterface::updatePinStates(void)
{
    int numberOfBytesSent = write(serialPortHandle, &g_PinStates, sizeof(g_PinStates));
    if(numberOfBytesSent < 0){
        std::cerr << "ERROR while writing on serial port! (" << numberOfBytesSent << ")" << std::endl;
        // throw exception;
    }

    int numberOfBytesReceived = read(serialPortHandle, &g_PinStates, sizeof(g_PinStates));
    if(numberOfBytesReceived < 0){
        std::cerr << "ERROR while reading from serial port! (" << numberOfBytesReceived << ")" << std::endl;
        // throw exception;
    }
}


bool IO_ControllerSerialInterface::readPinState(uint8_t pin)
{
    updatePinStates();
    bool pinState = BIT_IS_SET(g_PinStates, pin);
    return pinState;
}


void IO_ControllerSerialInterface::writePinState(uint8_t pin, bool state)
{
    BIT_OVERRIDE_WITH_VAL(g_PinStates, pin, state);
    updatePinStates();
}

