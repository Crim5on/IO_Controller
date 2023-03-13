#pragma once

#include <stdint.h>
#include <stdbool.h>

#include <avr/io.h>
#define F_CPU 16000000  // set CPU frequency in Hz
#include <util/delay.h>

#define HIGH 1
#define LOW 0


typedef enum {
    INPUT,
    OUTPUT,
    INPUT_PULLUP,
    PWM_OUTPUT
} Mode;


typedef enum {
//  Arduino         ATmega
    // port D
    D0,             // PD0
    D1,             // PD1
    D2,             // PD2
    D3,             // PD3
    D4,             // PD4
    D5,             // PD5
    D6,             // PD6
    D7,             // PD7
    // port B 
    D8,             // PB0
    D9,             // PB1
    D10,            // PB2
    D11,            // PB3
    D12,            // PB4
    D13,            // PB5
    // port C
    A0,             // PC0
    A1,             // PC1
    A2,             // PC2
    A3,             // PC3
    A4,             // PC4
    A5              // PC5
} ArduinoPin;


void setPinMode(const uint8_t pin, const Mode mode);

void digitalWrite(const uint8_t pin, const bool value);

int8_t digitalRead(const uint8_t pin);

int8_t pinIsSetAsInput(const uint8_t pin);
