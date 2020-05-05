#include "transfertask.h"
#include "hwconfig.h"

#include "util/delay.h"

#include <stdio.h>

#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"



volatile static uint32_t Data=0;
volatile static SemaphoreHandle_t mutexHandle;

//Private function prototypes
void WorkerSendTask(void *pvParameters);
void WorkerReceiveTask(void *pvParameters);

//Function definitions
void InitTransferTasks()
{
	mutexHandle = xSemaphoreCreateMutex();
	xTaskCreate( WorkerSendTask, "sendtask", 256, NULL, tskIDLE_PRIORITY+1, NULL );
	xTaskCreate( WorkerReceiveTask, "receivetask", 256, NULL, tskIDLE_PRIORITY+1, NULL );
}

void WorkerSendTask(void *pvParameters)
{	
	while (1)
	{
		taskENTER_CRITICAL();
		Data=0x10101010;	
		taskEXIT_CRITICAL();
		
		taskENTER_CRITICAL();
		Data=0x20202020;	
		taskEXIT_CRITICAL();
	}
}

void WorkerReceiveTask(void *pvParameters)
{
	uint32_t time1, time2;
	
	while(1)
	{
		time1 = portGET_RUN_TIME_COUNTER_VALUE();
		
		taskENTER_CRITICAL();
		if (Data!=0x10101010 && Data!=0x20202020) printf ("Invalid Data value:%lx \r\n",Data);
		else printf ("OK\r\n");
		taskEXIT_CRITICAL();
		
		time2 = portGET_RUN_TIME_COUNTER_VALUE();
		
		if(time1 < time2)
		{
			printf("%u\r\n", time2 - time1);
		}
		else
		{
			printf("%u\r\n", time1 - time2);
		}
	}
}

/*
5a) Volatile zorgt ervoor dat er geen compiler optimalisaties werken op reads en writes op deze variabele. 
Dit zorgt ervoor dat er geen read en writes worden genegeerd.

5b) Omdat af en toe het geheugen wordt gelezen terwijl dat de andere task nog bezig is met schrijven.
Hierdoor zie je combinaties van de twee getallen verschijnen

5c)
Semaphore = 17276
Enter/Exit Critical = 47015
*/