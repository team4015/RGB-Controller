#include "led.h"

#include <xc.h>
#include <pic16f690.h>

#include "pins.h"

void led_init(void)
{
	LED_TRIS = 0;   // set LED as output
}

void led_on(void)
{
	LED = 1;
}

void led_off(void)
{
	LED = 0;
}
