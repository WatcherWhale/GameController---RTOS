/**
 * \brief Initialize USART module
*/


#ifndef DRIVER_USART_H
#define DRIVER_USART_H
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include "hwconfig.h"
#include "simusart.h"

#include "FreeRTOS.h"
#include "queue.h"


/**
 * \brief Initialize USART defined in hwconfig.h, bind to stdin, stdout
*/
void DriverUSARTInit(void); 

int stdio_putchar(char c, FILE * stream);
int stdio_getchar(FILE *stream);

#endif