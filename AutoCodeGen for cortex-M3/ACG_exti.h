#ifndef ACG_EXTI_H
#define ACG_EXTI_H

#include "ACG_datatype.h"

//  Pin Map for External Interrupt

//	EXTI_00 : PD0
//	EXTI_01 : PD1
//	EXTI_02 : PD2
//	EXTI_03 : PD3
//	EXTI_04 : PE4
//	EXTI_05 : PE5
//	EXTI_06 : PE6
//	EXTI_07 : PE7
//	EXTI_08 : PE8
//	EXTI_09 : PE9
//	EXTI_10 : PE10
//	EXTI_11 : PE11
//	EXTI_12 : PE12
//	EXTI_13 : PE13
//	EXTI_14 : PE14
//	EXTI_15 : PE15

#define PIN     ((uint32_t)0x00001) 
#define LINE    ((uint32_t)0x00001) 

typedef enum
{
  RISING = 0x08,
  FALLING = 0x0C,  
  TOGGLE = 0x10
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
  EXTI_07,  
  EXTI_08,  
  EXTI_09,  
  EXTI_10,  
  EXTI_11,  
  EXTI_12,  
  EXTI_13,  
  EXTI_14,  
  EXTI_15   
}ExitChannel;

extern void EXTI_00_interrupt(void);
extern void EXTI_01_interrupt(void);
extern void EXTI_02_interrupt(void);
extern void EXTI_03_interrupt(void);
extern void EXTI_04_interrupt(void);
extern void EXTI_05_interrupt(void);
extern void EXTI_06_interrupt(void);
extern void EXTI_07_interrupt(void);
extern void EXTI_08_interrupt(void);
extern void EXTI_09_interrupt(void);
extern void EXTI_10_interrupt(void);
extern void EXTI_11_interrupt(void);
extern void EXTI_12_interrupt(void);
extern void EXTI_13_interrupt(void);
extern void EXTI_14_interrupt(void);
extern void EXTI_15_interrupt(void);


//외부 인터럽트 초기화 함수
void AcgEXTI_Setting(ExitChannel ch,TriggerType Trigger); 

#endif


