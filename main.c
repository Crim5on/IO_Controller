#include <stdlib.h>
#include "hal/pin.h"
#include "hal/serial.h"
#include "utils/bit.h"

/* this is slave sided */

// arduino does never send something on its own, master will poll to transcieve communication.
uint8_t g_PinStates;


void setup(void)
{
    setPinMode(D2, OUTPUT);
    setPinMode(D3, OUTPUT);
    setPinMode(D4, OUTPUT);
    setPinMode(D5, OUTPUT);

    setPinMode(A0, INPUT_PULLUP);
    setPinMode(A1, INPUT_PULLUP);
    setPinMode(A2, INPUT_PULLUP);
    setPinMode(A3, INPUT_PULLUP);

    g_PinStates = 0b00000000;
    //  [b7][b6][b5][b4]    [b3][b2][b1][b0] 
    //  [D2][D3][D4][D5]    [A0][A1][A2][A3] 
    //      < output >          < input >

    serialSetup(9600);
}


void loop(void)
{
    // testcode for hardware:
    digitalWrite(D5, digitalRead(A0));

    // update input states
    BIT_OVERRIDE_WITH_VAL(g_PinStates, 3, digitalRead(A0));
    BIT_OVERRIDE_WITH_VAL(g_PinStates, 2, digitalRead(A1));
    BIT_OVERRIDE_WITH_VAL(g_PinStates, 1, digitalRead(A2));
    BIT_OVERRIDE_WITH_VAL(g_PinStates, 0, digitalRead(A3));


    // transceive message over serial (wait for cmd) UART
    // read serial until ready
    // a.) send g_PinStates
    // b.) read g_PinStates
    const char testMsg[] = "\nHello World! ";
    for(uint8_t i = 0; i < sizeof(testMsg)-1; i++){
        serialSendWithBusyWait(testMsg[i]);
    }
    _delay_ms(2000);


    // ? -> send input states 0 0 0 0 


    // update output states
    digitalWrite(D2, BIT_IS_SET(g_PinStates, 7));
    digitalWrite(D3, BIT_IS_SET(g_PinStates, 6));
    digitalWrite(D4, BIT_IS_SET(g_PinStates, 5));
    digitalWrite(D5, BIT_IS_SET(g_PinStates, 4));
}


int main (void)
{
    setup();

    while(true) {
        loop();
    }

    return EXIT_SUCCESS;
}
