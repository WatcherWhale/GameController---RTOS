#include "RGBLedTask.h"
#include "../Drivers/Driverpl9823.h"

static void RGBLedJob(void *pvParameters);

void InitRGB(void)
{
	DriverPL9823Init();
	//xTaskCreate( RGBLedJob, "doRGB", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY, NULL );
}

static void RGBLedJob(void *pvParameters)
{
	while(1)
	{
		taskENTER_CRITICAL();
		DriverPL9823Set(PL9823_RED, PL9823_RED, PL9823_RED, PL9823_RED);
		taskEXIT_CRITICAL();
	}
}


/*
7b) Jitter = 3185824
	Max    = 3185835
	
7c) Omdat de andere task deze blocked en daardoor niet de juiste bitsequentie wordt doorgestuurd

7d) Jitter = 3184848
	Max    = 3184835
	
7e) De Jitters blijven precies altijd hetzelfde alleen toen we een extra taak toevoegde kwam er extra jitter bij.

*/