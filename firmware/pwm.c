#include "pwm.h"

#include <xc.h>
#include <pic16f690.h>

#include "pins.h"

static unsigned char red_counter = 0;
static unsigned char green_counter = 0;
static unsigned char blue_counter = 0;

static unsigned char red_brightness = 0;
static unsigned char green_brightness = 0;
static unsigned char blue_brightness = 0;

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
	PIE1bits.TMR2IE = 1;         // enable Timer2 interrupt

	/* Fosc = 4 MHz -> input clock = 4 Mhz / 4 = 1 MHz
	 * with a 1:1 prescaler and postscaler.
	 * 1 MHz / 75 = 13.3 kHz PWM refresh rate.
	 * We don't want the interrupt rate to be too
	 * high because it will starve the UART. */

	PR2 = 75;   // set timer period (interrupt frequency = input clock / PR2)

	// reset counters
	red_counter =  0;
	green_counter =  0;
	blue_counter =  0;

	// set all colours to be initially off
	red_brightness = 0;
	green_brightness = 0;
	blue_brightness = 0;

	// RGB //

	// set pins as outputs
	RED_TRIS = 0;
	GREEN_TRIS = 0;
	BLUE_TRIS = 0;
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

void pwm_isr(void)
{
	RED = (red_counter < red_brightness);
	GREEN = (green_counter < green_brightness);
	BLUE = (blue_counter < blue_brightness);

	red_counter++;
	green_counter++;
	blue_counter++;

	PIR1bits.TMR2IF = 0;   // clear the interrupt flag
}
