#include "stm32f10x.h"
#include "AutoCodeGen.h"
#include <stdio.h>

#define MOTER_DIR            AcgGpioOut_F.Bit.GPIO_00
#define MOTER_STOP           AcgGpioOut_F.Bit.GPIO_02
#define MOTER_ENABLE         AcgGpioOut_F.Bit.GPIO_04

uint8_t Conf = 0;

void TIMER_02_interrupt()
{
    Conf = 1;
}

void main() 
{
  int16_t ROLL,PITCH;
  uint8_t temp[4];
  uint8_t receive;
  float math;
  
  AcgSystemClock_Setting(SYSCLK_40MHz);
  AcgGPIO_OutputSetting(GPIO_F ,0xffff);
  AcgGPIO_OutputSetting(GPIO_A ,0xffff);
  AcgUSART1_Setting(BAUDRATE_9600,WORDLENGTH_8,STOPBIT_1,PARITY_NONE,HWFLOWCONTROL_NONE);
  AcgPWM3_Setting(TIM_01,10000);
  AcgPWM3_Setting(TIM_02,10000);
  //AcgI2C2_setting(FAST);
  AcgADC1_Setting();
  AcgTIMER2_Setting(10000); 
  
  MOTER_DIR = 1;
  MOTER_STOP = 0;
  MOTER_ENABLE = 1;
  
  AcgGpioOut_A.Bit.GPIO_04 = 1;
  
  while(1)
  {
    
    if(Conf == 1)
    {
      
      //------------------------------------------------
      receive = AcgUSART1_rxc();
      if(receive == 'w')
      { 
          MOTER_DIR = 1;
          MOTER_STOP = 0;
          MOTER_ENABLE = 1;
          AcgPWM3(TIM_01,7);
          AcgPWM3(TIM_02,14);
      }
      else if(receive == 'a')
      {
         AcgPWM3(TIM_02,20);
      }
      else if(receive == 'd')
      {
          AcgPWM3(TIM_02,9);
      }
      else if(receive == 'x')
      {
        MOTER_DIR = 0;
        MOTER_STOP = 0;
        MOTER_ENABLE = 1;
        AcgPWM3(TIM_01,7);
      }
      else if(receive == 's')
      {
          MOTER_ENABLE = 1;
          MOTER_STOP = 1;
          MOTER_DIR = 1;
          AcgPWM3(TIM_01,0);

      }
      //---------------------------------------------
     // myARS_BufferRead(0x1c<<1, 0x3E, 4, temp);
       
     // ROLL  = ((int16_t)temp[1]<<8 | temp[0]);
      //PITCH = ((int16_t)temp[3]<<8 | temp[2]);            

      //--------------------------------------------- 
      math = (float)AcgADC1(ADC_00);
      math = 0.0000098*math*math -0.053*math +80.246;
      if(math > 40.0) math = 40.0;
      else if(math < 8.0) math = 8.0;
      //----------------------------------------------
        
     printf("ROLL : %3.3f  PITCH : %3.3f  ADC : %3.3f cm \n",(float)ROLL/100, (float)PITCH/100,math);
      
       Conf = 0;
    }
  }
}






