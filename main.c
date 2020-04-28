#include "hwconfig.h"

#include "FreeRTOS.h"
#include "task.h"

#include "DriverSysClk.h"
#include "DriverUSART.h"
#include "DriverCursorStick.h"
#include "DriverAdc.h"
#include "DriverLed.h"
#include "DriverPl9823.h"

#include <util/delay.h>
#include <avr/interrupt.h>

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

	//Init tasks


	vTaskStartScheduler();	//Start scheduler loop

	return 0;
}


