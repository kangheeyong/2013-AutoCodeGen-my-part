
#ifndef ACG_ADC_H
#define ACG_ADC_H

#include "ACG_datatype.h"


//	Pin Map for ADC

//	ADC1_00 or ADC2_00 : PA0
//	ADC1_01 or ADC2_01 : PA1
//	ADC1_02 or ADC2_02 : PA2
//	ADC1_03 or ADC2_03 : PA3
//	ADC1_04 or ADC2_04 : PA4
//	ADC1_05 or ADC2_05 : PA5
//	ADC1_06 or ADC2_06 : PA6
//	ADC1_07 or ADC2_07 : PA7
//	ADC1_08 or ADC2_08 : PB0
//	ADC1_09 or ADC2_09 : PB1
//	ADC1_10 or ADC2_10 : PC0
//	ADC1_11 or ADC2_11 : PC1
//      ADC1_12 or ADC2_12 : PC2
//	ADC1_13 or ADC2_13 : PC3
//	ADC1_14 or ADC2_14 : PC4
//	ADC1_15 or ADC2_15 : PC5

typedef enum
{
  ADC_00,     
  ADC_01, 
  ADC_02, 
  ADC_03, 
  ADC_04, 
  ADC_05, 
  ADC_06, 
  ADC_07, 
  ADC_08, 
  ADC_09, 
  ADC_10, 
  ADC_11, 
  ADC_12, 
  ADC_13, 
  ADC_14, 
  ADC_15, 
}AdcChannel;

// ADC1 초기화 함수
void AcgADC1_Setting();

// 사용 함수  
// 파라미터로 channel을 입력하면 ADC 변환값을 반환한다.
uint16_t AcgADC1(AdcChannel ch);

// ADC2 초기화 함수
void AcgADC2_Setting();

// 사용 함수  
// 파라미터로 channel을 입력하면 ADC 변환값을 반환한다.
uint16_t AcgADC2(AdcChannel ch); 

#endif


