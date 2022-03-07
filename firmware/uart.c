// screen tty.usbserial-AL065BVB <baud>
// (ctrl + a + k) ---> y

#include "uart.h"

#include <xc.h>
#include <pic16f690.h>
#include <string.h>

#include "pins.h"

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

	// 9600 bps @ Fosc = 4 MHz

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

int uart_transmit(void * buffer, int size)
{
	if (buffer == NULL || size < 0)
	{
		return ERROR;
	}

	char * data = (char *)buffer;
	int count = 0;

	for (int i = 0; i < size; i++)
	{
		uart_transmit_byte(data[i]);
		count++;
	}

	return count;
}

int uart_receive(void * buffer, int size)
{
	if (buffer == NULL || size < 0)
	{
		return ERROR;
	}

	char * data = (char *)buffer;
	int count = 0;

	for (int i = 0; i < size; i++)
	{
		data[i] = uart_receive_byte();
		count++;
	}

	return count;
}

//int uart_transmit_message(Message message)
//{
//	char * data = message_string(message);
//	int length = strlen(data);

//	uart_transmit(data, length);
//	uart_transmit_byte('\r');   // carriage return [Enter] indicates end of transmission

//	return length + 1;
//}

//Message uart_receive_message(void)
//{
//	char next = 0;
//	char data [MAX_MESSAGE_SIZE];
//	int length = sizeof(data);

//	memset(data, 0, length);

//	for (int i = 0; i < length - 1; i++)
//	{
//		next = uart_receive_byte();

//		if (next == '\r')   // carriage return [Enter] indicates end of transmission
//		{
//			break;
//		}

//		data[i] = next;
//	}

//	if (data[0] == '\0')   // empty message string
//	{
//		return MESSAGE_UNKNOWN;
//	}

//	for (Message message = 0; message < NUM_MESSAGES; message++)
//	{
//		if (strncmp(data, message_string(message), MAX_MESSAGE_SIZE) == 0)
//		{
//			return message;
//		}
//	}

//	return MESSAGE_UNKNOWN;
//}

void putch(char byte)
{
    uart_transmit_byte(byte);
}
