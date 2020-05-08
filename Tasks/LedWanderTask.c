#include "LedWanderTask.h"

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

#include <util/delay.h>

#include "../Drivers/DriverUSART.h"

volatile char direction[6] = {'H', 'E', 'Y', '\r', '\n', '\0'};
volatile int ledDirection = -1;
volatile int ledCounter = 0;

void InitLedWanderTask(void)
{
	xTaskCreate( LedWanderJob, "doLed", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 4, NULL );
	xTaskCreate( DirectionChangeJob, "terminal", configMINIMAL_STACK_SIZE + 512, NULL, tskIDLE_PRIORITY + 3, NULL );	
}

static void LedWanderJob(void *pvParameters)
{
	int currentLed = 0;
	TickType_t xLastWakeTime;
	const TickType_t xFrequency = portTICK_PERIOD_MS * 500;
	xLastWakeTime = xTaskGetTickCount();
	
	while (1)
	{
		currentLed = (currentLed + ledDirection);
		
		if(currentLed == -1) currentLed = 3;
		if(currentLed == 4) currentLed = 0;
		
		DriverLedWrite(1 << currentLed);
		
		
		//_delay_ms(5000);
		//vTaskDelay(portTICK_PERIOD_MS * 500);
		vTaskDelayUntil(&xLastWakeTime, xFrequency);
	}
}

static void DirectionChangeJob(void *pvParameters)
{	
	while(1)
	{
		//vTaskGetRunTimeStats(taskInfo);
		//printf(taskInfo);
		//printf("\r\n");
		
		//scanf("%s", direction);
		//printf(direction);
		
		/*if(strcmp(direction,"looplicht_links"))
		{
			ledDirection = -1;
		}
		else if(strcmp(direction, "looplicht_rechts"))
		{
			ledDirection = 1;
		}*/

		//usart_putstring(direction, 6);
		char ch = 'H';

		stdio_putchar('A', NULL);
		stdio_putchar('A', NULL);
		//usart_putchar(&ch);
		//usart_putchar('\0');
	}
}

/*
3a) _delay_ms werkt op klok cycli en niet op echte tijd

3b) Er veranderd niets beide scanf en het loop licht blijven werken.

Ik verwachtte echter iets anders, omdat de ledwander task nu een hogere prioriteit heeft en er geen vTaskDelay functie 
dat de scanf task niet meer wordt uitgevoerd

3c) vTaskDelay blocked de task als het wordt opgeroepen waardoor andere lagere prioriteits tasks ook kunnen runnen.
_delay_ms doet dit niet.

3d) vTaskDelay stopt de task voor x aantal ticks als er echter meerdere tasks zijn kan dit ervoor zorgen dat de periode niet exact 500 ms is.
vTaskDelayUntil verzekerd dat dit altijd gebeurt omdat het de tijd opslaagt wanneer de laatste call gebeurt is.

3e) Nu houdt de scheduler geen rekening meer met de prioriteit van de tasks. Er wordt nu enkel nog naar de scanf gekeken want deze wacht op een SYSCALL
*/