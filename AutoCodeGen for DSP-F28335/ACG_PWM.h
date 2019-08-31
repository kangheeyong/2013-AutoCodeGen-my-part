#ifndef PWM_H
#define PWM_H

#include "DSP28x_Project.h"



//	Pin Map for PWM
//
//	PWM1A : Pin 5  (GPIO_00)
//	PWM1B : Pin 6  (GPIO_01)
//	PWM2A : Pin 7  (GPIO_02)
// 	PWM2B : Pin 10 (GPIO_03)
//	PWM3A : Pin 11 (GPIO_04)
//	PWM3B : Pin 12 (GPIO_05)
//	PWM4A : Pin 13 (GPIO_06)
//	PWM4B : Pin 16 (GPIO_07)
//	PWM5A : Pin 17 (GPIO_08)
//	PWM5B : Pin 18 (GPIO_09)
//	PWM6A : Pin 19 (GPIO_10)
//	PWM6B : Pin 20 (GPIO_11)
//
//




typedef enum
{
	TIMER_01 = 1,     //PWM_A
	TIMER_02 = 2      //PWM_B

}PWMChannel;




//	PWM 초기화 함수
/* 50ms ~ 1us */
void AcgPWM1_Setting(PWMChannel ch, Uint16 period);
void AcgPWM1(PWMChannel ch, int dutycycle);
void AcgPWM2_Setting(PWMChannel ch, Uint16 period);
void AcgPWM2(PWMChannel ch, int dutycycle);
void AcgPWM3_Setting(PWMChannel ch, Uint16 period);
void AcgPWM3(PWMChannel ch, int dutycycle);
void AcgPWM4_Setting(PWMChannel ch, Uint16 period);
void AcgPWM4(PWMChannel ch, int dutycycle);

void AcgPWM5_Setting(PWMChannel ch, Uint16 period);
void AcgPWM5(PWMChannel ch, int dutycycle);
void AcgPWM6_Setting(PWMChannel ch, Uint16 period);
void AcgPWM6(PWMChannel ch, int dutycycle);


#endif
