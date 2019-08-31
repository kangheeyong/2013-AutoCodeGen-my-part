#ifndef EXTI_H
#define EXTI_H

#include "DSP28x_Project.h"

// Pin Map for EXTI
//
// ExtiChannel A : EXTI_01 ~ EXTI_02��  GPIO �� (GPIO_00 ~ GPIO_31) �� ���� ����
// ExtiChannel B : EXTI_03 ~ EXTI_07��  GPIO �� (GPIO_32 ~ GPIO_63) �� ���� ����
//

interrupt void AcgEXTI1_ISR(void);
interrupt void AcgEXTI2_ISR(void);
interrupt void AcgEXTI3_ISR(void);
interrupt void AcgEXTI4_ISR(void);
interrupt void AcgEXTI5_ISR(void);
interrupt void AcgEXTI6_ISR(void);
interrupt void AcgEXTI7_ISR(void);

//interrupt trigger mode
typedef enum
{
	RISING = 1,
	FALLING	 = 0

}TriggerType;

typedef enum
{
  EXTI_01 = 1,
  EXTI_02 = 2,
  EXTI_03 = 3,
  EXTI_04 = 4,
  EXTI_05 = 5,
  EXTI_06 = 6,
  EXTI_07 = 7

}EXTIChannel;



//	interrupt �ʱ�ȭ �Լ�
void AcgEXTI_Setting(EXTIChannel ch, TriggerType trigger, Uint32 pin);

//  ���� �Լ�
void AcgEXTI_GpaSetting(EXTIChannel ch, TriggerType trigger,  Uint32 pin); // pin : �ܺ� ���ͷ�Ʈ�� ����� pin(0~31)�� ����
void AcgEXTI_GpbSetting(EXTIChannel ch, TriggerType trigger,  Uint32 pin);

// Exti Interrupt handler
extern void EXTI_01_interrupt();
extern void EXTI_02_interrupt();
extern void EXTI_03_interrupt();
extern void EXTI_04_interrupt();
extern void EXTI_05_interrupt();
extern void EXTI_06_interrupt();
extern void EXTI_07_interrupt();


#endif
