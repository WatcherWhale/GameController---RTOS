#ifndef RLIGHT_H
#define RLIGHT_H
#include <stdint.h>
void InitRlight(void);

volatile extern uint8_t RlightDir; //0=left, 1=right

#endif