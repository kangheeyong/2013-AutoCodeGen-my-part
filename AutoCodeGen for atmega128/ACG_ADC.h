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


// ADC �ʱ�ȭ �Լ�
void AcgADC_Setting();      
   
// ��� �Լ�  
// �Ķ���ͷ� channel�� �Է��ϸ� ADC ��ȯ���� ��ȯ�Ѵ�.
int AcgADC(ADCChannel ch); 
                               

#endif ADC_H
