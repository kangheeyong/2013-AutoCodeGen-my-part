#ifndef EXTI_H
#define EXTI_H

#include <avr/io.h>
#include <avr/interrupt.h>


//  Pin Map for External Interrupt

//	EXTI_00 : PD0
//	EXTI_01 : PD1
//	EXTI_02 : PD2
//	EXTI_03 : PD3
//	EXTI_04 : PE4
//	EXTI_05 : PE5
//	EXTI_06 : PE6
//	EXTI_07 : PE7



//Interrupt trigger mode
typedef enum
{
  RISING = 0x03,
  FALLING = 0x02,
  LOW = 0x00,
  TOGGLE = 0x01   //4~7번 interrupt핀에만 존재 

}TriggerType;


typedef enum
{
  EXTI_00,
  EXTI_01,
  EXTI_02,
  EXTI_03,
  EXTI_04,
  EXTI_05,
  EXTI_06,
  EXTI_07

}EXTIChannel;


extern void EXTI_00_interrupt(void);
extern void EXTI_01_interrupt(void);
extern void EXTI_02_interrupt(void);
extern void EXTI_03_interrupt(void);
extern void EXTI_04_interrupt(void);
extern void EXTI_05_interrupt(void);
extern void EXTI_06_interrupt(void);
extern void EXTI_07_interrupt(void);




//외부 인터럽트 초기화 함수
void AcgEXTI_Setting(EXTIChannel ch, TriggerType Trigger);

#endif
