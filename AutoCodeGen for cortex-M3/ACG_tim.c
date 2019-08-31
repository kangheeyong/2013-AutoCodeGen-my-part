#include "stm32f10x.h"
#include "ACG_tim.h"

extern int SYSCLCK;


double before_period[8] = {0,0,0,0,0,0,0,0};
uint8_t PWM_ch1_using[8] = {0,0,0,0,0,0,0,0};
uint8_t PWM_ch2_using[8] = {0,0,0,0,0,0,0,0};
uint8_t PWM_ch3_using[8] = {0,0,0,0,0,0,0,0};
uint8_t PWM_ch4_using[8] = {0,0,0,0,0,0,0,0};

void AcgPWM1_Setting(TimerChannel ch, int period)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;   
    TIM_OCInitTypeDef  TIM_OCInitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;
    
    int prescaler = 0;
    int pulse = 0;
    int dutycycle = 0;
    
    if(before_period[0] != period)
    {
	before_period[0] = period;
                  
        //타이머 주기 계산 함수
        if(period >= 100 && period <= 40000)
        {
            pulse = 100; 
            prescaler = (int)(period*SYSCLCK/100);
        }
        else if(period >= 40000 && period <= 40000000)
        {
            pulse = 10000; 
            prescaler = (int)(period*SYSCLCK/10000);
        }            
        
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
        RCC_APB2PeriphClockCmd( RCC_APB2Periph_AFIO | RCC_APB2Periph_GPIOE, ENABLE); 
        
        GPIO_PinRemapConfig ( GPIO_FullRemap_TIM1, ENABLE );
           
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
            
        //타이머 설정
        TIM_TimeBaseStructure.TIM_Period = pulse;
        TIM_TimeBaseStructure.TIM_Prescaler = prescaler;
        TIM_TimeBaseStructure.TIM_ClockDivision = 0;
        TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
        TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;   
            
        TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);
            
        TIM_Cmd(TIM1, ENABLE); 
            
        TIM_CtrlPWMOutputs(TIM1, ENABLE);
        
    }
    
    if(ch & TIM_01)//pwm ch1
    {
         if(PWM_ch1_using[0] == DISUSE)
         {
            PWM_ch1_using[0] = USE;
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
            GPIO_Init(GPIOE, &GPIO_InitStructure);
      
            //pwm 출력핀 설정
            TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
            TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
            TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;
            TIM_OCInitStructure.TIM_Pulse = dutycycle;
            TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
            TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;
            TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
            TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCIdleState_Reset;
            
            TIM_OC1Init(TIM1, &TIM_OCInitStructure);        
            TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);
         }
        if(period >= 100 && period <= 40000)
        {
            TIM1->CCR1 = dutycycle;
        }         
        else if(period >= 40000 && period <= 40000000)
        {
            TIM1->CCR1 = dutycycle*100;
        }
    }
    if(ch & TIM_02)//pwm ch2
    {
         if(PWM_ch2_using[0] == DISUSE)
         {
            PWM_ch2_using[0] =USE;
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
            GPIO_Init(GPIOE, &GPIO_InitStructure);
              
            //pwm 출력핀 설정
            TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
            TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
            TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;
            TIM_OCInitStructure.TIM_Pulse = dutycycle;
            TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
            TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;
            TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
            TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCIdleState_Reset;
        
            TIM_OC2Init(TIM1, &TIM_OCInitStructure); 
        
            TIM_OC2PreloadConfig(TIM1, TIM_OCPreload_Enable);
         }
        if(period >= 100 && period <= 40000)
        {
            TIM1->CCR2 = dutycycle;
        }         
        else if(period >= 40000 && period <= 40000000)
        {
            TIM1->CCR2 = dutycycle*100;
        }
    }
    if(ch & TIM_03)//pwm ch3
    {
         if(PWM_ch3_using[0] == DISUSE)
         {
            PWM_ch3_using[0] =USE;
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
            GPIO_Init(GPIOE, &GPIO_InitStructure);
              
            //pwm 출력핀 설정
            TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
            TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
            TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;
            TIM_OCInitStructure.TIM_Pulse = dutycycle;
            TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
            TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;
            TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
            TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCIdleState_Reset;
        
            TIM_OC3Init(TIM1, &TIM_OCInitStructure);         
            TIM_OC3PreloadConfig(TIM1, TIM_OCPreload_Enable);
         }
        if(period >= 100 && period <= 40000)
        {
            TIM1->CCR3 = dutycycle;
        }         
        else if(period >= 40000 && period <= 40000000)
        {
            TIM1->CCR3 = dutycycle*100;
        }
    }
    if(ch & TIM_04)//pwm ch4
    {
         if(PWM_ch4_using[0] == DISUSE)
         {
            PWM_ch4_using[0] =USE;
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;
            GPIO_Init(GPIOE, &GPIO_InitStructure);
              
            //pwm 출력핀 설정
            TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
            TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
            TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;
            TIM_OCInitStructure.TIM_Pulse = dutycycle;
            TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
            TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;
            TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
            TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCIdleState_Reset;
        
            TIM_OC4Init(TIM1, &TIM_OCInitStructure); 
        
            TIM_OC4PreloadConfig(TIM1, TIM_OCPreload_Enable);
         }
        if(period >= 100 && period <= 40000)
        {
            TIM1->CCR4 = dutycycle;
        }         
        else if(period >= 40000 && period <= 40000000)
        {
            TIM1->CCR4 = dutycycle*100;
        }
    }
}
void AcgPWM1(TimerChannel ch, long dutycycle)
{
    if(ch & TIM_01)//pwm ch1
    {

        if(before_period[0] >= 100 && before_period[0] <= 40000)
        {
            TIM1->CCR1 = dutycycle;
        }         
        else if(before_period[0] >= 40000 && before_period[0] <= 40000000)
        {
            TIM1->CCR1 = dutycycle*100;
        }
    }
    if(ch & TIM_02)//pwm ch2
    {
 
        if(before_period[0] >= 100 && before_period[0] <= 40000)
        {
            TIM1->CCR2 = dutycycle;
        }         
        else if(before_period[0] >= 40000 && before_period[0] <= 40000000)
        {
            TIM1->CCR2 = dutycycle*100;
        }
    }
    if(ch & TIM_03)//pwm ch3
    {

        if(before_period[0] >= 100 && before_period[0] <= 40000)
        {
            TIM1->CCR3 = dutycycle;
        }         
        else if(before_period[0] >= 40000 && before_period[0] <= 40000000)
        {
            TIM1->CCR3 = dutycycle*100;
        }
    }
    if(ch & TIM_04)//pwm ch4
    {
        
        if(before_period[0] >= 100 && before_period[0] <= 40000)
        {
            TIM1->CCR4 = dutycycle;
        }         
        else if(before_period[0] >= 40000 && before_period[0] <= 40000000)
        {
            TIM1->CCR4 = dutycycle*100;
        }
    }  
}

void AcgTIMER2_Setting(int period) 
{
    NVIC_InitTypeDef NVIC_InitStructure;
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;           
    int prescaler = 0;
    int pulse = 0;
    
    if(before_period[1] != period)
    {
	before_period[1] = period;
               
        //타이머 주기 계산 함수
        if(period >= 100 && period <= 40000)
        {
            pulse = 100; 
            prescaler = (int)(period*SYSCLCK/100);
        }
        else if(period >= 40000 && period <= 40000000)
        {
            pulse = 10000; 
            prescaler = (int)(period*SYSCLCK/10000);
        }
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
            
        //인터럽트 핸들러와 우선순위 설정
        NVIC_InitStructure.NVIC_IRQChannel =  TIM2_IRQn;
        NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 28;
        NVIC_InitStructure.NVIC_IRQChannelSubPriority = 35;
        NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
        NVIC_Init(&NVIC_InitStructure);
           
        //타이머 설정
        TIM_TimeBaseStructure.TIM_Period = pulse;
        TIM_TimeBaseStructure.TIM_Prescaler = prescaler;  
        TIM_TimeBaseStructure.TIM_ClockDivision = 0;
        TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
        
        TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);            
        TIM_Cmd(TIM2, ENABLE);        
        TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
        
    }
}
void AcgPWM2_Setting(TimerChannel ch, int period)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;   
    TIM_OCInitTypeDef  TIM_OCInitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;
    
    int prescaler = 0;
    int pulse = 0;
    int dutycycle = 0;
    
    if(before_period[1] != period)
    {
	before_period[1] = period;
                  
        //타이머 주기 계산 함수
        if(period >= 100 && period <= 40000)
        {
            pulse = 100; 
            prescaler = (int)(period*SYSCLCK/100);
        }
        else if(period >= 40000 && period <= 40000000)
        {
            pulse = 10000; 
            prescaler = (int)(period*SYSCLCK/10000);
        }

        RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); 
              
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
            
        //pwm 출력핀 설정
        TIM_TimeBaseStructure.TIM_Period = pulse;
        TIM_TimeBaseStructure.TIM_Prescaler = prescaler;
        TIM_TimeBaseStructure.TIM_ClockDivision = 0;
        TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
        
        TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);           
        TIM_Cmd(TIM2, ENABLE); 
        
    }
    
    if(ch & TIM_01) //pwm ch1
    {
         if(PWM_ch1_using[1] == DISUSE)
         {
            PWM_ch1_using[1] =USE;
            
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
            GPIO_Init(GPIOA, &GPIO_InitStructure);
      
            //pwm 출력핀 설정
            TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
            TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
            TIM_OCInitStructure.TIM_Pulse =  prescaler;
            TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
        
            TIM_OC1Init(TIM2, &TIM_OCInitStructure); 
        
            TIM_OC1PreloadConfig(TIM2, TIM_OCPreload_Enable);
         }
        if(period >= 100 && period <= 40000)
        {
            TIM2->CCR1 = dutycycle;
        }         
        else if(period >= 40000 && period <= 40000000)
        {
            TIM2->CCR1 = dutycycle*100;
        }
    }
    if(ch & TIM_02) //pwm ch2
    {
         if(PWM_ch2_using[1] == DISUSE)
         {
            PWM_ch2_using[1] = USE;
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
            GPIO_Init(GPIOA, &GPIO_InitStructure);
        
            //pwm 출력핀 설정
            TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
            TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
            TIM_OCInitStructure.TIM_Pulse =  prescaler;
            TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
  
            TIM_OC2Init(TIM2, &TIM_OCInitStructure); 
      
            TIM_OC2PreloadConfig(TIM2, TIM_OCPreload_Enable);
         }
        if(period >= 100 && period <= 40000)
        {
            TIM2->CCR2 = dutycycle;
        }         
        else if(period >= 40000 && period <= 40000000)
        {
            TIM2->CCR2 = dutycycle*100;
        }
    }
    if(ch & TIM_03) //pwm ch3
    {
         if(PWM_ch3_using[1] == DISUSE)
         {
            PWM_ch3_using[1] =USE;
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
            GPIO_Init(GPIOA, &GPIO_InitStructure);
              
            //pwm 출력핀 설정
            TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
            TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
            TIM_OCInitStructure.TIM_Pulse =  prescaler;
            TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
        
            TIM_OC3Init(TIM2, &TIM_OCInitStructure); 
        
            TIM_OC3PreloadConfig(TIM2, TIM_OCPreload_Enable);
         }
        if(period >= 100 && period <= 40000)
        {
            TIM2->CCR3 = dutycycle;
        }         
        else if(period >= 40000 && period <= 40000000)
        {
            TIM2->CCR3 = dutycycle*100;
        }
    }
    if(ch & TIM_04) //pwm ch4
    {
         if(PWM_ch4_using[1] == DISUSE)
         {
            PWM_ch4_using[1] = USE;
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
            GPIO_Init(GPIOA, &GPIO_InitStructure);
              
            //pwm 출력핀 설정
            TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
            TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
            TIM_OCInitStructure.TIM_Pulse =  prescaler;
            TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
        
            TIM_OC4Init(TIM2, &TIM_OCInitStructure); 
        
            TIM_OC4PreloadConfig(TIM2, TIM_OCPreload_Enable);
         }
        if(period >= 100 && period <= 40000)
        {
            TIM2->CCR4 = dutycycle;
        }         
        else if(period >= 40000 && period <= 40000000)
        {
            TIM2->CCR4 = dutycycle*100;
        }
    }
}
void AcgPWM2(TimerChannel ch, long dutycycle)
{
    if(ch & TIM_01)//pwm ch1
    {

        if(before_period[1] >= 100 && before_period[1] <= 40000)
        {
            TIM2->CCR1 = dutycycle;
        }         
        else if(before_period[1] >= 40000 && before_period[1] <= 40000000)
        {
            TIM2->CCR1 = dutycycle*100;
        }
    }
    if(ch & TIM_02)//pwm ch2
    {
 
        if(before_period[1] >= 100 && before_period[1] <= 40000)
        {
            TIM2->CCR2 = dutycycle;
        }         
        else if(before_period[1] >= 40000 && before_period[1] <= 40000000)
        {
            TIM2->CCR2 = dutycycle*100;
        }
    }
    if(ch & TIM_03)//pwm ch3
    {

        if(before_period[1] >= 100 && before_period[1] <= 40000)
        {
            TIM2->CCR3 = dutycycle;
        }         
        else if(before_period[1] >= 40000 && before_period[1] <= 40000000)
        {
            TIM2->CCR3 = dutycycle*100;
        }
    }
    if(ch & TIM_04)//pwm ch4
    {
        
        if(before_period[1] >= 100 && before_period[1] <= 40000)
        {
            TIM2->CCR4 = dutycycle;
        }         
        else if(before_period[1] >= 40000 && before_period[1] <= 40000000)
        {
            TIM2->CCR4 = dutycycle*100;
        }
    }  
}
void AcgTIMER3_Setting(int period)
{
    NVIC_InitTypeDef NVIC_InitStructure;
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;           
    int prescaler = 0;
    int pulse = 0;
    
    if(before_period[2] != period)
    {
	before_period[2] = period;
               
        //타이머 주기 계산 함수
        if(period >= 100 && period <= 40000)
        {
            pulse = 100; 
            prescaler = (int)(period*SYSCLCK/100);
        }
        else if(period >= 40000 && period <= 40000000)
        {
            pulse = 10000; 
            prescaler = (int)(period*SYSCLCK/10000);
        }
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
            
        //인터럽트 핸들러와 우선순위 설정
        NVIC_InitStructure.NVIC_IRQChannel =  TIM3_IRQn;
        NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 29;
        NVIC_InitStructure.NVIC_IRQChannelSubPriority = 36;
        NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
        NVIC_Init(&NVIC_InitStructure);
           
        //타이머 설정
        TIM_TimeBaseStructure.TIM_Period = pulse;
        TIM_TimeBaseStructure.TIM_Prescaler = prescaler;  
        TIM_TimeBaseStructure.TIM_ClockDivision = 0;
        TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
        
        TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);            
        TIM_Cmd(TIM3, ENABLE);        
        TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);
        
    }
}
void AcgPWM3_Setting(TimerChannel ch, int period)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;   
    TIM_OCInitTypeDef  TIM_OCInitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;
    
    int prescaler = 0;
    int pulse = 0;
    int dutycycle = 0;
    
    if(before_period[2] != period)
    {
	before_period[2] = period;
                  
        //타이머 주기 계산 함수
        if(period >= 100 && period <= 40000)
        {
            pulse = 100; 
            prescaler = (int)(period*SYSCLCK/100);
        }
        else if(period >= 40000 && period <= 40000000)
        {
            pulse = 10000; 
            prescaler = (int)(period*SYSCLCK/10000);
        }

        RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
        RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB, ENABLE); 
         
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
            
        //타이머 설정
        TIM_TimeBaseStructure.TIM_Period = pulse;
        TIM_TimeBaseStructure.TIM_Prescaler = prescaler;
        TIM_TimeBaseStructure.TIM_ClockDivision = 0;
        TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
        
        TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);           
        TIM_Cmd(TIM3, ENABLE); 
        
    }
    
    if(ch & TIM_01)  //pwm ch1
    {
         if(PWM_ch1_using[2] == DISUSE)
         {
            PWM_ch1_using[2] = USE;

            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
            GPIO_Init(GPIOA, &GPIO_InitStructure);
      
            //pwm 출력핀 설정
            TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
            TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
            TIM_OCInitStructure.TIM_Pulse =  dutycycle;
            TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
        
            TIM_OC1Init(TIM3, &TIM_OCInitStructure); 
        
            TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);
         }
        if(period >= 100 && period <= 40000)
        {
            TIM3->CCR1 = dutycycle;
        }         
        else if(period >= 40000 && period <= 40000000)
        {
            TIM3->CCR1 = dutycycle*100;
        }
    }
    if(ch & TIM_02)  //pwm ch2
    {
         if(PWM_ch2_using[2] == DISUSE)
         {
            PWM_ch2_using[2] = USE;
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
            GPIO_Init(GPIOA, &GPIO_InitStructure);
        
            //pwm 출력핀 설정
            TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
            TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
            TIM_OCInitStructure.TIM_Pulse =  dutycycle;
            TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
  
            TIM_OC2Init(TIM3, &TIM_OCInitStructure);       
            TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);
         }
        if(period >= 100 && period <= 40000)
        {
            TIM3->CCR2 = dutycycle;
        }         
        else if(period >= 40000 && period <= 40000000)
        {
            TIM3->CCR2 = dutycycle*100;
        }
    }
    if(ch & TIM_03)  //pwm ch3
    {
         if(PWM_ch3_using[2] == DISUSE)
         {
            PWM_ch3_using[2] = USE;
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
            GPIO_Init(GPIOB, &GPIO_InitStructure);
              
            //pwm 출력핀 설정
            TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
            TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
            TIM_OCInitStructure.TIM_Pulse =  dutycycle;
            TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
        
            TIM_OC3Init(TIM3, &TIM_OCInitStructure); 
        
            TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);
         }
        if(period >= 100 && period <= 40000)
        {
            TIM3->CCR3 = dutycycle;
        }         
        else if(period >= 40000 && period <= 40000000)
        {
            TIM3->CCR3 = dutycycle*100;
        }
    }
    if(ch & TIM_04)  //pwm ch4
    {
         if(PWM_ch4_using[2] == DISUSE)
         {
            PWM_ch4_using[2] = USE;
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
            GPIO_Init(GPIOB, &GPIO_InitStructure);
              
            //pwm 출력핀 설정
            TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
            TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
            TIM_OCInitStructure.TIM_Pulse =  dutycycle;
            TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
        
            TIM_OC4Init(TIM3, &TIM_OCInitStructure); 
        
            TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Enable);
         }
        if(period >= 100 && period <= 40000)
        {
            TIM3->CCR4 = dutycycle;
        }         
        else if(period >= 40000 && period <= 40000000)
        {
            TIM3->CCR4 = dutycycle*100;
        }
    }
}
void AcgPWM3(TimerChannel ch, long dutycycle)
{
    if(ch & TIM_01)//pwm ch1
    {

        if(before_period[2] >= 100 && before_period[2] <= 40000)
        {
            TIM3->CCR1 = dutycycle;
        }         
        else if(before_period[2] >= 40000 && before_period[2] <= 40000000)
        {
            TIM3->CCR1 = dutycycle*100;
        }
    }
    if(ch & TIM_02)//pwm ch2
    {
 
        if(before_period[2] >= 100 && before_period[2] <= 40000)
        {
            TIM3->CCR2 = dutycycle;
        }         
        else if(before_period[2] >= 40000 && before_period[2] <= 40000000)
        {
            TIM3->CCR2 = dutycycle*100;
        }
    }
    if(ch & TIM_03)//pwm ch3
    {

        if(before_period[2] >= 100 && before_period[2] <= 40000)
        {
            TIM3->CCR3 = dutycycle;
        }         
        else if(before_period[2] >= 40000 && before_period[2] <= 40000000)
        {
            TIM3->CCR3 = dutycycle*100;
        }
    }
    if(ch & TIM_04)//pwm ch4
    {
        
        if(before_period[2] >= 100 && before_period[2] <= 40000)
        {
            TIM3->CCR4 = dutycycle;
        }         
        else if(before_period[2] >= 40000 && before_period[2] <= 40000000)
        {
            TIM3->CCR4 = dutycycle*100;
        }
    }  
}
void AcgTIMER4_Setting(int period) //real tim4
{
    NVIC_InitTypeDef NVIC_InitStructure;
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;           
    int prescaler = 0;
    int pulse = 0;
    
    if(before_period[3] != period)
    {
	before_period[3] = period;
               
        //타이머 주기 계산 함수
        if(period >= 100 && period <= 40000)
        {
            pulse = 100; 
            prescaler = (int)(period*SYSCLCK/100);
        }
        else if(period >= 40000 && period <= 40000000)
        {
            pulse = 10000; 
            prescaler = (int)(period*SYSCLCK/10000);
        }
        
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
            
         //인터럽트 핸들러와 우선순위 설정
        NVIC_InitStructure.NVIC_IRQChannel =  TIM4_IRQn;
        NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 30;
        NVIC_InitStructure.NVIC_IRQChannelSubPriority = 37;
        NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
        NVIC_Init(&NVIC_InitStructure);
           
        //타이머 설정
        TIM_TimeBaseStructure.TIM_Period = pulse;
        TIM_TimeBaseStructure.TIM_Prescaler = prescaler;  
        TIM_TimeBaseStructure.TIM_ClockDivision = 0;
        TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
        
        TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);            
        TIM_Cmd(TIM4, ENABLE);        
        TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);
        
    }
}
void AcgPWM4_Setting(TimerChannel ch, int period)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;   
    TIM_OCInitTypeDef  TIM_OCInitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;
    
    int prescaler = 0;
    int pulse = 0;
    int dutycycle = 0;
    
    if(before_period[3] != period)
    {
	before_period[3] = period;
                  
               //타이머 주기 계산 함수
        if(period >= 100 && period <= 40000)
        {
            pulse = 100; 
            prescaler = (int)(period*SYSCLCK/100);
        }
        else if(period >= 40000 && period <= 40000000)
        {
            pulse = 10000; 
            prescaler = (int)(period*SYSCLCK/10000);
        }

        RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
           
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
            
        //타이머 설정
        TIM_TimeBaseStructure.TIM_Period = pulse;
        TIM_TimeBaseStructure.TIM_Prescaler = prescaler;
        TIM_TimeBaseStructure.TIM_ClockDivision = 0;
        TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
        
        TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);            
        TIM_Cmd(TIM4, ENABLE);   
        
    }
    
    if(ch & TIM_01)  //pwm ch1
    {
         if(PWM_ch1_using[3] == DISUSE)
         {
            PWM_ch1_using[3] = USE;
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
            GPIO_Init(GPIOB, &GPIO_InitStructure);
      
            //pwm 출력핀 설정
            TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
            TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
            TIM_OCInitStructure.TIM_Pulse =  dutycycle;
            TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
        
            TIM_OC1Init(TIM4, &TIM_OCInitStructure); 
        
            TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);
         }
        if(period >= 100 && period <= 40000)
        {
            TIM4->CCR1 = dutycycle;
        }         
        else if(period >= 40000 && period <= 40000000)
        {
            TIM4->CCR1 = dutycycle*100;
        }
    }
    if(ch & TIM_02) //pwm ch2
    {
         if(PWM_ch2_using[3] == DISUSE)
         {
            PWM_ch2_using[3] = USE;
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
            GPIO_Init(GPIOB, &GPIO_InitStructure);
              
            //pwm 출력핀 설정
            TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
            TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
            TIM_OCInitStructure.TIM_Pulse =  dutycycle;
            TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
        
            TIM_OC2Init(TIM4, &TIM_OCInitStructure); 
        
            TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Enable);
         }
        if(period >= 100 && period <= 40000)
        {
            TIM4->CCR2 = dutycycle;
        }         
        else if(period >= 40000 && period <= 40000000)
        {
            TIM4->CCR2 = dutycycle*100;
        }
    }
    if(ch & TIM_03)  //pwm ch3
    {
         if(PWM_ch3_using[3] == DISUSE)
         {
            PWM_ch3_using[3] = USE;
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
            GPIO_Init(GPIOB, &GPIO_InitStructure);
              
            //pwm 출력핀 설정
            TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
            TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
            TIM_OCInitStructure.TIM_Pulse =  dutycycle;
            TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
        
            TIM_OC3Init(TIM4, &TIM_OCInitStructure); 
        
            TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable);
         }
        if(period >= 100 && period <= 40000)
        {
            TIM4->CCR3 = dutycycle;
        }         
        else if(period >= 40000 && period <= 40000000)
        {
            TIM4->CCR3 = dutycycle*100;
        }
    }
    if(ch & TIM_04)  //pwm ch4
    {
         if(PWM_ch4_using[3] == DISUSE)
         {
            PWM_ch4_using[3] = USE;
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
            GPIO_Init(GPIOB, &GPIO_InitStructure);
              
            //pwm 출력핀 설정
            TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
            TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
            TIM_OCInitStructure.TIM_Pulse =  dutycycle;
            TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
        
            TIM_OC4Init(TIM4, &TIM_OCInitStructure); 
        
            TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Enable);
         }
        if(period >= 100 && period <= 40000)
        {
            TIM4->CCR4 = dutycycle;
        }         
        else if(period >= 40000 && period <= 40000000)
        {
            TIM4->CCR4 = dutycycle*100;
        }
    }
}
void AcgPWM4(TimerChannel ch, long dutycycle)
{
    if(ch & TIM_01)//pwm ch1
    {

        if(before_period[3] >= 100 && before_period[3] <= 40000)
        {
            TIM4->CCR1 = dutycycle;
        }         
        else if(before_period[3] >= 40000 && before_period[3] <= 40000000)
        {
            TIM4->CCR1 = dutycycle*100;
        }
    }
    if(ch & TIM_02)//pwm ch2
    {
 
        if(before_period[3] >= 100 && before_period[3] <= 40000)
        {
            TIM4->CCR2 = dutycycle;
        }         
        else if(before_period[3] >= 40000 && before_period[3] <= 40000000)
        {
            TIM4->CCR2 = dutycycle*100;
        }
    }
    if(ch & TIM_03)//pwm ch3
    {

        if(before_period[3] >= 100 && before_period[3] <= 40000)
        {
            TIM4->CCR3 = dutycycle;
        }         
        else if(before_period[3] >= 40000 && before_period[3] <= 40000000)
        {
            TIM4->CCR3 = dutycycle*100;
        }
    }
    if(ch & TIM_04)//pwm ch4
    {
        
        if(before_period[3] >= 100 && before_period[3] <= 40000)
        {
            TIM4->CCR4 = dutycycle;
        }         
        else if(before_period[3] >= 40000 && before_period[3] <= 40000000)
        {
            TIM4->CCR4 = dutycycle*100;
        }
    }  
}
void AcgTIMER5_Setting(int period) //real tim5
{
    NVIC_InitTypeDef NVIC_InitStructure;
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    int prescaler = 0;
    int pulse = 0;
       
    if(before_period[4] != period)
    {
	before_period[4] = period; 
        
        //타이머 주기 계산 함수
        if(period >= 100 && period <= 40000)
        {
            pulse = 100; 
            prescaler = (int)(period*SYSCLCK/100);
        }
        else if(period >= 40000 && period <= 40000000)
        {
            pulse = 10000; 
            prescaler = (int)(period*SYSCLCK/10000);
        }
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);
        
        //인터럽트 핸들러와 우선순위 설정
        NVIC_InitStructure.NVIC_IRQChannel =  TIM5_IRQn;
        NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 50;
        NVIC_InitStructure.NVIC_IRQChannelSubPriority = 57;
        NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
        NVIC_Init(&NVIC_InitStructure);
       
        //타이머 설정
        TIM_TimeBaseStructure.TIM_Period = pulse;
        TIM_TimeBaseStructure.TIM_Prescaler = prescaler; 
        TIM_TimeBaseStructure.TIM_ClockDivision = 0;
        TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    
        TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure);      
        TIM_Cmd(TIM5, ENABLE);    
        TIM_ITConfig(TIM5, TIM_IT_Update, ENABLE);
        
    }
}
void AcgPWM5_Setting(TimerChannel ch, int period)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;   
    TIM_OCInitTypeDef  TIM_OCInitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;
    
    int prescaler = 0;
    int pulse = 0;
    int dutycycle = 0;
    
    if(before_period[4] != period)
    {
	before_period[4] = period;
                  

        //타이머 주기 계산 함수
        if(period >= 100 && period <= 40000)
        {
            pulse = 100; 
            prescaler = (int)(period*SYSCLCK/100);
        }
        else if(period >= 40000 && period <= 40000000)
        {
            pulse = 10000; 
            prescaler = (int)(period*SYSCLCK/10000);
        }

        RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); 
              
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
            
        //타이머 설정
        TIM_TimeBaseStructure.TIM_Period = pulse;
        TIM_TimeBaseStructure.TIM_Prescaler = prescaler;
        TIM_TimeBaseStructure.TIM_ClockDivision = 0;
        TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
        
        TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure);  
        TIM_Cmd(TIM5, ENABLE); 
        
    }
    
    if(ch &= TIM_01) //pwm ch1
    {
         if(PWM_ch1_using[4] == DISUSE)
         {
            PWM_ch1_using[4] = USE;
            
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
            GPIO_Init(GPIOA, &GPIO_InitStructure);
      
            //pwm 출력핀 설정
            TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
            TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
            TIM_OCInitStructure.TIM_Pulse =  prescaler;
            TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
        
            TIM_OC1Init(TIM5, &TIM_OCInitStructure); 
        
            TIM_OC1PreloadConfig(TIM5, TIM_OCPreload_Enable);
         }
        if(period >= 100 && period <= 40000)
        {
            TIM5->CCR1 = dutycycle;
        }         
        else if(period >= 40000 && period <= 40000000)
        {
            TIM5->CCR1 = dutycycle*100;
        }
    }
    if(ch & TIM_02) //pwm ch2
    {
         if(PWM_ch2_using[4] == DISUSE)
         {
            PWM_ch2_using[4] = USE;
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
            GPIO_Init(GPIOA, &GPIO_InitStructure);
        
            //pwm 출력핀 설정
            TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
            TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
            TIM_OCInitStructure.TIM_Pulse =  prescaler;
            TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
  
            TIM_OC2Init(TIM5, &TIM_OCInitStructure); 
      
            TIM_OC2PreloadConfig(TIM5, TIM_OCPreload_Enable);
         }
        if(period >= 100 && period <= 40000)
        {
            TIM5->CCR2 = dutycycle;
        }         
        else if(period >= 40000 && period <= 40000000)
        {
            TIM5->CCR2 = dutycycle*100;
        }
    }
    if(ch & TIM_03) //pwm ch3
    {
         if(PWM_ch3_using[4] == DISUSE)
         {
            PWM_ch3_using[4] = USE;
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
            GPIO_Init(GPIOA, &GPIO_InitStructure);
              
            //pwm 출력핀 설정
            TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
            TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
            TIM_OCInitStructure.TIM_Pulse =  prescaler;
            TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
        
            TIM_OC3Init(TIM5, &TIM_OCInitStructure); 
        
            TIM_OC3PreloadConfig(TIM5, TIM_OCPreload_Enable);
         }
        if(period >= 100 && period <= 40000)
        {
            TIM5->CCR3 = dutycycle;
        }         
        else if(period >= 40000 && period <= 40000000)
        {
            TIM5->CCR3 = dutycycle*100;
        }
    }
    if(ch & TIM_04) //pwm ch4
    {
         if(PWM_ch4_using[4] == DISUSE)
         {
            PWM_ch4_using[4] = USE;
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
            GPIO_Init(GPIOA, &GPIO_InitStructure);
              
            //pwm 출력핀 설정
            TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
            TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
            TIM_OCInitStructure.TIM_Pulse =  prescaler;
            TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
        
            TIM_OC4Init(TIM5, &TIM_OCInitStructure); 
        
            TIM_OC4PreloadConfig(TIM5, TIM_OCPreload_Enable);
         }
        if(period >= 100 && period <= 40000)
        {
            TIM5->CCR4 = dutycycle;
        }         
        else if(period >= 40000 && period <= 40000000)
        {
            TIM5->CCR4 = dutycycle*100;
        }
    }
}
void AcgPWM5(TimerChannel ch, long dutycycle)
{
    if(ch & TIM_01)//pwm ch1
    {

        if(before_period[4] >= 100 && before_period[4] <= 40000)
        {
            TIM5->CCR1 = dutycycle;
        }         
        else if(before_period[4] >= 40000 && before_period[4] <= 40000000)
        {
            TIM5->CCR1 = dutycycle*100;
        }
    }
    if(ch & TIM_02)//pwm ch2
    {
 
        if(before_period[4] >= 100 && before_period[4] <= 40000)
        {
            TIM5->CCR2 = dutycycle;
        }         
        else if(before_period[4] >= 40000 && before_period[4] <= 40000000)
        {
            TIM5->CCR2 = dutycycle*100;
        }
    }
    if(ch & TIM_03)//pwm ch3
    {

        if(before_period[4] >= 100 && before_period[4] <= 40000)
        {
            TIM5->CCR3 = dutycycle;
        }         
        else if(before_period[4] >= 40000 && before_period[4] <= 40000000)
        {
            TIM5->CCR3 = dutycycle*100;
        }
    }
    if(ch & TIM_04)//pwm ch4
    {
        
        if(before_period[4] >= 100 && before_period[4] <= 40000)
        {
            TIM5->CCR4 = dutycycle;
        }         
        else if(before_period[4] >= 40000 && before_period[4] <= 40000000)
        {
            TIM5->CCR4 = dutycycle*100;
        }
    }  
}

void AcgTIMER6_Setting(int period) //real tim6
{
    NVIC_InitTypeDef NVIC_InitStructure;
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    int prescaler = 0;
    int pulse = 0;
    
    if(before_period[5] != period)
    {
	before_period[5] = period;
               
        //타이머 주기 계산 함수
        if(period >= 100 && period <= 40000)
        {
            pulse = 100; 
            prescaler = (int)(period*SYSCLCK/100);
        }
        else if(period >= 40000 && period <= 40000000)
        {
            pulse = 10000; 
            prescaler = (int)(period*SYSCLCK/10000);
        }
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE);
            
        //인터럽트 핸들러와 우선순위 설정
        NVIC_InitStructure.NVIC_IRQChannel =  TIM6_IRQn;
        NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 54;
        NVIC_InitStructure.NVIC_IRQChannelSubPriority = 61;
        NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
        NVIC_Init(&NVIC_InitStructure);
           
        //타이머 설정
        TIM_TimeBaseStructure.TIM_Period = pulse;
        TIM_TimeBaseStructure.TIM_Prescaler = prescaler; 
        TIM_TimeBaseStructure.TIM_ClockDivision = 0;
        TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
        
        TIM_TimeBaseInit(TIM6, &TIM_TimeBaseStructure);
        TIM_Cmd(TIM6, ENABLE);
        TIM_ITConfig(TIM6, TIM_IT_Update, ENABLE);
        
    }
}

void AcgTIMER7_Setting(int period) //real tim7
{
    NVIC_InitTypeDef NVIC_InitStructure;
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;           
    int prescaler = 0;
    int pulse = 0;
    
    if(before_period[6] != period)
    {
	before_period[6] = period;
               
        //타이머 주기 계산 함수
        if(period >= 100 && period <= 40000)
        {
            pulse = 100; 
            prescaler = (int)(period*SYSCLCK/100);
        }
        else if(period >= 40000 && period <= 40000000)
        {
            pulse = 10000; 
            prescaler = (int)(period*SYSCLCK/10000);
        }
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7, ENABLE);
            
        //인터럽트 핸들러와 우선순위 설정
        NVIC_InitStructure.NVIC_IRQChannel =  TIM7_IRQn;
        NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 55;
        NVIC_InitStructure.NVIC_IRQChannelSubPriority = 62;
        NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
        NVIC_Init(&NVIC_InitStructure);
           
        //타이머 설정
        TIM_TimeBaseStructure.TIM_Period = pulse;
        TIM_TimeBaseStructure.TIM_Prescaler = prescaler;  
        TIM_TimeBaseStructure.TIM_ClockDivision = 0;
        TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
        
        TIM_TimeBaseInit(TIM7, &TIM_TimeBaseStructure);            
        TIM_Cmd(TIM7, ENABLE);        
        TIM_ITConfig(TIM7, TIM_IT_Update, ENABLE);
        
    }
}

void AcgPWM8_Setting(TimerChannel ch, int period)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;   
    TIM_OCInitTypeDef  TIM_OCInitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;
    
    int prescaler = 0;
    int pulse = 0;
    int dutycycle = 0;
    
    if(before_period[0] != period)
    {
	before_period[0] = period;
                  
        //타이머 주기 계산 함수
        if(period >= 100 && period <= 40000)
        {
            pulse = 100; 
            prescaler = (int)(period*SYSCLCK/100);
        }
        else if(period >= 40000 && period <= 40000000)
        {
            pulse = 10000; 
            prescaler = (int)(period*SYSCLCK/10000);
        }
            
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8, ENABLE);
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE); 
                  
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
            
        //타이머 설정
        TIM_TimeBaseStructure.TIM_Period = pulse;
        TIM_TimeBaseStructure.TIM_Prescaler = prescaler;
        TIM_TimeBaseStructure.TIM_ClockDivision = 0;
        TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
        TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;   
            
        TIM_TimeBaseInit(TIM8, &TIM_TimeBaseStructure);           
        TIM_Cmd(TIM8, ENABLE);             
        TIM_CtrlPWMOutputs(TIM8, ENABLE);
        
    }
    
    if(ch & TIM_01) //pwm ch1
    {
         if(PWM_ch1_using[7] == DISUSE)
         {
            PWM_ch1_using[7] = USE;
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
            GPIO_Init(GPIOC, &GPIO_InitStructure);
      
            //pwm 출력핀 설정
            TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
            TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
            TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;
            TIM_OCInitStructure.TIM_Pulse = dutycycle;
            TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
            TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;
            TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
            TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCIdleState_Reset;
            
            TIM_OC1Init(TIM8, &TIM_OCInitStructure); 
        
            TIM_OC1PreloadConfig(TIM8, TIM_OCPreload_Enable);
         }
        if(period >= 100 && period <= 40000)
        {
            TIM8->CCR1 = dutycycle;
        }         
        else if(period >= 40000 && period <= 40000000)
        {
            TIM8->CCR1 = dutycycle*100;
        }
    }
    if(ch & TIM_02) //pwm ch2
    {
         if(PWM_ch2_using[7] == DISUSE)
         {
            PWM_ch2_using[7] = USE;
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
            GPIO_Init(GPIOC, &GPIO_InitStructure);
              
            //pwm 출력핀 설정
            TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
            TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
            TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;
            TIM_OCInitStructure.TIM_Pulse = dutycycle;
            TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
            TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;
            TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
            TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCIdleState_Reset;
        
            TIM_OC2Init(TIM8, &TIM_OCInitStructure); 
        
            TIM_OC2PreloadConfig(TIM8, TIM_OCPreload_Enable);
         }
        if(period >= 100 && period <= 40000)
        {
            TIM8->CCR2 = dutycycle;
        }         
        else if(period >= 40000 && period <= 40000000)
        {
            TIM8->CCR2 = dutycycle*100;
        }
    }
    if(ch & TIM_03) //pwm ch3
    {
         if(PWM_ch3_using[7] == DISUSE)
         {
            PWM_ch3_using[7] = USE;
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
            GPIO_Init(GPIOC, &GPIO_InitStructure);
              
            //pwm 출력핀 설정
            TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
            TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
            TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;
            TIM_OCInitStructure.TIM_Pulse = dutycycle;
            TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
            TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;
            TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
            TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCIdleState_Reset;
        
            TIM_OC3Init(TIM8, &TIM_OCInitStructure); 
        
            TIM_OC3PreloadConfig(TIM8, TIM_OCPreload_Enable);
         }
        if(period >= 100 && period <= 40000)
        {
            TIM8->CCR3 = dutycycle;
        }         
        else if(period >= 40000 && period <= 40000000)
        {
            TIM8->CCR3 = dutycycle*100;
        }
    }
    if(ch & TIM_04) //pwm ch4
    {
         if(PWM_ch4_using[7] == DISUSE)
         {
            PWM_ch4_using[7] = USE;
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
            GPIO_Init(GPIOC, &GPIO_InitStructure);
              
            //pwm 출력핀 설정
            TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
            TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
            TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;
            TIM_OCInitStructure.TIM_Pulse = dutycycle;
            TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
            TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;
            TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
            TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCIdleState_Reset;
        
            TIM_OC4Init(TIM8, &TIM_OCInitStructure); 
        
            TIM_OC4PreloadConfig(TIM8, TIM_OCPreload_Enable);
         }
        if(period >= 100 && period <= 40000)
        {
            TIM8->CCR4 = dutycycle;
        }         
        else if(period >= 40000 && period <= 40000000)
        {
            TIM8->CCR4 = dutycycle*100;
        }
    }
}
void AcgPWM8(TimerChannel ch, long dutycycle)
{
    if(ch & TIM_01)//pwm ch1
    {

        if(before_period[7] >= 100 && before_period[7] <= 40000)
        {
            TIM8->CCR1 = dutycycle;
        }         
        else if(before_period[7] >= 40000 && before_period[7] <= 40000000)
        {
            TIM8->CCR1 = dutycycle*100;
        }
    }
    if(ch & TIM_02)//pwm ch2
    {
 
        if(before_period[7] >= 100 && before_period[7] <= 40000)
        {
            TIM8->CCR2 = dutycycle;
        }         
        else if(before_period[7] >= 40000 && before_period[7] <= 40000000)
        {
            TIM8->CCR2 = dutycycle*100;
        }
    }
    if(ch & TIM_03)//pwm ch3
    {

        if(before_period[7] >= 100 && before_period[7] <= 40000)
        {
            TIM8->CCR3 = dutycycle;
        }         
        else if(before_period[7] >= 40000 && before_period[7] <= 40000000)
        {
            TIM8->CCR3 = dutycycle*100;
        }
    }
    if(ch & TIM_04)//pwm ch4
    {
        
        if(before_period[7] >= 100 && before_period[7] <= 40000)
        {
            TIM8->CCR4 = dutycycle;
        }         
        else if(before_period[7] >= 40000 && before_period[7] <= 40000000)
        {
            TIM8->CCR4 = dutycycle*100;
        }
    }  
}

void TIM2_IRQHandler(void)
{
  if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
  {
     TIMER_02_interrupt();
     TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
  } 
}
void TIM3_IRQHandler(void)
{
  if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)
  {
     TIMER_03_interrupt();
     TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
  } 
}
void TIM4_IRQHandler(void)
{
  if (TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET)
  {
     TIMER_04_interrupt();
     TIM_ClearITPendingBit(TIM4, TIM_IT_Update);
  }
}
void TIM5_IRQHandler(void)
{
  if (TIM_GetITStatus(TIM5, TIM_IT_Update) != RESET)
  {
     TIMER_05_interrupt();
     TIM_ClearITPendingBit(TIM5, TIM_IT_Update);
  } 
}
void TIM6_IRQHandler(void)
{
 if (TIM_GetITStatus(TIM6, TIM_IT_Update) != RESET)
  {
   TIMER_06_interrupt();
   TIM_ClearITPendingBit(TIM6, TIM_IT_Update);
  }
}
void TIM7_IRQHandler(void)
{
  if (TIM_GetITStatus(TIM7, TIM_IT_Update) != RESET)
  {
     TIMER_07_interrupt();
     TIM_ClearITPendingBit(TIM7, TIM_IT_Update);
  } 
}










