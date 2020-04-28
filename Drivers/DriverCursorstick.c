#include "DriverCursorstick.h"

void DriverCursorstickInit(void)
{
	PORTD.DIRCLR=0b11110001;
	PORTD.PIN0CTRL=0b01011000; //Inverted logic, pullup
	PORTD.PIN4CTRL=0b01011000; //Inverted logic, pullup
	PORTD.PIN5CTRL=0b01011000; //Inverted logic, pullup
	PORTD.PIN6CTRL=0b01011000; //Inverted logic, pullup
	PORTD.PIN7CTRL=0b01011000; //Inverted logic, pullup
}

uint8_t DriverCursorstickGet(void)
{
	uint8_t ret=0;
	
	if (PORTD_IN & 0b00000001) ret |= CURSOR_PRESS;
	if (PORTD_IN & 0b00010000) ret |= CURSOR_RIGHT;
	if (PORTD_IN & 0b00100000) ret |= CURSOR_DOWN;
	if (PORTD_IN & 0b01000000) ret |= CURSOR_LEFT;
	if (PORTD_IN & 0b10000000) ret |= CURSOR_UP;

	return ret;
}

