#include "stm32f10x.h"
#include "ACG_exti.h"

uint8_t PreemptionPriority[16] = {6,7,8,9,10,23,23,23,23,23,40,40,40,40,40,40};
uint8_t SubPriority[16] = {13,14,15,16,17,30,30,30,30,30,47,47,47,47,47,47};

void AcgEXTI_Setting(ExitChannel ch,TriggerType Trigger)
{    
  NVIC_InitTypeDef   NVIC_InitStructure;
  EXTI_InitTypeDef   EXTI_InitStructure;
  GPIO_InitTypeDef   GPIO_InitStructure;
   
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE); 
  
  //pin 환경 설정 
  GPIO_InitStructure.GPIO_Pin =  PIN << ch;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOE, &GPIO_InitStructure);  
  
  GPIO_EXTILineConfig(GPIO_PortSourceGPIOE, ch);
  
  //exti 환경 설정 
  EXTI_InitStructure.EXTI_Line =  LINE << ch;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = (EXTITrigger_TypeDef)Trigger; 
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);

  //인터럽트 핸들러와 우선순위 설정
  if(ch == 0) NVIC_InitStructure.NVIC_IRQChannel =  EXTI0_IRQn;
  else if(ch == 1) NVIC_InitStructure.NVIC_IRQChannel =  EXTI1_IRQn;
  else if(ch == 2) NVIC_InitStructure.NVIC_IRQChannel =  EXTI2_IRQn;
  else if(ch == 3) NVIC_InitStructure.NVIC_IRQChannel =  EXTI3_IRQn;
  else if(ch == 4) NVIC_InitStructure.NVIC_IRQChannel =  EXTI4_IRQn;
  else if(ch == 5) NVIC_InitStructure.NVIC_IRQChannel =  EXTI9_5_IRQn;
  else if(ch == 6) NVIC_InitStructure.NVIC_IRQChannel =  EXTI9_5_IRQn;
  else if(ch == 7) NVIC_InitStructure.NVIC_IRQChannel =  EXTI9_5_IRQn;
  else if(ch == 8) NVIC_InitStructure.NVIC_IRQChannel =  EXTI9_5_IRQn;
  else if(ch == 9) NVIC_InitStructure.NVIC_IRQChannel =  EXTI9_5_IRQn;
  else if(ch == 10) NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;
  else if(ch == 11) NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;
  else if(ch == 12) NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;
  else if(ch == 13) NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;
  else if(ch == 14) NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;
  else NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;
   
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = PreemptionPriority[ch]; //첫번째 우선순위
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = SubPriority[ch]; //두번째 우선순위 
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

}



//PendingBit를 클리어 하지 않으면 인터럽트가 다시 발생하지 않는다.
//0 ~ 4 인터럽트는 각각의 핸들러를 갖고있지만
//5 ~ 9, 10 ~ 15 는 각각 하나식 인터럽트 핸들러를 갖는다.

void EXTI0_IRQHandler(void)
{
  if(EXTI_GetITStatus(EXTI_Line0) == SET)
  {
    EXTI_00_interrupt();
    EXTI_ClearITPendingBit(EXTI_Line0);
  }
} 

void EXTI1_IRQHandler(void)
{
  if(EXTI_GetITStatus(EXTI_Line1) == SET)
  {
    EXTI_01_interrupt();
    EXTI_ClearITPendingBit(EXTI_Line1); 
  }
} 

void EXTI2_IRQHandler(void)
{
  if(EXTI_GetITStatus(EXTI_Line2) == SET)
  {
    EXTI_02_interrupt();
    EXTI_ClearITPendingBit(EXTI_Line2);
  }
} 

void EXTI3_IRQHandler(void)
{
  if(EXTI_GetITStatus(EXTI_Line3) == SET)
  {
    EXTI_03_interrupt();
    EXTI_ClearITPendingBit(EXTI_Line3);
  }
} 

void EXTI4_IRQHandler(void)
{
  if(EXTI_GetITStatus(EXTI_Line4) == SET)
  {
    EXTI_04_interrupt();
    EXTI_ClearITPendingBit(EXTI_Line4);
  }
}  

void EXTI9_5_IRQHandler(void)
{
  if(EXTI_GetITStatus(EXTI_Line5) == SET)
  {
    EXTI_05_interrupt();
    EXTI_ClearITPendingBit(EXTI_Line5);
  }
  if(EXTI_GetITStatus(EXTI_Line6) == SET)
  {
    EXTI_06_interrupt();
    EXTI_ClearITPendingBit(EXTI_Line6);
  }
  if(EXTI_GetITStatus(EXTI_Line7) ==SET)
  {
    EXTI_07_interrupt();
    EXTI_ClearITPendingBit(EXTI_Line7);
  }
  if(EXTI_GetITStatus(EXTI_Line8) == SET)
  {
    EXTI_08_interrupt();
    EXTI_ClearITPendingBit(EXTI_Line8);
  }
  if(EXTI_GetITStatus(EXTI_Line9) == SET)
  {
    EXTI_09_interrupt();
    EXTI_ClearITPendingBit(EXTI_Line9);
  }
    
}  
void EXTI15_10_IRQHandler(void)
{
  if(EXTI_GetITStatus(EXTI_Line10) == SET)
  {
    EXTI_10_interrupt();
    EXTI_ClearITPendingBit(EXTI_Line10);
  }
  if(EXTI_GetITStatus(EXTI_Line11) == SET)
  {
    EXTI_11_interrupt();
    EXTI_ClearITPendingBit(EXTI_Line11);     
  }
  if(EXTI_GetITStatus(EXTI_Line12) == SET)
  {
    EXTI_12_interrupt();
    EXTI_ClearITPendingBit(EXTI_Line12);
  }
  if(EXTI_GetITStatus(EXTI_Line13) == SET)
  {
    EXTI_13_interrupt();
    EXTI_ClearITPendingBit(EXTI_Line13);
  }
  if(EXTI_GetITStatus(EXTI_Line14) == SET)
  {
    EXTI_14_interrupt();
    EXTI_ClearITPendingBit(EXTI_Line14);
  }
  if(EXTI_GetITStatus(EXTI_Line15) == SET)
  {
    EXTI_15_interrupt();
    EXTI_ClearITPendingBit(EXTI_Line15);
  }
}

