#include "stm32f10x.h"
#include "ACG_enc.h"

char enc_using[8] = {0,0,0,0,0,0,0,0};


void AcgENC1_Setting(int max)
{
  if(enc_using[0] == DISUSE)
  {
      enc_using[0] = USE;
      GPIO_InitTypeDef GPIO_InitStructure;
      TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
        
      RCC_APB2PeriphClockCmd( RCC_APB2Periph_TIM1, ENABLE); 
      RCC_APB2PeriphClockCmd( RCC_APB2Periph_AFIO | RCC_APB2Periph_GPIOE, ENABLE); 
        
      GPIO_PinRemapConfig ( GPIO_FullRemap_TIM1, ENABLE );
         
      //GPIO Pin 설정 
      GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_11 ; 
      GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 
      GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
      GPIO_Init(GPIOE, &GPIO_InitStructure);
          
      //Timer 설정 
      TIM_TimeBaseStructure.TIM_Prescaler = 1;   
      TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
      TIM_TimeBaseStructure.TIM_Period = max; 
      TIM_TimeBaseStructure.TIM_ClockDivision = 0; 
      TIM_TimeBaseStructure.TIM_RepetitionCounter = 0; 
      TIM_TimeBaseInit( TIM1, &TIM_TimeBaseStructure ); 
      //타이머를 엔코더 카운터로 사용 
      TIM_EncoderInterfaceConfig(TIM1, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising); 
      
      TIM_Cmd( TIM1, ENABLE ); 
  }  
}
UINT16 AcgENC1()
{
  return  TIM1->CNT;
}
void AcgENC2_Setting(int max)
{
  if(enc_using[1] == DISUSE)
  {
      enc_using[1] = USE;
      GPIO_InitTypeDef GPIO_InitStructure;
      TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
        
      RCC_APB1PeriphClockCmd( RCC_APB1Periph_TIM2, ENABLE); 
      RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); 
    
      //GPIO Pin 설정 
      GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 ; 
      GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 
      GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
      GPIO_Init(GPIOA, &GPIO_InitStructure);
      
      //Timer 설정 
      TIM_TimeBaseStructure.TIM_Prescaler = 1;   
      TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
      TIM_TimeBaseStructure.TIM_Period = max; 
      TIM_TimeBaseStructure.TIM_ClockDivision = 0; 
      TIM_TimeBaseStructure.TIM_RepetitionCounter = 0; 
      TIM_TimeBaseInit( TIM2, &TIM_TimeBaseStructure ); 
      //타이머를 엔코더 카운터로 사용 
      TIM_EncoderInterfaceConfig(TIM2, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising); 
      
      TIM_Cmd( TIM2, ENABLE );
  }
}
UINT16 AcgENC2()
{
  return  TIM2->CNT;
}

void AcgENC3_Setting(int max)
{
  if(enc_using[2] == DISUSE)
  {
      enc_using[2] = USE;
      GPIO_InitTypeDef GPIO_InitStructure;
      TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
        
      RCC_APB1PeriphClockCmd( RCC_APB1Periph_TIM3, ENABLE); 
      RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA, ENABLE); 
    
      //GPIO Pin 설정 
      GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7 ; 
      GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 
      GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
      GPIO_Init(GPIOA, &GPIO_InitStructure);
      
      //Timer 설정 
      TIM_TimeBaseStructure.TIM_Prescaler = 1;   
      TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
      TIM_TimeBaseStructure.TIM_Period = max; 
      TIM_TimeBaseStructure.TIM_ClockDivision = 0; 
      TIM_TimeBaseStructure.TIM_RepetitionCounter = 0; 
      TIM_TimeBaseInit( TIM3, &TIM_TimeBaseStructure ); 
      //타이머를 엔코더 카운터로 사용 
      TIM_EncoderInterfaceConfig(TIM3, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising); 
      
      TIM_Cmd( TIM3, ENABLE );

  }
}
UINT16 AcgENC3()
{
  return  TIM3->CNT;
}
void AcgENC4_Setting(int max)
{
  if(enc_using[3] == DISUSE)
  {
      enc_using[3] = USE;
      GPIO_InitTypeDef GPIO_InitStructure;
      TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
        
      RCC_APB1PeriphClockCmd( RCC_APB1Periph_TIM4, ENABLE); 
      RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); 
    
      //GPIO Pin 설정 
      GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7 ; 
      GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 
      GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
      GPIO_Init(GPIOB, &GPIO_InitStructure);
      
      //Timer 설정 
      TIM_TimeBaseStructure.TIM_Prescaler = 1;   
      TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
      TIM_TimeBaseStructure.TIM_Period = max; 
      TIM_TimeBaseStructure.TIM_ClockDivision = 0; 
      TIM_TimeBaseStructure.TIM_RepetitionCounter = 0; 
      TIM_TimeBaseInit( TIM4, &TIM_TimeBaseStructure ); 
      //타이머를 엔코더 카운터로 사용 
      TIM_EncoderInterfaceConfig(TIM4, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising); 
      
      TIM_Cmd( TIM4, ENABLE );
  }
}
UINT16 AcgENC4()
{
  return  TIM4->CNT;
}
void AcgENC5_Setting(int max)
{
  if(enc_using[4] == DISUSE)
  {
      enc_using[4] = USE;
      GPIO_InitTypeDef GPIO_InitStructure;
      TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
        
      RCC_APB1PeriphClockCmd( RCC_APB1Periph_TIM5, ENABLE); 
      RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA, ENABLE); 
    
      //GPIO Pin 설정 
      GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 ; 
      GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 
      GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
      GPIO_Init(GPIOA, &GPIO_InitStructure);
      
      //Timer 설정 
      TIM_TimeBaseStructure.TIM_Prescaler = 1;   
      TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
      TIM_TimeBaseStructure.TIM_Period = max; 
      TIM_TimeBaseStructure.TIM_ClockDivision = 0; 
      TIM_TimeBaseStructure.TIM_RepetitionCounter = 0; 
      TIM_TimeBaseInit( TIM5, &TIM_TimeBaseStructure ); 
      //타이머를 엔코더 카운터로 사용 
      TIM_EncoderInterfaceConfig(TIM5, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising); 
      
      TIM_Cmd( TIM5, ENABLE );
  }
}
UINT16 AcgENC5()
{
  return  TIM5->CNT;
}
void AcgENC8_Setting(int max)
{
  if(enc_using[7] == DISUSE)
  {
      enc_using[7] = USE;
      GPIO_InitTypeDef GPIO_InitStructure;
      TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
        
      RCC_APB2PeriphClockCmd( RCC_APB2Periph_TIM8, ENABLE); 
      RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOC, ENABLE); 
    
      //GPIO Pin 설정 
      GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7 ; 
      GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 
      GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
      GPIO_Init(GPIOC, &GPIO_InitStructure);
      
      //Timer 설정 
      TIM_TimeBaseStructure.TIM_Prescaler = 1;   
      TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
      TIM_TimeBaseStructure.TIM_Period = max; 
      TIM_TimeBaseStructure.TIM_ClockDivision = 0; 
      TIM_TimeBaseStructure.TIM_RepetitionCounter = 0; 
      TIM_TimeBaseInit( TIM8, &TIM_TimeBaseStructure ); 
      
      //타이머를 엔코더 카운터로 사용 
      TIM_EncoderInterfaceConfig(TIM8, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising); 
      
      TIM_Cmd( TIM8, ENABLE ); 

  }
}
UINT16 AcgENC8()
{
  return  TIM8->CNT;
}










