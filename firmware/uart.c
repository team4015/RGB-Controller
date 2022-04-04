// screen tty.usbserial-AL065BVB <baud>
// (ctrl + a + k) ---> y

#include "uart.h"

#include <xc.h>
#include <pic16f690.h>
#include <stddef.h>

#include "led.h"
#include "fifo.h"

#define RX_FIFO_SIZE   64
static char rx_buffer [RX_FIFO_SIZE];
static FIFO rx_fifo;

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
	PIE1bits.RCIE = 1;      // enable RX interrupt
	fifo_init(&rx_fifo, &rx_buffer, RX_FIFO_SIZE);

	// BAUD RATE //

	// 9615 (~9600) bps @ Fosc = 4 MHz

	TXSTAbits.BRGH = 1;     // use high baud rate settings
	BAUDCTLbits.BRG16 = 1;  // use 16-bit baud rate generator
	BAUDCTLbits.SCKP = 0;   // don't invert transmitted bits
	SPBRGH = 0;             // high register BRG multiplier
	SPBRG = 207;            // low register BRG multiplier
}

void uart_transmit_byte(char byte)
{
	while (TXSTAbits.TRMT == 0);   // wait for TX register to empty
	TXREG = byte;                  // load new byte into TX register
}
#include "init.h"
char uart_receive_byte(void)
{
	if (RCSTAbits.OERR == 1)   // Reset receiver if RX buffer is overrun
	{
		while (1)
		{
			init_indicator();
		}
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

char uart_read_byte(void)
{
	while (fifo_is_empty(&rx_fifo));   // wait for new RX data to arrive
	return fifo_read_byte(&rx_fifo);   // return the next byte
}

void uart_isr_rx(void)
{
	char value = uart_receive_byte();   // remove byte from RCREG (clears RCIF)
	fifo_write_byte(&rx_fifo, value);   // byte will be dropped if FIFO is full
	if (fifo_is_full(&rx_fifo))
	{
		while (1)
		{
			init_indicator();
		}
	}
}
