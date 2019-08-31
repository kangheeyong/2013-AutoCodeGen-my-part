#ifndef TIM_H
#define TIM_H

#include <avr/io.h>
#include <avr/interrupt.h>

//	Pin Map for PWM

//	PWM0 : PB4(TIMER_01)
//	PWM1 : PB5(TIMER_01), PB6(TIMER_02), PB7(TIMER_03)
//	PWM2 : PB7(TIMER_01)
//	PWM3 : PE3(TIMER_01), PE4(TIMER_02), PE5(TIMER_03)

typedef enum
{
  TIMER_01 = 1, // OC1A
  TIMER_02 = 2, // OC1B
  TIMER_03 = 4, // OC1C

}TIMERChannel;


extern void TIMER_00_interrupt(void);   //인터럽트 핸들러
extern void TIMER_01_interrupt(void);   //인터럽트 핸들러
extern void TIMER_02_interrupt(void);   //인터럽트 핸들러
extern void TIMER_03_interrupt(void);   //인터럽트 핸들러




void AcgTIMER0_Setting(long period);  //100us ~ 10ms 까지
void AcgPWM0_Setting(TIMERChannel ch, long period); //TIMER_01
void AcgPWM0(TIMERChannel ch, long dutycycle);

void AcgTIMER1_Setting(long period);   //100us ~ 4s 까지
void AcgPWM1_Setting(TIMERChannel ch, long period); //TIMER_01 , TIMER_02, TIMER_03
void AcgPWM1(TIMERChannel ch, long dutycycle);

void AcgTIMER2_Setting(long period);   //100us ~ 10ms 까지
void AcgPWM2_Setting(TIMERChannel ch, long period); //TIMER_01
void AcgPWM2(TIMERChannel ch, long dutycycle);

void AcgTIMER3_Setting(long period); //100us ~ 4s 까지
void AcgPWM3_Setting(TIMERChannel ch, long period); //TIMER_01,  TIMER_02, TIMER_03
void AcgPWM3(TIMERChannel ch, long dutycycle);

#endif

