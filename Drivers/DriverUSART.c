#include "DriverUSART.h"

static FILE UsartStdio = FDEV_SETUP_STREAM(stdio_putchar, stdio_getchar,_FDEV_SETUP_RW);
static volatile QueueHandle_t usartTXCQueue;
static volatile int sendByte = 0;
static volatile BaseType_t isBusy = pdFALSE;

void DriverUSARTInit(void)
{
	USART_PORT.DIRSET=0b00001000;	
	USART_PORT.DIRCLR=0b00000100;
	
	USART.CTRLA = 0b00111100;
	USART.CTRLB = 0b00011000;
	USART.CTRLC = 0b00000011;	
	
	USART.BAUDCTRLA=0xE5; //BSEL=3301, BSCALE=-5 19200 baud
	USART.BAUDCTRLB=0xBC;
	
	stdout=&UsartStdio;
	stdin=&UsartStdio;
	
	usartTXCQueue = xQueueCreate(100, sizeof(char));
}

int stdio_putchar(char c, FILE * stream)
{
	if(uxQueueMessagesWaiting(usartTXCQueue) == 0 && isBusy == pdFALSE)
	{
		USART.DATA = c;
		isBusy = pdTRUE;
	}
	else
	{
		xQueueSendToBack(usartTXCQueue, &c, 1);
	}
	
	return 0;
}
	
int stdio_getchar(FILE *stream)
{
	return SimUsartGetChar();
}

ISR(USART_TXC_vect)
{
	char ch;
	BaseType_t wokenToken = pdFALSE;
	
	USART.STATUS = 0b01000000;
	
	if(xQueueIsQueueEmptyFromISR(usartTXCQueue) == pdFALSE)
	{
		xQueueReceiveFromISR(usartTXCQueue, &ch, &wokenToken);
		USART.DATA = ch;
	}
	else
	{
		isBusy = pdFALSE;
	}
}
