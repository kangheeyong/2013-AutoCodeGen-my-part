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

	if(TimerInitCheck == 0)  //Timer_Setting�� �Ǿ����� üũ�Ͽ� �ȵǾ����� ���� (�� ���� ����)
	{
		AcgTIMER_Setting();
		TimerInitCheck = 1;
	}

	//interrupt vector remapping
	EALLOW;
    PieVectTable.TINT0 = &AcgTIMER0_ISR;
	EDIS;


	float Cpu_Clk = SystemClock;				// ���� �ý��� Ŭ���� ���� (MHz ����)
	float Timer_Prd = (float)period;		// Ÿ�̸� �ֱ� ���� (usec ����)

	// CPU Timer0 �� 1�� �ֱ�� ����
	ConfigCpuTimer(&CpuTimer0, Cpu_Clk, Timer_Prd);

	StartCpuTimer0();

	// CPU Timer0 ���ͷ�Ʈ Ȱ��ȭ
	PieCtrlRegs.PIEIER1.bit.INTx7 = 1;			// PIE ���ͷ�Ʈ(TINT0) Ȱ��ȭ
	IER |= M_INT1; 								// CPU ���ͷ�Ʈ(INT1)  Ȱ��ȭ


}

void AcgTIMER1_Setting(long period)
{

	if(TimerInitCheck == 0)   //Timer_Setting�� �Ǿ����� üũ�Ͽ� �ȵǾ����� ���� (�� ���� ����)
	{
		AcgTIMER_Setting();
		TimerInitCheck = 1;
	}

	//interrupt vector remapping
	EALLOW;
	PieVectTable.XINT13 = &AcgTIMER1_ISR;
	EDIS;

	float Cpu_Clk = SystemClock;				// ���� �ý��� Ŭ���� ���� (MHz ����)
	float Timer_Prd = (float)period;		// Ÿ�̸� �ֱ� ���� (usec ����)

	// CPU Timer0 �� 1�� �ֱ�� ����
	ConfigCpuTimer(&CpuTimer1, Cpu_Clk, Timer_Prd);

	StartCpuTimer1();
	IER |= M_INT13; // CPU ���ͷ�Ʈ(INT13) Ȱ��ȭ



}

void AcgTIMER2_Setting(long period)
{

	if(TimerInitCheck == 0)   //Timer_Setting�� �Ǿ����� üũ�Ͽ� �ȵǾ����� ���� (�� ���� ����)
	{
		AcgTIMER_Setting();
		TimerInitCheck = 1;
	}

	//interrupt vector remapping
	EALLOW;
	PieVectTable.TINT2 = &AcgTIMER2_ISR;
	EDIS;

	float Cpu_Clk = SystemClock;				// ���� �ý��� Ŭ���� ���� (MHz ����)
	float Timer_Prd = (float)period;		// Ÿ�̸� �ֱ� ���� (usec ����)

	// CPU Timer0 �� 1�� �ֱ�� ����
	ConfigCpuTimer(&CpuTimer2, Cpu_Clk, Timer_Prd);

	StartCpuTimer2();
	IER |= M_INT14; // CPU ���ͷ�Ʈ(INT14) Ȱ��ȭ


}

void AcgTIMER_Setting()
{
	InitCpuTimers();
}




//============================================================================================
//	���ͷ�Ʈ ���� ��ƾ ����
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



