#include <reg51.h>	

void delayms(unsigned char ms)	
{						
	unsigned char i;
	while(ms--)
	{
		for(i = 0; i < 120; i++);
	}
}

main()
{
	unsigned char LED;
	LED = 0xfe;	  
 	while(1)
	{
	      
    	 P1 = LED;
		 delayms(250);
		 LED = LED << 1;   
		 if(LED == 0x00 )	 
		 { P1 = LED; LED = 0xfe;  delayms(250);  } 
	}
}






