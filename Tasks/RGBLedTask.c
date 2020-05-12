#include "RGBLedTask.h"
#include "../Drivers/Driverpl9823.h"

static void RGBLedJob(void *pvParameters);

void InitRGB(void)
{
	DriverPL9823Init();
	xTaskCreate( RGBLedJob, "doRGB", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY, NULL );
}

static void RGBLedJob(void *pvParameters)
{
	while(1)
	{
		DriverPL9823Set(PL9823_RED, PL9823_RED, PL9823_RED, PL9823_RED);
	}
}