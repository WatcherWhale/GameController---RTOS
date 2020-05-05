#include "hwconfig.h"

#include "FreeRTOS.h"
#include "task.h"

#include "DriverSysClk.h"
#include "DriverUSART.h"
#include "DriverCursorStick.h"
#include "DriverPower.h"
#include "DriverAdc.h"
#include "DriverLed.h"
#include "Driverpl9823.h"

#include "transfertask.h"

#include <util/delay.h>
#include <avr/interrupt.h>

#include <stdio.h>

int main(void)
{
	DriverSysClkXtalInit();	//Clock init
	DriverUSARTInit();		//USART init and link to stdio
	DriverCursorstickInit();//Initialize cursor stick
	DriverLedInit();		//Initialize LED's
	DriverPowerInit();		//Initialize aux power driver
	DriverAdcInit();		//Initialize ADC driver
	DriverPL9823Init();		//Initialize RGB LED driver


	//Enable interrupts
	PMIC.CTRL=0b111;		
	sei();

	_delay_ms(10);

	//Init tasks
	InitTransferTasks();

	
	vTaskStartScheduler();	//Start scheduler loop

	return 0;
}


