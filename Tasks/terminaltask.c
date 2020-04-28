#include "terminaltask.h"
#include "rlighttask.h"
#include "hwconfig.h"

#include "util/delay.h"

#include <string.h>
#include <stdio.h>

#include "FreeRTOS.h"
#include "task.h"

#include "DriverLed.h"


//Private function prototypes
void WorkerTerminal(void *pvParameters);

//Function definitions
void InitTerminal()
{
	xTaskCreate( WorkerTerminal, "terminal", 1024, NULL, tskIDLE_PRIORITY+1, NULL );
}

void WorkerTerminal(void *pvParameters)
{
	int Dir;
	char s[64];
	char sbuf[512];
	while(1)
	{
		printf ("CMD>");
		scanf ("%s",s);		
		if (!strcmp(s,"looplicht_links")) RlightDir=0;
		if (!strcmp(s,"looplicht_rechts")) RlightDir=1;
		printf ("\r\n");
		vTaskGetRunTimeStats(sbuf);
		puts(sbuf);
		
	}
}