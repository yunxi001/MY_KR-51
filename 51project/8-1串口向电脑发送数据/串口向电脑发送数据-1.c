#include <REGX52.H>
#include "Delay.h"
#include "Uart.h"
unsigned char Num;

void main()
{
 Uart_Init();

	while(1)
	{
		Uart_SendByte(Num);
		Num++;
		Delay(1000);
	}
}