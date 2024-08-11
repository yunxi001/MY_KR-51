#include <REGX52.H>
#include "Delay.h"
#include "Uart.h"

sbit  hw=P3^2;

void main()
{
	unsigned char i;
 Uart_Init();
 
	while(1)
	{
		if(hw==0) {i=0;}
		if(hw==1) {i=1;}
		Uart_SendByte(hw);
		Delay(1000);
	}
}