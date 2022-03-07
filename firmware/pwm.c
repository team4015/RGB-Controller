#include "pwm.h"

#include <xc.h>
#include <pic16f690.h>

#include "led.h"

char counter = 0;
char target = 0;

void pwm_init(void)
{
	// TIMER 2 //

	/* The Timer2 value is saved in TMR2.  It takes
	 * (Fosc / 4) * prescaler as input and compares
	 * TMR2 to PR2.  TMR2 always resets to 0 and
	 * increments until it matches PR2 (after postscaler).
	 * When they match the PIR1.TMR2IF interrupt flag
	 * is set and must be cleared manually. */

	T2CONbits.TMR2ON = 1;        // turn on timer
	T2CONbits.T2CKPS = 0b00;     // 1:1 prescaler
	T2CONbits.TOUTPS = 0b0000;   // 1:1 postscaler

	INTCONbits.GIE = 1;    // enable global interrupts
	INTCONbits.PEIE = 1;   // enable peripherial interrupts
	PIE1bits.TMR2IE = 1;   // enable Timer2 interrupt

	PR2 = 50;   // set period to 50 (interrupt frequency = input clock / PR2)

	/* Fosc = 4 MHz -> input clock = 4 Mhz / 4 = 1 MHz
	 * 1 MHz / 50 = 20 kHz PWM refresh rate.
	 * We don't want the interrupt rate to be too
	 * hight because it will starve the UART. */

	counter = 0;   // reset counter
}

void __interrupt() isr(void)
{
	if (PIR1bits.TMR2IF == 1)
	{
		PIR1bits.TMR2IF = 0;   // clear the interrupt flag

		if (counter < target)
		{
			led_on();
		}
		else
		{
			led_off();
		}

		counter++;
	}
}
