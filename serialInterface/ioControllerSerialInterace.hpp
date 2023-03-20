#include <iostream>
#include <stdint.h>



class ioControllerSerialInterace
{
    private:
    uint8_t g_PinStates;

    public:
    ioControllerSerialInterace(/* args */);
    ~ioControllerSerialInterace();

    /** @returns logical state of input pin */
    bool readPinState(uint8_t pin);

    /** sets logical state of output pin */
    void writePinState(uint8_t pin, bool state);
};


ioControllerSerialInterace::ioControllerSerialInterace(/* args */)
{
    g_PinStates = 0b00000000;
}


ioControllerSerialInterace::~ioControllerSerialInterace()
{
    // close serial port
}
