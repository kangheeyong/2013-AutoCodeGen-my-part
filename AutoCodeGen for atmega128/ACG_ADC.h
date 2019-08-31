#ifndef ADC_H
#define ADC_H

#include <avr/io.h>
#include <avr/delay.h>


//	Pin Map for ADC

//	ADC_00 : PF0
//	ADC_01 : PF1
//	ADC_02 : PF2
//	ADC_03 : PF3
//	ADC_04 : PF4
//	ADC_05 : PF5
//	ADC_06 : PF6
//	ADC_07 : PF7



typedef enum
{
  ADC_00,
  ADC_01,
  ADC_02,
  ADC_03,
  ADC_04,
  ADC_05,
  ADC_06,
  ADC_07

}ADCChannel;


// ADC 초기화 함수
void AcgADC_Setting();      
   
// 사용 함수  
// 파라미터로 channel을 입력하면 ADC 변환값을 반환한다.
int AcgADC(ADCChannel ch); 
                               

#endif ADC_H
