#pragma once
/** CLIENT THAT CAN BE USED TO COMUNICATE WITH THE IO CONTROLLER OVER SERIAL */

#include <iostream>
#include <string>
#include <exception>

#include "lxSerial.h"
#include "../utils/bit.h"

/*  NOTE: BYTE DEFINITION - BIT-TO-PIN MAPPING
                < output >         < input >
    bits:   [b7][b6][b5][b4]    [b3][b2][b1][b0] 
    pins:   [D2][D3][D4][D5]    [A0][A1][A2][A3] 
*/


class IO_ControllerSerialClient
{
    private:
        uint8_t g_PinStates;
        int serialPortHandle;
        void updatePinStates(void);
        bool alreadyInitialised;

    public:
        IO_ControllerSerialClient(const std::string comPort);
        ~IO_ControllerSerialClient();

        /** @returns logical state of input pin */
        bool readPinState(uint8_t pin);

        /** sets logical state of output pin */
        void writePinState(uint8_t pin, bool state);
};


IO_ControllerSerialClient::IO_ControllerSerialClient(const std::string comPort)
{
    g_PinStates = 0b00000000;
    serialPortHandle = initialiseSerialConnection(comPort.c_str());

    if(serialPortHandle < 0){
        throw std::runtime_error("ERROR while initialising serial port!");
    }
    else{
        std::cout << "Serial Connection Open." << std::endl;
    }
}


IO_ControllerSerialClient::~IO_ControllerSerialClient()
{
    close(serialPortHandle);
    std::cout << "Serial Connection Closed." << std::endl;
}


void IO_ControllerSerialClient::updatePinStates(void)
{
    int numberOfBytesSent = write(serialPortHandle, &g_PinStates, sizeof(g_PinStates));
    if(numberOfBytesSent < 0){
        throw std::runtime_error("ERROR while writing on serial port!");
    }

    int numberOfBytesReceived = read(serialPortHandle, &g_PinStates, sizeof(g_PinStates));
    if(numberOfBytesReceived < 0){
        throw std::runtime_error("ERROR while reading from serial port!");
    }
}


bool IO_ControllerSerialClient::readPinState(uint8_t pin)
{
    updatePinStates();
    bool pinState = BIT_IS_SET(g_PinStates, pin);
    return pinState;
}


void IO_ControllerSerialClient::writePinState(uint8_t pin, bool state)
{
    BIT_OVERRIDE_WITH_VAL(g_PinStates, pin, state);
    updatePinStates();
}

