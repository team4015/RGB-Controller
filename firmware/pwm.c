#include "pwm.h"

#include <xc.h>
#include <pic16f690.h>

#include "led.h"

char counter = 0;
char target = 128;

void pwm_init(void)
{
	// TIMER 2 //

	/* The Timer2 value is saved in TMR2.  It takes
	 * (Fosc / 4) * prescaler as input and compares
	 * TMR2 to PR2.  TMR2 always resets to 0 and
	 * increments until it matches PR2 (after postscaler).
	 * When matched, the PIR1.TMR2IF interrupt flag
	 * is set and must be manually cleared. */

	T2CONbits.TMR2ON = 1;        // turn on timer
	T2CONbits.T2CKPS = 0b00;     // 1:1 prescaler
	T2CONbits.TOUTPS = 0b0000;   // 1:1 postscaler

	INTCONbits.GIE = 1;    // enable global interrupts
	INTCONbits.PEIE = 1;   // enable peripherial interrupts
	PIE1bits.TMR2IE = 1;   // enable Timer2 interrupt

	PR2 = 120;   // set period to 1 (interrupt frequency = (Fosc / 4) * PR2)

	counter = 0;
}

void __interrupt() isr(void)
{
    if (PIR1bits.TMR2IF == 0)
	{
		return;
	}

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

