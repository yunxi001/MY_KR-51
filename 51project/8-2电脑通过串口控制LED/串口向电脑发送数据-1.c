#include <REGX52.H>
#include "Delay.h"
#include "Uart.h"


void main()
{
 Uart_Init();

	while(1)
	{
		
	}
}
void Uart_Routine() interrupt 4
{
	if(RI==1)
	{
		P1=~SBUF;
		Uart_SendByte(SBUF);
		RI=0;
	}
}