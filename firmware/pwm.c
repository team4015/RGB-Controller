#include "pwm.h"

#include <xc.h>
#include <pic16f690.h>

#include "pins.h"

static unsigned char red_counter = 0;
static unsigned char green_counter = 0;
static unsigned char blue_counter = 0;

static unsigned char red_brightness = 1;
static unsigned char green_brightness = 1;
static unsigned char blue_brightness = 1;

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

	/* Fosc = 4 MHz -> input clock = 4 Mhz / 4 = 1 MHz
	 * with a 1:1 prescaler and postscaler.
	 * 1 MHz / 50 = 20 kHz PWM refresh rate.
	 * We don't want the interrupt rate to be too
	 * high because it will starve the UART. */

	PR2 = 50;   // set timer period (interrupt frequency = input clock / PR2)

	// reset counters
	red_counter =  0;
	green_counter =  0;
	blue_counter =  0;

	// set all colours to be initially off
	pwm_red(0);
	pwm_green(0);
	pwm_blue(0);

	// RGB //

	// set pins as outputs
	RED_TRIS = 0;
	GREEN_TRIS = 0;
	BLUE_TRIS = 0;
}

void __interrupt() isr(void)
{
	if (PIR1bits.TMR2IF == 1)
	{
		PIR1bits.TMR2IF = 0;   // clear the interrupt flag

		RED = (red_counter < red_brightness);
		GREEN = (green_counter < green_brightness);
		BLUE = (blue_counter < blue_brightness);

		red_counter++;
		green_counter++;
		blue_counter++;
	}
}

void pwm_red(unsigned char brightness)
{
	red_brightness = brightness;
}

void pwm_green(unsigned char brightness)
{
	green_brightness = brightness;
}

void pwm_blue(unsigned char brightness)
{
	blue_brightness = brightness;
}
