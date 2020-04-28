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

#include "LedWander.h"

char direction[18];
volatile int currentLed = 0;
volatile int ledDirection = 1;
volatile int ledCounter = 0;

int main(void)
{
	DriverSysClkXtalInit();	//Clock init
	DriverUSARTInit();		//USART init and link to stdio
	DriverCursorstickInit();//Initialize cursor stick
	DriverLedInit();		//Initialize LED's
	DriverAdcInit();		//Initialize ADC driver

	//Enable interrupts
	PMIC.CTRL = 0b111;		
	sei();
	
	initLedWander();

	_delay_ms(10);

	while(1)
	{
		//scanf("%s", direction);
		//DriverLedWrite(1 << currentLed);
	}

	return 0;
}

void initLedWander(void)
{
	TCC0.PER = 4095;
	TCC0.CTRLA = 1; // Set Prescaler => 1
	TCC0.CTRLB = 0; // Set Normal Mode
	TCC0.CTRLC = 0; // Not used
	TCC0.CTRLD = 0;
	TCC0.CTRLE = 0;
	
	TCC0.INTCTRLA = 0b11;
	
	DriverLedWrite(1 << currentLed);
}

ISR(TCC0_OVF_vect)
{
	ledCounter++;
	
	if(ledCounter == 3000)
	{
		currentLed = (currentLed + ledDirection) % 4;
		DriverLedWrite(1 << currentLed);
		
		ledCounter = 0;
	}
}


