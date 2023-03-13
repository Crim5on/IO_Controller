#include <stdlib.h>
#include "hal/pin.h"


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
}


void loop(void)
{
    digitalWrite(D5, digitalRead(A0));
    //_delay_ms(1000);
}


int main (void)
{
    setup();

    while(true) {
        loop();
    }

    return EXIT_SUCCESS;
}
