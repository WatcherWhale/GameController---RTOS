#include "LedWanderTask.h"

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

#include <util/delay.h>

volatile char direction[20];
volatile int currentLed = 0;
volatile int ledDirection = -1;
volatile int ledCounter = 0;

void InitLedWanderTask(void)
{
	xTaskCreate( LedWanderJob, "ledwander", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY+3, NULL );
	xTaskCreate( DirectionChangeJob, "directionchange", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY+3, NULL );	
}

static void LedWanderJob(void *pvParameters)
{
	while (1)
	{
		currentLed = (currentLed + ledDirection);
		
		if(currentLed == -1) currentLed = 3;
		if(currentLed == 4) currentLed = 0;
		
		DriverLedWrite(1 << currentLed);
		
		_delay_ms(500);
	}
}

static void DirectionChangeJob(void *pvParameters)
{
	while(1)
	{
		scanf("%s", direction);
		
		if(strcmp(direction,"looplicht_links"))
		{
			ledDirection = -1;
		}
		else if(strcmp(direction, "looplicht_rechts"))
		{
			ledDirection = 1;
		}
	}
}
