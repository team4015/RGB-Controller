#include <xc.h>
#include <pic16f690.h>
#include <stdio.h>

#include "init.h"
#include "uart.h"

void main(void)
{
	init_hardware();
	uart_init();

	while (1)
	{
		printf("Hello");
	}
}
