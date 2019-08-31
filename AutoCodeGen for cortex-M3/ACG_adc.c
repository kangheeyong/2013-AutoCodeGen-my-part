#include "stm32f10x.h"
#include "ACG_adc.h"


void AcgADC1_Setting()
{
  ADC_InitTypeDef ADC_InitStructure;
  
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);  
 
  //ADC 환경 설정
  ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;     
  ADC_InitStructure.ADC_ScanConvMode = DISABLE;             
  ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;       
  ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
  ADC_InitStructure.ADC_NbrOfChannel = 1;
  ADC_Init(ADC1, &ADC_InitStructure);
  
  ADC_Cmd(ADC1, ENABLE);
  
  ADC_ResetCalibration(ADC1);
  
  while(ADC_GetResetCalibrationStatus(ADC1));
    
  ADC_StartCalibration(ADC1);
  
  while(ADC_GetCalibrationStatus(ADC1));
   
}

uint16_t AcgADC1(AdcChannel ch)
{ 
   
    ADC_RegularChannelConfig(ADC1, ch, 1, ADC_SampleTime_55Cycles5); //채널과 샘플링 사이클 설정
   
    ADC_SoftwareStartConvCmd(ADC1, ENABLE); //ADC1변환 시작 
    
    while(ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC) == 0); //변환이 완료되면 1
    
    return ADC1->DR; //변환값 반환 
}

void AcgADC2_Setting()
{
  ADC_InitTypeDef ADC_InitStructure;
  
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC2, ENABLE); 
 
  //ADC 환경 설정
  ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
  ADC_InitStructure.ADC_ScanConvMode = DISABLE;
  ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;
  ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
  ADC_InitStructure.ADC_NbrOfChannel = 1;
  ADC_Init(ADC2, &ADC_InitStructure);

  ADC_Cmd(ADC2, ENABLE);
  
  ADC_ResetCalibration(ADC2);
  
  while(ADC_GetResetCalibrationStatus(ADC2));
    
  ADC_StartCalibration(ADC2);
  
  while(ADC_GetCalibrationStatus(ADC2));
   
}

uint16_t AcgADC2(AdcChannel ch)
{ 
   
    ADC_RegularChannelConfig(ADC2, ch, 1, ADC_SampleTime_55Cycles5); //채널과 샘플링 사이클 설정 
   
    ADC_SoftwareStartConvCmd(ADC2, ENABLE); //ADC1변환 시작 
    
    while(ADC_GetFlagStatus(ADC2,ADC_FLAG_EOC) == 0);  //변환이 완료되면 1
    
    return ADC2->DR; //변환값 반환 
}

