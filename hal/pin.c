#include "pin.h"
#include "../utils/bit.h"

/* 
    This code maps the Arduino pinout to the ATmega328P pinout (driver or HAL).
    The microcontroller can therfore be ported to another platform without having
    to change the implementation of the application layer.   
*/

#define OFFSET_PORT_B 8
#define OFFSET_PORT_C 14
#define OFFSET_PORT_D 0


static inline bool isOnPortB(const ArduinoPin pin){
    return (pin >= 8 && pin <= 13);
}

static inline bool isOnPortC(const ArduinoPin pin){
    return (pin >= 14 && pin <= 19);
}

static inline bool isOnPortD(const ArduinoPin pin){
    return (pin >= 0 && pin <= 7);
}


void setPinMode(const uint8_t pin, const Mode mode)
{
    if(isOnPortB(pin)){
        if(mode == OUTPUT){
            BIT_SET(DDRB, (pin - OFFSET_PORT_B));
        }
        else if(mode == INPUT){
            BIT_CLR(DDRB, (pin - OFFSET_PORT_B));
        }
        else if(mode == INPUT_PULLUP){
            // enable pull-up by writting a logical 1 to the PORT register of an as input defined pin.
            BIT_CLR(DDRB, (pin - OFFSET_PORT_B));
            BIT_SET(PORTB, (pin - OFFSET_PORT_B));
        }
    } 
    else if(isOnPortC(pin)){
        if(mode == OUTPUT){
            BIT_SET(DDRC, (pin - OFFSET_PORT_C));
        }
        else if(mode == INPUT){
            BIT_CLR(DDRC, (pin - OFFSET_PORT_C));
        }
        else if(mode == INPUT_PULLUP){
            // enable pull-up by writting a logical 1 to the PORT register of an as input defined pin.
            BIT_CLR(DDRC, (pin - OFFSET_PORT_C));
            BIT_SET(PORTC, (pin - OFFSET_PORT_C));
        }
    } 
    else if(isOnPortD(pin)){
        if(mode == OUTPUT){
            BIT_SET(DDRD, (pin - OFFSET_PORT_D));
        }
        else if(mode == INPUT){
            BIT_CLR(DDRD, (pin - OFFSET_PORT_D));
        }
        else if(mode == INPUT_PULLUP){
            // enable pull-up by writting a logical 1 to the PORT register of an as input defined pin.
            BIT_CLR(DDRD, (pin - OFFSET_PORT_D));
            BIT_SET(PORTD, (pin - OFFSET_PORT_D));
        }
    }
}


int8_t digitalRead(const uint8_t pin)
{
    if(isOnPortB(pin)){
        return BIT_IS_SET(PINB, (pin - OFFSET_PORT_B));
    }
    else if (isOnPortC(pin)){
        return BIT_IS_SET(PINC, (pin - OFFSET_PORT_C));
    }
    else if(isOnPortD(pin)){
        return BIT_IS_SET(PIND, (pin - OFFSET_PORT_D));
    }
    else{
        return -1; // for wrong pin
    }
}


void digitalWrite(const uint8_t pin, const bool value)
{
    if(isOnPortB(pin)){
        if(value == HIGH){
            BIT_SET(PORTB, (pin - OFFSET_PORT_B));
        }
        else if(value == LOW){
            BIT_CLR(PORTB, (pin - OFFSET_PORT_B));
        }
    }
    else if(isOnPortC(pin)){
        if(value == HIGH){
            BIT_SET(PORTC, (pin - OFFSET_PORT_C));
        }
        else if(value == LOW){
            BIT_CLR(PORTC, (pin - OFFSET_PORT_C));
        }
    }
    else if(isOnPortD(pin)){
        if(value == HIGH){
            BIT_SET(PORTD, (pin - OFFSET_PORT_D));
        }
        else if(value == LOW){
            BIT_CLR(PORTD, (pin - OFFSET_PORT_D));
        }
    }
}


int8_t pinIsSetAsInput(const uint8_t pin)
{
    // negated because 'bit not set' means input. ;)
    if(isOnPortB(pin)){
        return !BIT_IS_SET(DDRB, (pin - OFFSET_PORT_B));
    } 
    else if(isOnPortC(pin)){
        return !BIT_IS_SET(DDRC, (pin - OFFSET_PORT_C));
    } 
    else if(isOnPortD(pin)){
        return !BIT_IS_SET(DDRD, (pin - OFFSET_PORT_D));
    }
    else{
        return -1;  // for wrong pin
    }
}
