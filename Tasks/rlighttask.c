#include "hwconfig.h"

#include "util/delay.h"

#include "rlighttask.h"

#include "FreeRTOS.h"
#include "task.h"

#include "DriverLed.h"


volatile uint8_t RlightDir=1;

//Private function prototypes
void WorkerRLight(void *pvParameters);

//Function definitions
void InitRlight()
{
	xTaskCreate( WorkerRLight, "rlight", 256, NULL, tskIDLE_PRIORITY+2, NULL );	
}

void WorkerRLight(void *pvParameters)
{
	uint8_t Leds=1;
	TickType_t xLastWakeTime;
	const TickType_t xPeriod = 500;
	
	xLastWakeTime=xTaskGetTickCount();
	while(1)
	{
		DriverLedWrite(Leds);
		if (RlightDir==0)
		{
			Leds>>=1;
			if (Leds==0) Leds=0b1000;
		}
		else
		{
			Leds<<=1;
			if (Leds==0b10000) Leds=1;
		}
		vTaskDelayUntil( &xLastWakeTime, xPeriod );
	}
}


