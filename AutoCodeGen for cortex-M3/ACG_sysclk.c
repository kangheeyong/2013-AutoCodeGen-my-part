#include "stm32f10x.h"
#include "ACG_sysclk.h"

int SYSCLCK;

void AcgSystemClock_Setting(SysClk clk)
{
  int  HSEStartUpStatus;
  
  if(clk == SYSCLK_16MHz) SYSCLCK = 16;
  else if(clk == SYSCLK_24MHz) SYSCLCK = 24;
  else if(clk == SYSCLK_32MHz) SYSCLCK = 32;
  else if(clk == SYSCLK_40MHz) SYSCLCK = 40;
  else if(clk == SYSCLK_48MHz) SYSCLCK = 48;
  else if(clk == SYSCLK_56MHz) SYSCLCK = 56;
  else if(clk == SYSCLK_64MHz) SYSCLCK = 64;
  else SYSCLCK = 72;
  
  assert_param(IS_RCC_Sys(RCC_PLLMul));
  
  RCC_DeInit(); 
  
  RCC_HSEConfig(RCC_HSE_ON); 
  
  HSEStartUpStatus = RCC_WaitForHSEStartUp(); 

  if (HSEStartUpStatus == SUCCESS)
  {
      FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable); 
      FLASH_SetLatency(FLASH_Latency_2); 
      RCC_HCLKConfig(RCC_SYSCLK_Div1);
      RCC_PCLK2Config(RCC_HCLK_Div1);
      RCC_PCLK1Config(RCC_HCLK_Div2);
  }
  RCC_PLLConfig(RCC_PLLSource_HSE_Div1, clk); 
  
  RCC_PLLCmd(ENABLE);
  while (RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET) ; 
      
  RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
  while(RCC_GetSYSCLKSource() != 0x08); 
}
