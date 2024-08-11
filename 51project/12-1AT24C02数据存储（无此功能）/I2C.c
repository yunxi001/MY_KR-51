#include <REGX52.H>

sbit I2C_SCL=P2^1;
sbit I2C_SDA=P2^0;

/*
概要：  I2C开始
参数：  无
返回值：无
*/

void I2C_Start(void)
{
	
	I2C_SDA=1;
	I2C_SCL=1;
	I2C_SDA=0;
	I2C_SCL=0;
}

/*
概要：  I2C停止
参数：  无
返回值：无
*/

void I2C_Stop(void)
{
	I2C_SDA=0;
	I2C_SCL=1;
	I2C_SDA=1;
}

/*
概要：  I2C发送一个字节
参数：  Byte 要发送的字节
返回值：无
*/

void I2C_SendByte(unsigned char Byte)
{
	unsigned char i;
	for (i=0;i<8;i++)
	{
		I2C_SDA=Byte&(0x80>>i);
		I2C_SCL=1;
		I2C_SCL=0;
	}
}

/*
概要：  I2C接收一个字节
参数：  无
返回值：接收到的一个字节数据
*/

unsigned char I2C_ReceiveByte(void)
{
	unsigned char i,Byte=0x00;
	I2C_SDA=1;
	for (i=0;i<8;i++)
	{
		I2C_SCL=1;
		if(I2C_SDA) {Byte|=(0x80>>i);}
		I2C_SCL=0;
	}
	return Byte;
}

/*
概要：  I2C发送应答位
参数：  ArkBit  应答位 ，0为应答，1为非应答
返回值：无
*/

void I2C_SendAck(unsigned char ArkBit)
{
	I2C_SDA= ArkBit;
	I2C_SCL=1;
	I2C_SCL=0;
}

/*
概要：  I2C接收应答位
参数：  无
返回值：接收到的应答位，0为应答，1为非应答
*/

unsigned char I2C_ReceiveAck(void)
{
	unsigned char AckBit;
	I2C_SDA=1;
	I2C_SCL=1;
	AckBit=I2C_SDA;
	I2C_SCL=0;
	return AckBit;
}

