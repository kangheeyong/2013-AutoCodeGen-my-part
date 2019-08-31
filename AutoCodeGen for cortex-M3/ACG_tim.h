#ifndef ACG_TIM_H_
#define ACG_TIM_H_

#include "ACG_datatype.h"

//	Pin Map for PWM

//	PWM1 : PE9(TIMER_01), PE11(TIMER_02), PE13(TIMER_03), PE14(TIMER_04)
//	PWM2 : PA0(TIMER_01), PA1 (TIMER_02), PA2 (TIMER_03), PA3 (TIMER_04)
//	PWM3 : PA6(TIMER_01), PA7 (TIMER_02), PB0 (TIMER_03), PB1 (TIMER_04)
//	PWM4 : PB6(TIMER_01), PB7 (TIMER_02), PB8 (TIMER_03), PB9 (TIMER_04)
//	PWM5 : PA0(TIMER_01), PA1 (TIMER_02), PA2 (TIMER_03), PA3 (TIMER_04)
//	PWM8 : PC6(TIMER_01), PC7 (TIMER_02), PC8 (TIMER_03), PC9 (TIMER_04)

typedef enum
{
    TIM_01 = 1,
    TIM_02 = 2,
    TIM_03 = 4,
    TIM_04 = 8
}TimerChannel;


extern void TIMER_02_interrupt();  //인터럽트 핸들러
extern void TIMER_03_interrupt();  //인터럽트 핸들러
extern void TIMER_04_interrupt();  //인터럽트 핸들러
extern void TIMER_05_interrupt();  //인터럽트 핸들러
extern void TIMER_06_interrupt();  //인터럽트 핸들러
extern void TIMER_07_interrupt();  //인터럽트 핸들러



void AcgPWM1_Setting(TimerChannel ch, int period); //100us ~ 5s 까지 

void AcgTIMER2_Setting(int period); 
void AcgPWM2_Setting(TimerChannel ch, int period); //100us ~ 5s 까지 
void AcgPWM2(TimerChannel ch, long dutycycle);

void AcgTIMER3_Setting(int period);
void AcgPWM3_Setting(TimerChannel ch, int period); //100us ~ 5s 까지 
void AcgPWM3(TimerChannel ch, long dutycycle);

void AcgTIMER4_Setting(int period);
void AcgPWM4_Setting(TimerChannel ch, int period); //100us ~ 5s 까지 
void AcgPWM4(TimerChannel ch, long dutycycle);

void AcgTIMER5_Setting(int period);
void AcgPWM5_Setting(TimerChannel ch, int period); //100us ~ 5s 까지 
void AcgPWM5(TimerChannel ch, long dutycycle);

void AcgTIMER6_Setting(int period); 

void AcgTIMER7_Setting(int period); 

void AcgPWM8_Setting(TimerChannel ch, int period); //100us ~ 5s 까지
void AcgPWM8(TimerChannel ch, long dutycycle);

#endif