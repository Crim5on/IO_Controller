#include <stdlib.h>
#include "hal/pin.h"
#include "hal/serial.h"
#include "utils/bit.h"


/*  NOTE: BYTE DEFINITION - BIT-TO-PIN MAPPING
                < output >         < input >
    bits:   [b7][b6][b5][b4]    [b3][b2][b1][b0] 
    pins:   [D5][D4][D3][D2]    [A3][A2][A1][A0] 
*/

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

    serialSetup(9600);
    g_PinStates = 0b00000000;
}


void loop(void)
{
    // wait to receive new output states from client
    g_PinStates = serialReceiveWithBusyWait();

    // write new output states
    digitalWrite(D2, BIT_IS_SET(g_PinStates, 4));
    digitalWrite(D3, BIT_IS_SET(g_PinStates, 5));
    digitalWrite(D4, BIT_IS_SET(g_PinStates, 6));
    digitalWrite(D5, BIT_IS_SET(g_PinStates, 7));

    // read new input states (negated bc of pull-up)
    BIT_OVERRIDE_WITH_VAL(g_PinStates, 0, !digitalRead(A0));
    BIT_OVERRIDE_WITH_VAL(g_PinStates, 1, !digitalRead(A1));
    BIT_OVERRIDE_WITH_VAL(g_PinStates, 2, !digitalRead(A2));
    BIT_OVERRIDE_WITH_VAL(g_PinStates, 3, !digitalRead(A3));

    // send updated input states back to client
    serialSendWithBusyWait(g_PinStates);
}


int main (void)
{
    setup();

    while(true) {
        loop();
    }

    return EXIT_SUCCESS;
}
