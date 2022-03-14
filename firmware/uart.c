// screen tty.usbserial-AL065BVB <baud>
// (ctrl + a + k) ---> y

#include "uart.h"

#include <xc.h>
#include <pic16f690.h>
#include <stddef.h>

#include "led.h"

void uart_init(void)
{
	// GENERAL //

	TXSTAbits.SYNC = 0;     // use asynchronous mode
	RCSTAbits.SPEN = 1;     // enable serial port pins (TX = OUTPUT, RX = INPUT)

	// TRANSMITTER (TX) //

	TXSTAbits.TXEN = 1;     // enable TX circuitry
	TXSTAbits.TX9 = 0;      // use 8-bit transmission

	// RECEIVER (RX) //

	RCSTAbits.CREN = 1;     // enable RX circuitry
	RCSTAbits.RX9 = 1;      // use 8-bit reception

	// BAUD RATE //

	// 9615 (~9600) bps @ Fosc = 4 MHz

	TXSTAbits.BRGH = 1;     // use high baud rate settings
	BAUDCTLbits.BRG16 = 1;  // use 16-bit baud rate generator
	BAUDCTLbits.SCKP = 0;   // don't invert transmitted bits
	SPBRGH = 0;             // high register BRG multiplier
	SPBRG = 103;            // low register BRG multiplier
}

void uart_transmit_byte(char byte)
{
	while (TXSTAbits.TRMT == 0);   // wait for TX register to empty
	TXREG = byte;                  // load new byte into TX register
}

char uart_receive_byte(void)
{
	if (RCSTAbits.OERR == 1)   // Reset receiver if RX buffer is overrun
	{
		RCSTAbits.CREN = 0;
		RCSTAbits.CREN = 1;
	}

	while (PIR1bits.RCIF == 0);   // wait for RX register to receive new byte
	return RCREG;                 // read new byte from RX buffer
}

void uart_transmit(void * buffer, int size)
{
	if (buffer == NULL || size < 0)
	{
		return;
	}

	char * data = (char *)buffer;

	for (int i = 0; i < size; i++)
	{
		uart_transmit_byte(data[i]);
	}
}

void uart_receive(void * buffer, int size)
{
	if (buffer == NULL || size < 0)
	{
		return;
	}

	char * data = (char *)buffer;

	for (int i = 0; i < size; i++)
	{
		data[i] = uart_receive_byte();
	}
}

void putch(char byte)
{
    uart_transmit_byte(byte);
}
