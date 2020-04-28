#include "DriverAdc.h"
#include <avr/io.h>
#include <avr/interrupt.h>

void DriverAdcInit(void)
{
	ADCA.CTRLA=0b00000001; //Enable ADC
	ADCA.CTRLB=0b00000110; //Manual mode, 12 bit left justified
	ADCA.REFCTRL=0b00000010; //1.00V internal reference, enable bandgap
	ADCA.PRESCALER=0b00000011; //DIV32; 1MHz ADCClk. Should be lower than 1,8MHz per spec
	ADCA.CH0.INTCTRL=0b01; //Lo pri int
}

int16_t DriverAdcGetCh(uint8_t PinPos,uint8_t PinNeg)
{
	int16_t Res;
	
	//Configure channels
	if (PinPos<16 && PinPos>=0)
	ADCA.CH0.MUXCTRL=PinPos<<3;
	else
	return 10000; //Invalid settings

	if (PinNeg==-1)
	{
		ADCA.CH0.CTRL=0b00000001; //Single ended mode, no gain
		ADCA.CTRLB&=~0b00010000;  //Unsigned mode
	}
	else if (PinNeg>=0 && PinNeg<4)
	{
		ADCA.CH0.CTRL=0b00000010; //Differential mode, no gain
		ADCA.CTRLB|=0b00010000;   //Signed mode
		ADCA.CH0.MUXCTRL|=PinNeg;
	}
	else if (PinNeg>=4 && PinNeg<8)
	{
		ADCA.CH0.CTRL=0b00000011; //Differential mode, 1X gain
		ADCA.CTRLB|=0b00010000;
		ADCA.CH0.MUXCTRL|=(PinNeg-4);
	}
	else return 10000; //Invalid settings
	
	//Start measurement
	ADCA.INTFLAGS=1;
	ADCA.CH0.CTRL|=0b10000000; //Start conversion
	while (!(ADCA.INTFLAGS & 1)); //Wait for conversion complete
	
	Res=ADCA.CH0.RES;

	return Res;
}