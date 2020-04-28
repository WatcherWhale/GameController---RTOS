#include "hwconfig.h"
#include <util/delay.h>
#include "simusart.h"
#include "DriverCursorstick.h"
#include <stdlib.h>


char LeftString[]="looplicht_links\r\n";
char RightString[]="looplicht_rechts\r\n";


char SimUsartGetChar()
{
	static char *StrPtr=NULL;

	if (StrPtr!=NULL && *StrPtr=='\0') //Handle end of string
	{
		_delay_ms(500);
		StrPtr=NULL;
	}
	
	while (StrPtr==NULL)
	{
		if (DriverCursorstickGet()==CURSOR_LEFT) StrPtr=LeftString;
		if (DriverCursorstickGet()==CURSOR_RIGHT) StrPtr=RightString;	
	}
	
	return *StrPtr++;
}