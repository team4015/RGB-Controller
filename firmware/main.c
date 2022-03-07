#include <xc.h>
#include <pic16f690.h>
#include <stdio.h>

#include "init.h"
#include "led.h"
#include "uart.h"
#include "pwm.h"

/* The PIC will only receive 3 bytes
 * at a time.  These bytes will be
 * interpreted as brightness values
 * for red, green, and blue. Therefore,
 * values should be sent in this order. */

enum Colour
{
	RED,
	BLUE,
	GREEN,

	NUM_COLOURS
};

void main(void)
{
	init_hardware();
	led_init();
	uart_init();
	pwm_init();

	unsigned char rgb [NUM_COLOURS];

	while (1)
	{
		uart_receive(rgb, NUM_COLOURS);

		pwm_green(rgb[RED]);
		pwm_red(rgb[GREEN]);
		pwm_blue(rgb[BLUE]);
	}
}
