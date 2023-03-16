#include <avr/io.h>

#include "serial.h"
#include "pin.h"
#include "../utils/bit.h"


void serialSetup(const uint32_t baudRate)
{
    // Set USART Baud Rate @ UBRRn (USART Baud Rate Register)
    // e.g.        baudValue = 16000000 Hz / (16 * 9600 Baud) - 1 = 103
    const uint16_t baudValue = F_CPU / (16 * baudRate) - 1;
    UBRR0H = (uint8_t)(baudValue >> 8);     // sets the 4 most significant bits of the baud rate
    UBRR0L = (uint8_t)(baudValue);          // sets the 8 least significant bits of the baud rate

    // Set frame format to 8N1 @ UCSR0C (USART Control and Status Register 0 C)
    // [ UMSELn1 | UMSELn0 | UPMn1 | UPMn0 | USBSn | UCSZn1 | UCSZn0 | UCPOLn ] |= 0b00000110
    BIT_SET(UCSR0C, UCSZ00);
    BIT_SET(UCSR0C, UCSZ01);
    
    // Enable Transmitter & Receiver @ UCSR0B (USART Control and Status Register 0 B)
    // [ RXCIEn |TXCIEn | UDRIEn | RXENn | TXENn | UCSZn2 | RXB8n | TXB8n ] |= 0b00011000
    BIT_SET(UCSR0B, RXEN0);     // enable receiver (RX) @ UCSR0B
    BIT_SET(UCSR0B, TXEN0);     // enable transmitter (TX) @ UCSR0B
}


void serialSendWithBusyWait(const uint8_t byte)
{
    // wait for USART Data Register Empty (UDREn) flag to be set.
    // [ RXCn | TXCn | UDREn | FEn | DORn | UPEn | U2Xn | MPCMn ]
    while(!BIT_IS_SET(UCSR0A, UDRE0)){
        ; // wait
    }

    // writing data byte into the USART Data Register (UDR) (automatically sends it)
    UDR0 = byte;    
}


uint8_t serialReceiveWithBusyWait(void)
{
    // wait for RXC0 (USART Receive Complete 0) flag to be set.
    // [ RXCn | TXCn | UDREn | FEn | DORn | UPEn | U2Xn | MPCMn ]
    while (!BIT_IS_SET(UCSR0A, RXC0))
    {
        ; // wait
    }

    // read byte from transmit buffer // TODO: ???
    uint8_t byte = UDR0;
    return byte;
}