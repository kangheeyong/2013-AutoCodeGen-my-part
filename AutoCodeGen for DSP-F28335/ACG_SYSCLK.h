/*
 * ACG_SYSCLK.h
 *
 *  Created on: 2013. 7. 26.
 *      Author: RODONGWAN
 */

#ifndef ACG_SYSCLK_H_
#define ACG_SYSCLK_H_

#include "DSP28x_Project.h"

//OSCCLK = 30Mhz



//System Clock
typedef enum
{
	SYSCLK_15MHz  = 1,  // (OSCCLK*1)/2
	SYSCLK_30MHz  = 2,  // (OSCCLK*2)/2
	SYSCLK_45MHz  = 3,  // (OSCCLK*3)/2
	SYSCLK_60MHz  = 4,  // (OSCCLK*4)/2
	SYSCLK_75MHz  = 5,  // (OSCCLK*5)/2
	SYSCLK_90MHz  = 6,  // (OSCCLK*6)/2
	SYSCLK_105MHz = 7,  // (OSCCLK*7)/2
	SYSCLK_120MHz = 8,  // (OSCCLK*8)/2
	SYSCLK_135MHz = 9,  // (OSCCLK*9)/2
    SYSCLK_150MHz = 10  // (OSCCLK*10)/2

}SysClk;

//SystemClock 초기화
void AcgSystemClock_Setting(SysClk clk);


//내부 함수
//인터럽트 초기화 함수
void Interrupt_Init();


//Enable Global interrupt
//모든 레지스터 초기화 후 실행
//레지스터의 모든 설정이 끝나고 이 함수를 써서 Global interrupt를 Enable 해야 합니다.
void EnableGlobal_INT();


#endif /* ACG_SYSCLK_H_ */
