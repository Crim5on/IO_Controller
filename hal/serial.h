#pragma once
#include <stdint.h>

void serialSetup(const uint32_t baudRate);

void serialSendWithBusyWait(const uint8_t byte);

uint8_t serialReceiveWithBusyWait(void);

void flushInput(void);
