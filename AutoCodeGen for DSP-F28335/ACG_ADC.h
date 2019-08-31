#ifndef ACD_H
#define ADC_H

#include "DSP28x_Project.h"

//  Pin Map for ADC
//
//  ADCINA
//  ADC_00 : Pin 42  ( ADCINA0 )
//  ADC_01 : Pin 41  ( ADCINA1 )
//  ADC_02 : Pin 40  ( ADCINA2 )
//  ADC_03 : Pin 39  ( ADCINA3 )
//  ADC_04 : Pin 38  ( ADCINA4 )
//  ADC_05 : Pin 37  ( ADCINA5 )
//  ADC_06 : Pin 36  ( ADCINA6 )
//  ADC_07 : Pin 35  ( ADCINA7 )
//
//  ADCINB
//  ADC_08 : Pin 46  ( ADCINB0 )
//  ADC_09 : Pin 47  ( ADCINB1 )
//  ADC_10 : Pin 48  ( ADCINB2 )
//  ADC_11 : Pin 49  ( ADCINB3 )
//  ADC_12 : Pin 50  ( ADCINB4 )
//  ADC_13 : Pin 51  ( ADCINB5 )
//  ADC_14 : Pin 52  ( ADCINB6 )
//  ADC_15 : Pin 53  ( ADCINB7 )


typedef enum
{
	ADC_00 = 0,
	ADC_01,
	ADC_02,
	ADC_03,
	ADC_04,
	ADC_05,
	ADC_06,
	ADC_07,

	ADC_08 = 8,
	ADC_09,
	ADC_10,
	ADC_11,
	ADC_12,
	ADC_13,
	ADC_14,
	ADC_15

}ADCChannel;

// ADC 초기화 함수
void AcgADC_Setting();

// 사용 함수
// 파라미터로 channel을 입력하면 ADC 변환 값을 반환한다.
Uint16 AcgADC(ADCChannel ch);

#endif
