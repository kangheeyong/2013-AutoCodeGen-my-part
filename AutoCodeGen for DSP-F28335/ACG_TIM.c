/*
 * ACG_TIM.c
 *
 *  Created on: 2013. 7. 11.
 *      Author: ssm
 */

#include "ACG_TIM.h"

unsigned char TimerInitCheck = 0;



void AcgTIMER0_Setting(long period)
{

	if(TimerInitCheck == 0)  //Timer_Setting이 되었는지 체크하여 안되었으면 실행 (한 번만 실행)
	{
		AcgTIMER_Setting();
		TimerInitCheck = 1;
	}

	//interrupt vector remapping
	EALLOW;
    PieVectTable.TINT0 = &AcgTIMER0_ISR;
	EDIS;


	float Cpu_Clk = SystemClock;				// 현재 시스템 클럭을 설정 (MHz 단위)
	float Timer_Prd = (float)period;		// 타이머 주기 설정 (usec 단위)

	// CPU Timer0 을 1초 주기로 설정
	ConfigCpuTimer(&CpuTimer0, Cpu_Clk, Timer_Prd);

	StartCpuTimer0();

	// CPU Timer0 인터럽트 활성화
	PieCtrlRegs.PIEIER1.bit.INTx7 = 1;			// PIE 인터럽트(TINT0) 활성화
	IER |= M_INT1; 								// CPU 인터럽트(INT1)  활성화


}

void AcgTIMER1_Setting(long period)
{

	if(TimerInitCheck == 0)   //Timer_Setting이 되었는지 체크하여 안되었으면 실행 (한 번만 실행)
	{
		AcgTIMER_Setting();
		TimerInitCheck = 1;
	}

	//interrupt vector remapping
	EALLOW;
	PieVectTable.XINT13 = &AcgTIMER1_ISR;
	EDIS;

	float Cpu_Clk = SystemClock;				// 현재 시스템 클럭을 설정 (MHz 단위)
	float Timer_Prd = (float)period;		// 타이머 주기 설정 (usec 단위)

	// CPU Timer0 을 1초 주기로 설정
	ConfigCpuTimer(&CpuTimer1, Cpu_Clk, Timer_Prd);

	StartCpuTimer1();
	IER |= M_INT13; // CPU 인터럽트(INT13) 활성화



}

void AcgTIMER2_Setting(long period)
{

	if(TimerInitCheck == 0)   //Timer_Setting이 되었는지 체크하여 안되었으면 실행 (한 번만 실행)
	{
		AcgTIMER_Setting();
		TimerInitCheck = 1;
	}

	//interrupt vector remapping
	EALLOW;
	PieVectTable.TINT2 = &AcgTIMER2_ISR;
	EDIS;

	float Cpu_Clk = SystemClock;				// 현재 시스템 클럭을 설정 (MHz 단위)
	float Timer_Prd = (float)period;		// 타이머 주기 설정 (usec 단위)

	// CPU Timer0 을 1초 주기로 설정
	ConfigCpuTimer(&CpuTimer2, Cpu_Clk, Timer_Prd);

	StartCpuTimer2();
	IER |= M_INT14; // CPU 인터럽트(INT14) 활성화


}

void AcgTIMER_Setting()
{
	InitCpuTimers();
}




//============================================================================================
//	인터럽트 서비스 루틴 정의
//--------------------------------------------------------------------------------------------
interrupt void AcgTIMER0_ISR(void)
{
	TIMER_00_interrupt();
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;	// Acknowledge interrupt to PIE
}
//============================================================================================
interrupt void AcgTIMER1_ISR(void)
{

	TIMER_01_interrupt();
}

interrupt void AcgTIMER2_ISR(void)
{
	TIMER_02_interrupt();

}



