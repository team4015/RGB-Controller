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

#include <stdbool.h>
enum Colour
{
	RED,
	GREEN,
	BLUE,

	NUM_COLOURS
};
typedef enum Colour Colour;
static bool header = false;
static char rgb [3];
static Colour colour = RED;

void main(void)
{
	init_hardware();
	led_init();
	uart_init();
	pwm_init();

	pwm_red(255);
	pwm_green(255);
	pwm_blue(255);

	while (1)
	{
		if (header && colour == NUM_COLOURS)
		{
			pwm_red(rgb[RED]);
			pwm_green(rgb[GREEN]);
			pwm_blue(rgb[BLUE]);
			header = false;
		}
		//uart_transmit_byte(uart_read_byte());
		//while (uart_read_byte() != HEADER);

		//// receive the RGB values
		//led_on();
		//char red = uart_read_byte();
		//char green = uart_read_byte();
		//char blue = uart_read_byte();
		//led_off();

		//// update the brightness for each colour
		//pwm_red(red);
		//pwm_green(green);
		//pwm_blue(blue);
	}
}

void __interrupt() isr(void)
{
	if (PIR1bits.TMR2IF == 1)
	{
		pwm_isr();
	}
	else if (PIR1bits.RCIF == 1)
	{
		// RCIF is automatically cleared after reading RCREG
		//uart_isr_rx();
		char value = uart_receive_byte();

		if (header)
		{
			// header has already been received
			if (colour < NUM_COLOURS)
			{
				rgb[colour] = value;
				colour++;
			}
			//else
			//{
			//	led_off();
			//}
		}
		else if (value == HEADER)
		{
			// header has just been received
			header = true;
			colour = RED;
			//led_on();
		}
	}
}
