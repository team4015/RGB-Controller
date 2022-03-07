#include "pwm.h"

#include <xc.h>
#include <pic16f690.h>

#include "uart.h"
#include "led.h"

char counter = 0;
char target = 1;

void pwm_init(void)
{
	// TIMER 0 //

	/* Timer0 is incremented on every clock cycle.
	 * INTCON.T0IF is set whenever TMR0 overflows
	 * from 255 to 0 and must be cleared manually. */

	OPTION_REGbits.T0CS = 0;     // set timer clock source to (Fosc / 4) -> 1 MHz
	OPTION_REGbits.PSA = 0;      // assign prescaler to Timer0 instead of WDT
	OPTION_REGbits.PS = 0b0;   // 1:2 prescaler

	INTCONbits.GIE = 1;    // enable global interrupts
	INTCONbits.T0IE = 1;   // enable interrupts when Timer0 overflows
	INTCONbits.T0IF = 0;   // clear interrupt flag bit

	counter = 0;
}

void __interrupt() isr(void)
{
    if (INTCONbits.T0IF == 0)
	{
		return;
	}

	INTCONbits.T0IF = 0;   // clear the interrupt flag
	if (counter == 0)
	{
		led_on();
	}
	else if (counter == target)
	{
		led_off();
	}
	uart_transmit_byte('X');

	counter++;
}

