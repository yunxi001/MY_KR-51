#include <REGX52.H>

sbit SPT2406_CS=P3^5;
sbit SPT2406_DCLK=P3^6;
sbit SPT2406_DIN=P3^4;
sbit SPT2406_DOUT=P3^7;

unsigned int XPT2046_ReadAD(unsigned char Command)
{
	unsigned char i;
	unsigned int ADVAlue;
	XPT2046_DCLK=0;
	SPT2406_CS=0;
	
	for(i=0;i<8;i++)
	{
		SPT2406_DIN=Command&(0x80>>i);
		SPT2406_DCLK=1;
		SPT2406_DCLK=0;
	}
		for(i=0;i<16;i++)
	{
	
		SPT2406_DCLK=1;
		SPT2406_DCLK=0;
		SPT2406_DOUT=ADVAlue|=(0x8000>>i);
	}
	SPT2406_CS=1;
	if(Command&0x08)
	{
		return ADVAlue>>8;
	}
	else
	{
		return ADVAlue>>4;
	}

	
}
