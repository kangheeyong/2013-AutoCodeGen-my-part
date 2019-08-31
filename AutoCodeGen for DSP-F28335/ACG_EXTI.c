#include "ACG_EXTI.h"


void AcgEXTI_Setting(EXTIChannel ch, TriggerType trigger, Uint32 pin)
{

	//  pin0 ~ pin31 (EXTI_01 ~ EXTI_02)
	if(ch == EXTI_01 || ch == EXTI_02)
	{
		AcgEXTI_GpaSetting(ch,trigger,pin);
	}


	//  pin32 ~ pin63 (EXTI_03 ~ EXTI_07)
	else
	{
		AcgEXTI_GpbSetting(ch,trigger,pin);
	}

}



void AcgEXTI_GpaSetting(EXTIChannel ch, TriggerType trigger,  Uint32 pin)
{


		// Vector Remapping
		EALLOW;
		if(ch == EXTI_01)PieVectTable.XINT1 = &AcgEXTI1_ISR;
		else if(ch == EXTI_02)PieVectTable.XINT2 = &AcgEXTI2_ISR;
		EDIS;
	//============================================================================================


	//============================================================================================
	// Step 4. GPIO 초기화
	//--------------------------------------------------------------------------------------------
		EALLOW;
		if(pin < 16){
			GpioCtrlRegs.GPAMUX1.all &= (~(0x00000011<<(2*pin)));
		}
		else GpioCtrlRegs.GPAMUX2.all &= (~(0x00000011<<(2*(pin - 16))));

		GpioCtrlRegs.GPADIR.all &= (~(0x00000001<<pin));

		EDIS;
	//============================================================================================

	//============================================================================================
	// Step 5. XINT 초기화
	//--------------------------------------------------------------------------------------------
		EALLOW;
		if(ch == EXTI_01){
			GpioIntRegs.GPIOXINT1SEL.bit.GPIOSEL = (Uint16)pin; // 외부 인터럽트 XINT1로 사용할 핀 선택
			XIntruptRegs.XINT1CR.bit.POLARITY = (Uint16)trigger; // XINT1 인터럽트 발생 조건 설정
			XIntruptRegs.XINT1CR.bit.ENABLE = 1;        // XINT1 인터럽트
			PieCtrlRegs.PIEIER1.bit.INTx4 = 1;   // PIE 인터럽트(XINT1)

		}

		else if(ch==EXTI_02){
			GpioIntRegs.GPIOXINT2SEL.bit.GPIOSEL = (Uint16)pin; // 외부 인터럽트 XINT2로 사용할 핀 선택
			XIntruptRegs.XINT2CR.bit.POLARITY = (Uint16)trigger; // XINT2 인터럽트 발생 조건 설정
			XIntruptRegs.XINT2CR.bit.ENABLE = 1;        // XINT2 인터럽트
			PieCtrlRegs.PIEIER1.bit.INTx5 = 1;   // PIE 인터럽트(XINT2)
		}

		IER |= M_INT1;							// CPU 인터럽트(INT1) : Enable


}

void AcgEXTI_GpbSetting(EXTIChannel ch, TriggerType trigger,  Uint32 pin)
{

			// Vector Remapping
			EALLOW;
			if(ch == EXTI_03)PieVectTable.XINT3 = &AcgEXTI3_ISR;
			else if(ch == EXTI_04)PieVectTable.XINT4 = &AcgEXTI4_ISR;
			else if(ch == EXTI_05)PieVectTable.XINT5 = &AcgEXTI5_ISR;
			else if(ch == EXTI_06)PieVectTable.XINT6 = &AcgEXTI6_ISR;
			else if(ch == EXTI_07)PieVectTable.XINT7 = &AcgEXTI7_ISR;
			EDIS;
		//============================================================================================


		//============================================================================================
		// Step 4. GPIO 초기화
		//--------------------------------------------------------------------------------------------
			EALLOW;
			if(pin < 16){
				GpioCtrlRegs.GPBMUX1.all &= (~(0x00000011<<(2*pin)));
			}
			else GpioCtrlRegs.GPBMUX2.all &= (~(0x00000011<<(2*(pin - 16))));

			GpioCtrlRegs.GPBDIR.all &= (~(0x00000001<<pin));

			EDIS;
		//============================================================================================

		//============================================================================================
			// Step 5. XINT 초기화
			//--------------------------------------------------------------------------------------------
				EALLOW;
				if(ch == EXTI_03)
				{
					GpioIntRegs.GPIOXINT3SEL.bit.GPIOSEL = pin; // 외부 인터럽트 XINT3 로 사용할 핀 선택
					XIntruptRegs.XINT3CR.bit.POLARITY = trigger; // XINT3 인터럽트 발생 조건 설정
					XIntruptRegs.XINT3CR.bit.ENABLE = 1;        // XINT3 인터럽트
					PieCtrlRegs.PIEIER12.bit.INTx1 = 1;   // PIE 인터럽트(XINT3)
				}

				else if(ch == EXTI_04)
				{
					GpioIntRegs.GPIOXINT4SEL.bit.GPIOSEL = pin; // 외부 인터럽트 XINT4로 사용할 핀 선택
					XIntruptRegs.XINT4CR.bit.POLARITY = trigger; // XINT4 인터럽트 발생 조건 설정
					XIntruptRegs.XINT4CR.bit.ENABLE = 1;        // XINT4 인터럽트
					PieCtrlRegs.PIEIER12.bit.INTx2 = 1;   // PIE 인터럽트(XINT4)
				}

				else if(ch == EXTI_05)
				{
					GpioIntRegs.GPIOXINT5SEL.bit.GPIOSEL = pin; // 외부 인터럽트 XINT5로 사용할 핀 선택
					XIntruptRegs.XINT5CR.bit.POLARITY = trigger; // XINT5 인터럽트 발생 조건 설정
					XIntruptRegs.XINT5CR.bit.ENABLE = 1;        // XINT5 인터럽트
					PieCtrlRegs.PIEIER12.bit.INTx3 = 1;   // PIE 인터럽트(XINT5)
				}

				else if(ch == EXTI_06)
				{
					GpioIntRegs.GPIOXINT6SEL.bit.GPIOSEL = pin; // 외부 인터럽트 XINT6로 사용할 핀 선택
					XIntruptRegs.XINT6CR.bit.POLARITY = trigger; // XINT6 인터럽트 발생 조건 설정
					XIntruptRegs.XINT6CR.bit.ENABLE = 1;        // XINT6 인터럽트
					PieCtrlRegs.PIEIER12.bit.INTx4 = 1;   // PIE 인터럽트(XINT6)
				}

				else if(ch == EXTI_07)
				{
					GpioIntRegs.GPIOXINT7SEL.bit.GPIOSEL = pin; // 외부 인터럽트 XINT7로 사용할 핀 선택
					XIntruptRegs.XINT7CR.bit.POLARITY = trigger; // XINT7 인터럽트 발생 조건 설정
					XIntruptRegs.XINT7CR.bit.ENABLE = 1;        // XINT7 인터럽트
					PieCtrlRegs.PIEIER12.bit.INTx5 = 1;   // PIE 인터럽트(XINT7)
				}
				IER |= M_INT12;							// CPU 인터럽트(INT1) : Enable

}


interrupt void AcgEXTI1_ISR(void)
{
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;

	EXTI_01_interrupt();
}
interrupt void AcgEXTI2_ISR(void)
{
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;

	EXTI_02_interrupt();
}
interrupt void AcgEXTI3_ISR(void)
{

	PieCtrlRegs.PIEACK.all = PIEACK_GROUP12;
	EXTI_03_interrupt();
}
interrupt void AcgEXTI4_ISR(void)
{

	PieCtrlRegs.PIEACK.all = PIEACK_GROUP12;

	EXTI_04_interrupt();
}
interrupt void AcgEXTI5_ISR(void)
{

	PieCtrlRegs.PIEACK.all = PIEACK_GROUP12;

	EXTI_05_interrupt();
}
interrupt void AcgEXTI6_ISR(void)
{

	PieCtrlRegs.PIEACK.all = PIEACK_GROUP12;

	EXTI_06_interrupt();
}
interrupt void AcgEXTI7_ISR(void)
{

	PieCtrlRegs.PIEACK.all = PIEACK_GROUP12;

	EXTI_07_interrupt();
}


