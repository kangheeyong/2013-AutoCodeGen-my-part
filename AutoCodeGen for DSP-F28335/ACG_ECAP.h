/*
 * ACG_ECAP.h
 *
 *  Created on: 2013. 7. 28.
 *      Author: RODONGWAN
 */

#ifndef ACG_ECAP_H_
#define ACG_ECAP_H_

#include "DSP28x_Project.h"

//	Pin Map for ECAP
//
//	ECAP_01 : Pin 142 (GPIO_34)
//	ECAP_02 : Pin 150 (GPIO_37)
//	ECAP_03 : Pin 72  (GPIO_26)
//	ECAP_04 : Pin 73  (GPIO_27)
//	ECAP_05 : Pin 88  (GPIO_48)
//	ECAP_06 : Pin 89  (GPIO_49)

// System Clock   ( ACG_SYSCLK.c에 선언 )
extern float SystemClock;

typedef enum
{
	ECAP_01,
	ECAP_02,
	ECAP_03,
	ECAP_04,
	ECAP_05,
	ECAP_06
}ECAPChannel;

//Ecap APWM 초기화  us 단위
void AcgECAP1_Setting(Uint32 period);
void AcgECAP1(int dutycycle);
void AcgECAP2_Setting(Uint32 period);
void AcgECAP2(int dutycycle);
void AcgECAP3_Setting(Uint32 period);
void AcgECAP3(int dutycycle);
void AcgECAP4_Setting(Uint32 period);
void AcgECAP4(int dutycycle);
void AcgECAP5_Setting(Uint32 period);
void AcgECAP5(int dutycycle);
void AcgECAP6_Setting(Uint32 period);
void AcgECAP6(int dutycycle);



//Ecap APWM Interrupt 함수
interrupt void AcgECAP1_ISR(void);
interrupt void AcgECAP2_ISR(void);
interrupt void AcgECAP3_ISR(void);
interrupt void AcgECAP4_ISR(void);
interrupt void AcgECAP5_ISR(void);
interrupt void AcgECAP6_ISR(void);


//내부 함수
void AcgECAP_GpioSetting(ECAPChannel ch);
void AcgECAP_RgSetting(ECAPChannel ch,Uint32 period,Uint32 dutycycle);


// Ecap Interrupt handler
extern void ECAP_01_interrupt();
extern void ECAP_02_interrupt();
extern void ECAP_03_interrupt();
extern void ECAP_04_interrupt();
extern void ECAP_05_interrupt();
extern void ECAP_06_interrupt();



#endif /* ACG_ECAP_H_ */
