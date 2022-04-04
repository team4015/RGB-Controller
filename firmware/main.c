/* ======= RGB CONTROLLER =======
 * The protocol for talking to the
 * RGB controller is very simple.
 * The PIC will look for a header
 * byte '0xFF' AKA eight 1's.  When
 * this byte is detected, the PIC will
 * receive the next three bytes from the
 * UART and use them as the RGB values.
 * These bytes will be should be the
 * brightness values for red, green,
 * and blue, in that order.  The status
 * LED will turn on while the RGB values
 * are being received.  The PIC will
 * will never respond to the sender.
 *
 * IMPORTANT:
 * Please note that the PIC UART can
 * only receive one or two bytes at a
 * time in the RX buffer.  Sending more
 * than one byte all at once will
 * drown the PIC in bytes.  Please
 * transmit bytes individually to the
 * PIC with a delay of 10 ms between
 * each one.
 * ============================== */

#include <xc.h>
#include <pic16f690.h>

#include "init.h"
#include "led.h"
#include "uart.h"
#include "pwm.h"

#define HEADER   0xFF
#define FLASH_DELAY   10000000

inline void rgb(unsigned char red, unsigned char green, unsigned char blue)
{
	pwm_red(red);
	pwm_green(green);
	pwm_blue(blue);
}

inline void purple(void)
{
	rgb(200, 0, 128);
}

void main(void)
{
	init_hardware();
	led_init();
	uart_init();
	pwm_init();

	purple();

	while (1)
	{
		while (uart_receive_byte() != HEADER);   // wait for the header byte on the UART

		led_on();

		// receive the RGB values
		char red = uart_receive_byte();
		char green = uart_receive_byte();
		char blue = uart_receive_byte();

		led_off();

		// update the brightness for each colour
		rgb(red, green, blue);
	}
}
