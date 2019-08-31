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

//SystemClock �ʱ�ȭ
void AcgSystemClock_Setting(SysClk clk);


//���� �Լ�
//���ͷ�Ʈ �ʱ�ȭ �Լ�
void Interrupt_Init();


//Enable Global interrupt
//��� �������� �ʱ�ȭ �� ����
//���������� ��� ������ ������ �� �Լ��� �Ἥ Global interrupt�� Enable �ؾ� �մϴ�.
void EnableGlobal_INT();


#endif /* ACG_SYSCLK_H_ */
