#include <xc.h>
#include <pic16f690.h>
#include <stdio.h>

#include "init.h"
#include "led.h"
#include "uart.h"

void main(void)
{
	init_hardware();
	led_init();
	uart_init();

	while (1)
	{
		printf("Hello");
	}
}
