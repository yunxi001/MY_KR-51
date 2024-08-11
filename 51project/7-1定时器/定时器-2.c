#include <REGX52.H>
#include <INTRINS.H>

unsigned char keyNum;

void Timer0Init(void){
 //为了不干扰定时器1
 //TMOD &= 0xF0;  //设置定时器模式
 //TMOD |= 0x01;  //设置定时器模式
 
 TMOD = 0x01;
 //TL0低8位，TH0高8位
 TL0 = 0x66;		//设置定时初值
	TH0 = 0xFC;		//设置定时初值
 //距离65535差1000，一次1us，1000次就是1ms
 
 //TCON配置
 TF0 = 0;  //清除TF0标志
 TR0 = 1;  //定时器0开始计时
 
 //中断配置
 ET0=1; //enable time0 interrupt
 EA=1; //enable global interrupt switch
 PT0=0;//低优先级
 
 
}


void main()
{
//P1=0xFE;
 Timer0Init();
 
 while(1)
 {
  
 }
}


void Timer0_Routine() interrupt 1{
 static unsigned int c = 0;
 TL0 = 0x66;		//设置定时初值
	TH0 = 0xFC;		//设置定时初值
 c++;
 
 //500ms
 if(c>=500){
  c=0;
  //循环左移
 //P1=_crol_(P2,1); //LED输出
	 P1_0=~P1_0;
 }
 
}