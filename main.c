#include "hwconfig.h"

#include "DriverSysClk.h"
#include "DriverUSART.h"
#include "DriverCursorStick.h"
#include "DriverAdc.h"
#include "DriverLed.h"
#include "Driverpl9823.h"

#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>

int main(void)
{
	DriverSysClkXtalInit();	//Clock init
	DriverUSARTInit();		//USART init and link to stdio
	DriverCursorstickInit();//Initialize cursor stick
	DriverLedInit();		//Initialize LED's
	DriverAdcInit();		//Initialize ADC driver

	//Enable interrupts
	PMIC.CTRL=0b111;		
	sei();

	_delay_ms(10);

	while(1)
	{
		
	}

	return 0;
}


