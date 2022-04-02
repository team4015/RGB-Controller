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

struct __attribute__((packed)) Colour
{
	unsigned char red;
	unsigned char green;
	unsigned char blue;
};

typedef struct Colour Colour;

void main(void)
{
	init_hardware();
	led_init();
	uart_init();
	pwm_init();

	pwm_red(0);
	pwm_green(0);
	pwm_blue(0);

	Colour colour;

	while (1)
	{
		while (uart_receive_byte() != HEADER);   // wait for the header byte on the UART

		// receive the RGB values
		led_on();
		uart_receive(&colour, sizeof(Colour));
		led_off();

		// update the brightness for each colour
		pwm_red(colour.red);
		pwm_green(colour.green);
		pwm_blue(colour.blue);
	}
}
