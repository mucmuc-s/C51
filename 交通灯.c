#include<reg51.h>
sbit ewr=P3^3;
sbit ewy=P3^4;
sbit ewg=P3^5;

sbit snr=P3^0;
sbit sny=P3^1;
sbit sng=P3^2;

sbit bit_0=P2^0;
sbit bit_1=P2^1;

sbit k1=P2^2;
sbit k2=P2^3;
sbit k3=P2^4;
sbit k4=P2^5;

int sec=20;
int pause=0;
int situation=1;
int mid=20;
int lightnum=0;
char duanxuan[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};
void delay(int x)
{
  while(x--);
}
void dialed()
{
    if(situation==1||situation==2)
	{
	  	bit_0=0;
		bit_1=1;
		P0=duanxuan[sec%10]; 
		delay(100);
		P0=0x00;
		if(sec>7)
		{
		  P1=duanxuan[(sec-7)%10];
		  delay(100);
		  P1=0x00;
		}
		else
		{
		  P1=duanxuan[sec%10];
		  delay(100);
		  P1=0x00;
		}       
	
	
	
		bit_0=1;
		bit_1=0;
		P0=duanxuan[sec/10]; 
		delay(100);
		P0=0x00;
		if(sec>7)
		{
		  P1=duanxuan[(sec-7)/10];
		  delay(100);
		  P1=0x00;
		}
		else
		{
		  P1=duanxuan[sec/10];
		  delay(100);
		  P1=0x00;
		}      
	}
   


    else if(situation==3||situation==4)
	{
	  	bit_0=0;
		bit_1=1;
		P1=duanxuan[sec%10]; 
		delay(100);
		P1=0x00;
		if(sec>7)
		{
		  P0=duanxuan[(sec-7)%10];
		  delay(100);
		  P0=0x00;
		}
		else
		{
		  P0=duanxuan[sec%10];
		  delay(100);
		  P0=0x00;
		}       
	
	
	
		bit_0=1;
		bit_1=0;
		P1=duanxuan[sec/10]; 
		delay(100);
		P1=0x00;
		if(sec>7)
		{
		  P0=duanxuan[(sec-7)/10];
		  delay(100);
		  P0=0x00;
		}
		else
		{
		  P0=duanxuan[sec/10];
		  delay(100);
		  P0=0x00;
		} 
	}

}


void led()
{
  switch(situation)
  {
   case 1:
         {
		      if((sec>7)&&((sec-7)<=5))
			  {
			      return ;
			  }
		      ewr=1;
			  ewy=1;
			  ewg=0;
			
			  snr=0;
			  sny=1;
			  sng=1;
			  break;
		 }
    case 2:
	      {
		      if((sec<=5))
			  {
			    return ;
			  }
		      ewr=1;
			  ewy=0;
			  ewg=1;
			
			  snr=0;
			  sny=1;
			  sng=1;
			  break;
		  }
	case 3:
	       {
		      if((sec>7)&&((sec-7)<=5))
			  {
			      return ;
			  }
		      ewr=0;
			  ewy=1;
			  ewg=1;
			
			  snr=1;
			  sny=1;
			  sng=0;
			  break;
		   }
	case 4:
	       {
		      if((sec<=5))
			  {
			    return ;
			  }
		      ewr=0;
			  ewy=1;
			  ewg=1;
			
			  snr=1;
			  sny=0;
			  sng=1;
			  break;
		   }
	case 5:
	       {
		     situation=1;
		   }
  }
}




void twinkle()
{
   if((situation==1||situation==3)&&(sec>7)&&((sec-7)<=5))
   {
      if(situation==1)
	  {
	    ewg=~ewg;
	  }
	  else if(situation==3)
	  {
	    sng=~sng;
	  }

   }
   else if((situation==2||situation==4)&&(sec<=5))
   {
     if(situation==2)
	 {
	   	ewy=~ewy;
		snr=~snr;
	 }
	 else if(situation==4)
	 {
	   	 ewr=~ewr;
		 sny=~sny;
	 }
   }
}






void key()
{
    static int k=0;
	if(k==0&&k4==0)
	{
	  TR0=~TR0;
	  k=1;
	}		
	if(k==0&&TR0==0&&k2==0)
	{
	  sec+=1;
	  mid=sec;
	  k=1;
	}
	if(k==0&&TR0==0&&k3==0)
	{
	  sec-=1;
	  mid=sec;
	  k=1;
	}
	if(k==0&&TR0==0&&k1==0)
	{
	  situation++;
	  k=1;
	}
	if(k1==1&&k2==1&&k3==1&&k4==1)
	{
	  k=0;
	}
}



int main()
{
  TMOD=0x01;
  TH0=0x3C;
  TL0=0xB0;
  EA=1;
  ET0=1;
  TR0=1;
  while(1)
  {
     led();
     dialed();
	 key();
  }
}


void timer0() interrupt 1
{
  TH0=0x3C;
  TL0=0xB0;
  pause++;
  if(pause==20)
  {
    pause=0;
	sec--;
	if((sec-7)==0)
	{
	  situation++;
	}
	if(sec==0)
	{
	  situation++;
	  sec=mid;
	}
	twinkle();
  }
}


