#include<REGX52.H>
#include<INTRINS.H>
void Delay500ms()		//@11.0592MHz
{
	unsigned char i, j, k;

	_nop_();
	i = 4;
	j = 129;
	k = 119;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}

void main()
{
	
	while(1)
	{
		P1=0xFE;//1111 1110
		Delay500ms();
		P1=0xFF;//1111 1111
		Delay500ms();
	}
}