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

    g_PinStates = 0b10100000;
    //  [b7][b6][b5][b4]    [b3][b2][b1][b0] 
    //  [D2][D3][D4][D5]    [A0][A1][A2][A3] 
    //      < output >          < input >

    serialSetup(9600);

    // initialise output pins low
    digitalWrite(D5, HIGH);     // writing reboots arduino??
    _delay_ms(2000);
    digitalWrite(D5, LOW);
}


void loop(void)
{
    // update input states
    /* // why are all bits high after this??
    BIT_OVERRIDE_WITH_VAL(g_PinStates, 3, digitalRead(A0));
    BIT_OVERRIDE_WITH_VAL(g_PinStates, 2, digitalRead(A1));
    BIT_OVERRIDE_WITH_VAL(g_PinStates, 1, digitalRead(A2));
    BIT_OVERRIDE_WITH_VAL(g_PinStates, 0, digitalRead(A3));
    */

    // transceive message over serial (wait for cmd) UART
    //serialSendWithBusyWait(g_PinStates);
    


    // testcode to receive:
    
    uint8_t receivedByte = 0b00000000;
    receivedByte = serialReceiveWithBusyWait();
    if(receivedByte == 0b10100000){
        digitalWrite(D5, HIGH);
        _delay_ms(40);
        digitalWrite(D5, LOW);
        _delay_ms(40);
        digitalWrite(D5, HIGH);
        _delay_ms(40);
    }else{
        digitalWrite(D5, HIGH);
        _delay_ms(500);
    }
    digitalWrite(D5, LOW);
    


    // update output states
    /*
    digitalWrite(D2, BIT_IS_SET(g_PinStates, 7));
    digitalWrite(D3, BIT_IS_SET(g_PinStates, 6));
    digitalWrite(D4, BIT_IS_SET(g_PinStates, 5));
    digitalWrite(D5, BIT_IS_SET(g_PinStates, 4));
    */
}


int main (void)
{
    setup();

    while(true) {
        loop();
    }

    return EXIT_SUCCESS;
}
