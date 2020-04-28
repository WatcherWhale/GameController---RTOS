#include "DriverMotor.h"
#include <avr/interrupt.h>
#include <stdio.h>
#include <stdint.h>

#include "DriverLed.h"


//Private variables
volatile uint16_t Cnt1,Cnt2;

void DriverMotorInit(void)
{
	//GPIO init
	PORTF.DIRSET=0b11111;
	PORTF.PIN4CTRL=0b01000000; //Invert
	PORTF.OUTSET=0b10000; //Sleep enable
	
	//Timer init, hbridge
	TCF0.CTRLA=0b00000001; //DIV1
	TCF0.CTRLB=0b11110011; //OCA,OCB,OCC,OCD enable, SS PWM
	TCF0.PER=4096; //7812 Hz PWM
	
	//Encoder 1A, 1B
	PORTC.DIRCLR=0b11000000;
	PORTC.PIN6CTRL=0b01000000; //any edge detect
	PORTC.PIN7CTRL=0b01000000; //any edge detect
	PORTC.INT0MASK=1<<6;
	PORTC.INT1MASK=1<<7;
	PORTC.INTCTRL=0b0101;

	//Encoder 2A, 2B
	PORTE.DIRCLR=0b00110000;
	PORTE.PIN4CTRL=0b01000000; //any edge detect
	PORTE.PIN5CTRL=0b01000000; //any edge detect
	PORTE.INT0MASK=1<<4;
	PORTE.INT1MASK=1<<5;
	PORTE.INTCTRL=0b0101;
}


void DriverMotorSet(int16_t MotorLeft,int16_t MotorRight)
{
	//Sleep mode handling
	if (MotorLeft==0 && MotorRight==0)
	PORTF.OUTSET=0b10000; //DRV8833 in sleep mode
	else
	PORTF.OUTCLR=0b10000; //DRV8833 in active mode
	
	//Left motor
	if (MotorLeft>0)
	{
		if (MotorLeft>4095) MotorLeft=4095;
		TCF0.CCA=0;
		TCF0.CCB=MotorLeft;
	}
	else
	{
		if (MotorLeft<-4095) MotorLeft=-4095;
		TCF0.CCA=-MotorLeft;
		TCF0.CCB=0;
	}

	//Right motor
	if (MotorRight>0)
	{
		if (MotorRight>4095) MotorRight=4095;
		TCF0.CCC=0;
		TCF0.CCD=MotorRight;
	}
	else
	{
		if (MotorRight<-4095) MotorRight=-4095;
		TCF0.CCC=-MotorRight;
		TCF0.CCD=0;
	}
	
}


EncoderStruct DriverMotorGetEncoder(void)
{
	EncoderStruct EncoderInfo;
	cli();
	EncoderInfo.Cnt1=Cnt1;
	EncoderInfo.Cnt2=Cnt2;
	sei();
	return EncoderInfo;
}

//Encoder 1 ISR's
ISR (PORTC_INT0_vect)
{
	uint8_t Data,l0,l1;
	Data=PORTC.IN;
	l0=Data & (1<<6);
	l1=Data & (1<<7);
	if ( l0 && !l1) Cnt1++; //Rising edge on Line0, Line1 low
	if ( l0 &&  l1) Cnt1--; //Rising edge on Line0, Line1 high
	if (!l0 &&  l1) Cnt1++; //Falling edge on Line0, Line1 high
	if (!l0 && !l1) Cnt1--;//Falling edge on Line1, Line1 low
}

ISR (PORTC_INT1_vect)
{
	uint8_t Data,l0,l1;
	Data=PORTC.IN;
	l0=Data & (1<<6);
	l1=Data & (1<<7);
	if ( l1 && !l0) Cnt1--;//Rising edge on Line1, Line0 low
	if ( l1 &&  l0) Cnt1++;//Rising edge on Line1, Line0 high
	if (!l1 &&  l0) Cnt1--;//Falling edge on Line1, Line0 high
	if (!l1 && !l0) Cnt1++;//Falling edge on Line1, Line0 low
}

//Encoder 2 ISR's
ISR (PORTE_INT0_vect)
{
	uint8_t Data,l0,l1;
	Data=PORTE.IN;
	l0=Data & (1<<4);
	l1=Data & (1<<5);
	if ( l0 && !l1) Cnt2++; //Rising edge on Line0, Line1 low
	if ( l0 &&  l1) Cnt2--; //Rising edge on Line0, Line1 high
	if (!l0 &&  l1) Cnt2++; //Falling edge on Line0, Line1 high
	if (!l0 && !l1) Cnt2--;//Falling edge on Line1, Line1 low
}

ISR (PORTE_INT1_vect)
{
	uint8_t Data,l0,l1;
	Data=PORTE.IN;
	l0=Data & (1<<4);
	l1=Data & (1<<5);
	if ( l1 && !l0) Cnt2--;//Rising edge on Line1, Line0 low
	if ( l1 &&  l0) Cnt2++;//Rising edge on Line1, Line0 high
	if (!l1 &&  l0) Cnt2--;//Falling edge on Line1, Line0 high
	if (!l1 && !l0) Cnt2++;//Falling edge on Line1, Line0 low
}