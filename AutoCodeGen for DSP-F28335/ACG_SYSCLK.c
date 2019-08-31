/*
 * ACG_SYSCLK.c
 *
 *  Created on: 2013. 7. 26.
 *      Author: RODONGWAN
 */



#include "ACG_SYSCLK.h"

//SystemClock�� �����ϱ� ���� ����
//Timer���� ���δ�.
//ePwm���� ���δ�.
float SystemClock;

void AcgSystemClock_Setting(SysClk clk)
{

	//Disable Global Interrupt & Interrupt Flag Clear
	DINT;

	//Interrupt �ʱ�ȭ
   Interrupt_Init();

   // Disable the watchdog
   DisableDog();

   // Initialize the PLL control: PLLCR and DIVSEL
   // DSP28_PLLCR and DSP28_DIVSEL are defined in DSP2833x_Examples.h
   InitPll(clk,2); // (PLLCR,DIVSEL)

   // Initialize the peripheral clocks
   InitPeripheralClocks();


   //SystemClock�� ���� (Mhz ����)
   switch(clk)
   {
   case SYSCLK_15MHz:
	   SystemClock = 15;
	   break;
   case SYSCLK_30MHz:
	   SystemClock = 30;
	   break;
   case SYSCLK_45MHz:
	   SystemClock = 45;
	   break;
   case SYSCLK_60MHz:
	   SystemClock = 69;
	   break;
   case SYSCLK_75MHz:
	   SystemClock = 75;
	   break;
   case SYSCLK_90MHz:
	   SystemClock = 90;
	   break;
   case SYSCLK_105MHz:
	   SystemClock = 105;
	   break;
   case SYSCLK_120MHz:
	   SystemClock = 120;
	   break;
   case SYSCLK_135MHz:
	   SystemClock = 135;
	   break;
   case SYSCLK_150MHz:
	   SystemClock = 150;
	   break;
   }


}

//Enable Global interrupt
//��� �������� �ʱ�ȭ �� ����
void EnableGlobal_INT()
{
	ERTM;  // Enable Global realtime interrupt DBGM
	EINT;  // Enalbe Global interrupt INTM
}


//Interrupt �ʱ�ȭ
void Interrupt_Init()
{
	InitPieCtrl();
	IER = 0x0000;
	IFR = 0x0000;
	InitPieVectTable();
}


