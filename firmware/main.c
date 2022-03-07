#include <xc.h>
#include <pic16f690.h>

#include "init.h"
#include "led.h"
#include "uart.h"
#include "pwm.h"

void main(void)
{
	init_hardware();
	led_init();
	uart_init();
	pwm_init();

	pwm_green(255);
	pwm_red(255);
	pwm_blue(255);

	while (1)
	{
		uart_echo();
	}
}
