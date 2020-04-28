#include "hwconfig.h"
#include "DriverDbgUSART.h"

#include <stdio.h>

#include "FreeRTOS.h"
#include "task.h"

#include <avr/io.h>
#include <util/delay.h>

#define CFG_ERR_LED() PORTE.DIRSET=1<<0
#define SET_ERR_LED() PORTE.OUTSET=1<<0
#define CLR_ERR_LED() PORTE.OUTCLR=1<<0

void vApplicationIdleHook( void )
{
	
}

void vApplicationMallocFailedHook(void)
{
	taskDISABLE_INTERRUPTS();
	DbgPrint ("ERROR: memory allocation failed\r\n");
	CFG_ERR_LED();
	while (1)
	{
		SET_ERR_LED();
		_delay_ms(100);
		CLR_ERR_LED();
		_delay_ms(100);
	}
}



void vApplicationStackOverflowHook( TaskHandle_t xTask,signed char *pcTaskName )
{
	char Dbg[128];
	taskDISABLE_INTERRUPTS();
	CFG_ERR_LED();
	snprintf(Dbg,128,"STACK overflow in task %s\r\n",pcTaskName);
	DbgPrint(Dbg);
	while (1)
	{
		SET_ERR_LED();
		_delay_ms(500);
		CLR_ERR_LED();
		_delay_ms(500);
	}
}

void vAssertCalled( char *File, int Line)
{
	char Dbg[128];
	taskDISABLE_INTERRUPTS();	
	CFG_ERR_LED();
	snprintf(Dbg,128,"Assert in file %s, line nr %d\r\n",File,Line);
	DbgPrint(Dbg);
	while (1)
	{
		SET_ERR_LED();
		_delay_ms(100);
		CLR_ERR_LED();
		_delay_ms(500);
	}
}