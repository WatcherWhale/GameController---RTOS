#include "DriverLed.h"

void DriverLedInit(void)
{
	PORTE.DIRSET=0b00001111;
	PORTE.PIN0CTRL=0b01000000; //Totem pole out, inverted
	PORTE.PIN1CTRL=0b01000000; //Totem pole out, inverted
	PORTE.PIN2CTRL=0b01000000; //Totem pole out, inverted
	PORTE.PIN3CTRL=0b01000000; //Totem pole out, inverted	

}

void DriverLedWrite(uint8_t LedData)
{
	PORTE.OUT=(PORTE.OUT & 0b11110000) | (LedData & 0b00001111);
}

void DriverLedSet(uint8_t LedData)
{
	PORTE.OUT=PORTE.OUT | (LedData & 0b00001111);
}

void DriverLedClear(uint8_t LedData)
{
	PORTE.OUT=PORTE.OUT & ~(LedData & 0b00001111);
}

void DriverLedToggle(uint8_t LedData)
{
	PORTE.OUT=PORTE.OUT ^ (LedData & 0b00001111);
}