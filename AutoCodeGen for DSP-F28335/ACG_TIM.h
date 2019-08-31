/*
 * ACG_TIM.h
 *
 *  Created on: 2013. 7. 11.
 *      Author: ssm
 */

#ifndef ACG_TIM_H_
#define ACG_TIM_H_

#include "DSP28x_Project.h"

//	cpuTimer0, cpuTimer1, cpuTimer2  3���� ������ �ִ�.
//
extern float SystemClock;  //System Clock


// Timer interrupt vector
interrupt void AcgTIMER0_ISR(void);
interrupt void AcgTIMER1_ISR(void);
interrupt void AcgTIMER2_ISR(void);


//TIMERx �ʱ�ȭ
void AcgTIMER0_Setting(long period);  //Timer0 setting period : us ����
void AcgTIMER1_Setting(long period);  //Timer1 setting period : us ����
void AcgTIMER2_Setting(long period);  //Timer2 setting period : us ����


// ���� �Լ�
void AcgTIMER_Setting();              //Init CPU Timers


// TIMER Interrupt handler
extern void TIMER_00_interrupt(void);
extern void TIMER_01_interrupt(void);
extern void TIMER_02_interrupt(void);


#endif /* ACG_TIM_H_ */
