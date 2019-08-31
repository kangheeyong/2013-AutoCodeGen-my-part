#include "ACG_TIM.h"

#define SYSCLK      16

static long TCNT_val[4] = {0};
static long before_period[4] = {0};
static char prescaler[4] = {0};  




//Timer0 Setting  10ms까지 설정할 수 있음 
void AcgTIMER0_Setting(long period)
{
    long sysclk = SYSCLK;
    long temp= 0;
    
    if(before_period[0] != period)  
    {
        before_period[0] = period;

		//period를 만들 수 있는 분주비를 찾는다.
        while(1)
        {               
                if( period >= 4000 && temp <= 10000 ) 
               {             
                     temp = ( long)(period*sysclk/1024);  
                     TCNT_val[0] = 255 - temp;
                     prescaler[0] = 0x07;
                     break;
               }
               
                
               if(  period >= 1000 && temp < 4000 ) 
               {          
                     temp = ( long)((period*sysclk)/256); 
                     TCNT_val[0] = 255 - temp;
                     prescaler[0] = 0x06;
                     break;
               } 
               
               
               if( period >= 100 && temp < 1000 ) 
               {          
                     temp = ( long)(period*sysclk/64);  
                     TCNT_val[0] = 255 - temp;
                     prescaler[0] = 0x04;
                     break;
               }    
               
               prescaler[0] = 0x0;
        }   
        
    }
    
    
    
    TCCR0 = prescaler[0];
    TIMSK |= 0x01; //timer0 ovf 인터럽트 인에이블
    TCNT0 = TCNT_val[0];
    SREG = 0x80; //전역인터럽트 인에이블
}


//PWM0 Setting (channel, 주기 , duty비)
void AcgPWM0_Setting(TIMERChannel ch, long period)
{
    long sysclk = SYSCLK;   
    long temp= 0;
	long dutycycle= 0;
    
    if(before_period[0] != period)  
    {
        before_period[0] = period;

		//period를 만들 수 있는 분주비를 찾는다.
        while(1)
        {                            
               
               if( period >= 4000 && temp <= 10000 ) 
               {             
                     temp = ( long)(period*sysclk/1024);  
                     TCNT_val[0] = 255 - temp;
                     prescaler[0] = 0x07;
                     break;
               }
               
                
               if(  period >= 1000 && temp < 4000 ) 
               {          
                     temp = ( long)((period*sysclk)/256); 
                     TCNT_val[0] = 255 - temp;
                     prescaler[0] = 0x06;
                     break;
               } 
               
               
               if( period >= 100 && temp < 1000 ) 
               {          
                     temp = ( long)(period*sysclk/64);  
                     TCNT_val[0] = 255 - temp;
                     prescaler[0] = 0x04;
                     break;
               }     
               
               
               prescaler[0] = 0x0;
        }   
        DDRB |=0x10;
		TCCR0 = 0b01101000 | prescaler[0];
		TIMSK |= 0x01; //timer0 ovf 인터럽트 인에이블
		TCNT0 = TCNT_val[0];
		SREG = 0x80; //전역인터럽트 인에이블
    }
        
    
    
    OCR0 = TCNT_val[0] + (255 - TCNT_val[0])*dutycycle/100;
       
}
void AcgPWM0(TIMERChannel ch, long dutycycle)
{
    OCR0 = TCNT_val[0] + (255 - TCNT_val[0])*dutycycle/100;	
}


void AcgTIMER1_Setting(long period)
{
    long sysclk = SYSCLK;
    long temp= 0;
    
    if(before_period[1] != period)  
    {
        before_period[1] = period;

		//period를 만들 수 있는 분주비를 찾는다.
        while(1)
        {                            
                 
               if(  period >= 1000000 && temp < 4000000 ) 
               {        
                     temp = (long)(period*sysclk/1024);
                     TCNT_val[1] = 65535 - temp;
                     prescaler[1] = 0x05;
                     break;
               }
               
               
               if( period >= 100000 && temp < 1000000 ) 
               {       
                     temp = (long)(period*sysclk/256);  
                     TCNT_val[1] = 65535 - temp;
                     prescaler[1] = 0x04;
                     break;
               } 
               
                
               if(period >= 10000 && temp < 100000 ) 
               {            
                     temp = (long)(period*sysclk/64); 
                     TCNT_val[1] = 65535 - temp;
                     prescaler[1] = 0x03;
                     break;
               } 
               
               if(period >= 100 && temp < 10000 ) 
               {            
                     temp = (long)(period*sysclk/8); 
                     TCNT_val[1] = 65535 - temp;
                     prescaler[1] = 0x02;
                     break;
               }     
                              
               prescaler[1] = 0x0;
        }   
        TCCR1A = 0x0;
		TCCR1B = prescaler[1];
		TCCR1C = 0x0; 
		TIMSK |= 0x04; //timer0 ovf 인터럽트 인에이블
		TCNT1H = (TCNT_val[1]>>8) & 0xff; 
		TCNT1L = TCNT_val[1] & 0x00ff;
		SREG = 0x80; //전역인터럽트 인에이블
    }
    
    
    
}

//PWM1 Setting (channel, 주기 , duty비)
void AcgPWM1_Setting(TIMERChannel ch, long period)
{
    long sysclk = SYSCLK;
    long temp= 0;
	long dutycycle= 0;
    
    if(before_period[1] != period)  
    {
        before_period[1] = period;

		//period를 만들 수 있는 분주비를 찾는다.
        while(1)
        {                            
              if(  period >= 1000000 && temp < 4000000 ) 
               {        
                     temp = (long)(period*sysclk/1024);
                     TCNT_val[1] = 65535 - temp;
                     prescaler[1] = 0x05;
                     break;
               }
               
               
               if( period >= 100000 && temp < 1000000 ) 
               {       
                     temp = (long)(period*sysclk/256);  
                     TCNT_val[1] = 65535 - temp;
                     prescaler[1] = 0x04;
                     break;
               } 
               
                
               if(period >= 10000 && temp < 100000 ) 
               {            
                     temp = (long)(period*sysclk/64); 
                     TCNT_val[1] = 65535 - temp;
                     prescaler[1] = 0x03;
                     break;
               } 
               
               if(period >= 100 && temp < 10000 ) 
               {            
                     temp = (long)(period*sysclk/8); 
                     TCNT_val[1] = 65535 - temp;
                     prescaler[1] = 0x02;
                     break;
               } 
               
               prescaler[1] = 0x0;
        }   
        ICR1H = 0xff;
		ICR1L = 0xff;
		TCCR1A |= 0x02;
		TCCR1B = 0x18 | prescaler[1];
		TCCR1C = 0x0; 
		TIMSK |= 0x04; //timer0 ovf 인터럽트 인에이블
		TCNT1H = (TCNT_val[1]>>8) & 0xff; 
		TCNT1L = TCNT_val[1] & 0x00ff;
		SREG = 0x80; //전역인터럽트 인에이블
    }
    
    if(ch & TIMER_01)
    {       
         DDRB |= 0x20;
         TCCR1A |=0x80;  
         temp =  TCNT_val[1] + (65535 - TCNT_val[1])*dutycycle/100;
         OCR1AH = (temp>>8) & 0xff;  
         OCR1AL = temp & 0x00ff; 
    }

    if(ch & TIMER_02)
    {       
         DDRB |= 0x40;
         TCCR1A |=0x20;  
         temp =  TCNT_val[1] + (65535 - TCNT_val[1])*dutycycle/100;
         OCR1BH = (temp>>8) & 0xff;  
         OCR1BL = temp & 0x00ff; 
    }

    if(ch & TIMER_03)
    {       
         DDRB |= 0x80;
         TCCR1A |=0x08;  
         temp =  TCNT_val[1] + (65535 - TCNT_val[1])*dutycycle/100;
         OCR1CH = (temp>>8) & 0xff;  
         OCR1CL = temp & 0x00ff; 
    }
           
    
}
void AcgPWM1(TIMERChannel ch, long dutycycle)
{
    long temp= 0;
	if(ch & TIMER_01)
    {        
         temp =  TCNT_val[1] + (65535 - TCNT_val[1])*dutycycle/100;
         OCR1AH = (temp>>8) & 0xff;  
         OCR1AL = temp & 0x00ff; 
    }

    if(ch & TIMER_02)
    {       
         temp =  TCNT_val[1] + (65535 - TCNT_val[1])*dutycycle/100;
         OCR1BH = (temp>>8) & 0xff;  
         OCR1BL = temp & 0x00ff; 
    }

    if(ch & TIMER_03)
    {       
         temp =  TCNT_val[1] + (65535 - TCNT_val[1])*dutycycle/100;
         OCR1CH = (temp>>8) & 0xff;  
         OCR1CL = temp & 0x00ff; 
    }
}



void AcgTIMER2_Setting(long period)
{
    long sysclk = SYSCLK;
    long temp= 0;
    
    if(before_period[2] != period)  
    {
        before_period[2] = period;

		//period를 만들 수 있는 분주비를 찾는다.
        while(1)
        {                            
               
               if( period >= 4000 && period <= 10000 ) 
               {                   
                     temp = (long)(period*sysclk/1024.0);  
                     TCNT_val[2] = 255 - temp;
                     prescaler[2] = 0x05;
                     break;
               }
               
                 
               if(  period >= 1000 && period <= 4000 ) 
               {                  
                     temp = (long)(period*sysclk/256.0);
                     TCNT_val[2] = 255 - temp;
                     prescaler[2] = 0x04;
                     break;
               } 
               
                 
               if(period >= 100 && period <= 1000 ) 
               {              
                     temp = (long)(period*sysclk/64.0);
                     TCNT_val[2] = 255 - temp;
                     prescaler[2] = 0x03;
                     break;
               }     
               
               prescaler[2] = 0x0;
        }   
        TCCR2 = prescaler[2];
		TIMSK |= 0x40; //timer0 ovf 인터럽트 인에이블
		TCNT2 = TCNT_val[2];
		SREG = 0x80; //전역인터럽트 인에이블
    }
    
    
    
    
}


//PWM2 Setting (channel, 주기 , duty비)
void AcgPWM2_Setting(TIMERChannel ch,long period)
{
    long sysclk = SYSCLK;
    long temp= 0;
	long dutycycle= 0;
    
    if(before_period[2] != period)  
    {
        before_period[2] = period;
                                                                                                                                                
		//period를 만들 수 있는 분주비를 찾는다.
        while(1)
        {                            
              if( period >= 4000 && period <= 10000 ) 
               {                   
                     temp = (long)(period*sysclk/1024.0);  
                     TCNT_val[2] = 255 - temp;
                     prescaler[2] = 0x05;
                     break;
               }
               
                 
               if(  period >= 1000 && period <= 4000 ) 
               {                  
                     temp = (long)(period*sysclk/256.0);
                     TCNT_val[2] = 255 - temp;
                     prescaler[2] = 0x04;
                     break;
               } 
               
                 
               if(period >= 100 && period <= 1000 ) 
               {              
                     temp = (long)(period*sysclk/64.0);
                     TCNT_val[2] = 255 - temp;
                     prescaler[2] = 0x03;
                     break;
               } 
               
               prescaler[2] = 0x0;
        }   
        DDRB |= 0x80;
		TCCR2 = 0b01101000 | prescaler[2];
		TIMSK |= 0x40; //timer0 ovf 인터럽트 인에이블
		TCNT2 = TCNT_val[2];
		SREG = 0x80; //전역인터럽트 인에이블  
    }
    
    
    
    OCR2 = TCNT_val[2] + (255 - TCNT_val[2])*dutycycle/100;
}

void AcgPWM2(TIMERChannel ch, long dutycycle)
{
	OCR2 = TCNT_val[2] + (255 - TCNT_val[2])*dutycycle/100;
}


void AcgTIMER3_Setting(long period)
{
    long sysclk = SYSCLK;
    long temp= 0;
    
    if(before_period[3] != period)  
    {
        before_period[3] = period;

		//period를 만들 수 있는 분주비를 찾는다.
        while(1)
        {                            
               
              if(  period >= 1000000 && temp < 4000000 ) 
               {        
                     temp = (long)(period*sysclk/1024);
                     TCNT_val[3] = 65535 - temp;
                     prescaler[3] = 0x05;
                     break;
               }
               
               
               if( period >= 100000 && temp < 1000000 ) 
               {       
                     temp = (long)(period*sysclk/256);  
                     TCNT_val[3] = 65535 - temp;
                     prescaler[3] = 0x04;
                     break;
               } 
               
                
               if(period >= 10000 && temp < 100000 ) 
               {            
                     temp = (long)(period*sysclk/64); 
                     TCNT_val[3] = 65535 - temp;
                     prescaler[3] = 0x03;
                     break;
               } 
               
               if(period >= 100 && temp < 10000 ) 
               {            
                     temp = (long)(period*sysclk/8); 
                     TCNT_val[3] = 65535 - temp;
                     prescaler[3] = 0x02;
                     break;
               }      
             
               prescaler[3] = 0x0;
        }   
        TCCR3A = 0x0;
		TCCR3B = prescaler[3];
		TCCR3C = 0x0; 
		ETIMSK |= 0x04; //timer0 ovf 인터럽트 인에이블
		TCNT3H = (TCNT_val[3]>>8) & 0xff; 
		TCNT3L = TCNT_val[3] & 0x00ff;
		SREG = 0x80; //전역인터럽트 인에이블
    }
    
    
    
}

//PWM3 Setting (channel, 주기 , duty비)
void AcgPWM3_Setting(TIMERChannel ch, long period)
{
    long sysclk = SYSCLK;
    long temp= 0;
	long dutycycle= 0;
    
    if(before_period[3] != period)  
    {
        before_period[3] = period;

		//period를 만들 수 있는 분주비를 찾는다.
        while(1)
        {                            
               if(  period >= 1000000 && temp < 4000000 ) 
               {        
                     temp = (long)(period*sysclk/1024);
                     TCNT_val[3] = 65535 - temp;
                     prescaler[3] = 0x05;
                     break;
               }
               
               
               if( period >= 100000 && temp < 1000000 ) 
               {       
                     temp = (long)(period*sysclk/256);  
                     TCNT_val[3] = 65535 - temp;
                     prescaler[3] = 0x04;
                     break;
               } 
               
                
               if(period >= 10000 && temp < 100000 ) 
               {            
                     temp = (long)(period*sysclk/64); 
                     TCNT_val[3] = 65535 - temp;
                     prescaler[3] = 0x03;
                     break;
               } 
               
               if(period >= 100 && temp < 10000 ) 
               {            
                     temp = (long)(period*sysclk/8); 
                     TCNT_val[3] = 65535 - temp;
                     prescaler[3] = 0x02;
                     break;
               }   
               
               prescaler[3] = 0x0;
        }   
        ICR3H = 0xff;
		ICR3L = 0xff;
		TCCR3A |= 0x02;
		TCCR3B = 0x18 | prescaler[3];
		TCCR3C = 0x0; 
		ETIMSK |= 0x04; //timer0 ovf 인터럽트 인에이블
		TCNT3H = (TCNT_val[3]>>8) & 0xff; 
		TCNT3L = TCNT_val[3] & 0x00ff;
		SREG = 0x80; //전역인터럽트 인에이블
    }
    
    if(ch & TIMER_01)
    {       
         DDRE |= 0x08;
         TCCR3A |=0x80;  
         temp =  TCNT_val[3] + (65535 - TCNT_val[3])*dutycycle/100;
         OCR3AH = (temp>>8) & 0xff;  
         OCR3AL = temp & 0x00ff; 
    }

    if(ch & TIMER_02)
    {       
         DDRE |= 0x10;
         TCCR3A |=0x20;  
         temp =  TCNT_val[3] + (65535 - TCNT_val[3])*dutycycle/100;
         OCR3BH = (temp>>8) & 0xff;  
         OCR3BL = temp & 0x00ff; 
    }
    
	if(ch & TIMER_03)
    {       
         DDRE |= 0x20;
         TCCR3A |=0x08;  
         temp =  TCNT_val[3] + (65535 - TCNT_val[3])*dutycycle/100;
         OCR3CH = (temp>>8) & 0xff;  
         OCR3CL = temp & 0x00ff; 
    }
    
    
}
void AcgPWM3(TIMERChannel ch, long dutycycle)
{
    long temp= 0;

	if(ch & TIMER_01)
    {       
         temp =  TCNT_val[3] + (65535 - TCNT_val[3])*dutycycle/100;
         OCR3AH = (temp>>8) & 0xff;  
         OCR3AL = temp & 0x00ff; 
    }

    if(ch & TIMER_02)
    {       
         temp =  TCNT_val[3] + (65535 - TCNT_val[3])*dutycycle/100;
         OCR3BH = (temp>>8) & 0xff;  
         OCR3BL = temp & 0x00ff; 
    }
    
	if(ch & TIMER_03)
    {       
         temp =  TCNT_val[3] + (65535 - TCNT_val[3])*dutycycle/100;
         OCR3CH = (temp>>8) & 0xff;  
         OCR3CL = temp & 0x00ff; 
    }
}

//Timer0 Over flow vector
SIGNAL (TIMER0_OVF_vect)
{
    TCNT0 = TCNT_val[0];
    TIMER_00_interrupt();
}


//Timer1 Over flow vector
SIGNAL (TIMER1_OVF_vect)
{
    TCNT1H = (TCNT_val[1]>>8) & 0xff; 
    TCNT1L = TCNT_val[1] & 0x00ff;
    TIMER_01_interrupt();
}

//Timer2 Over flow vector
SIGNAL (TIMER2_OVF_vect)
{
    TCNT2 = TCNT_val[2];
    TIMER_02_interrupt();
}



//Timer3 Over flow vector
SIGNAL (TIMER3_OVF_vect)
{
    TCNT3H = (TCNT_val[3]>>8) & 0xff; 
    TCNT3L = TCNT_val[3] & 0x00ff;
    TIMER_03_interrupt();
}
