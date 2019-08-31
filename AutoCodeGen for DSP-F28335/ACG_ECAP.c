/*
 * ACG_ECAP.c
 *
 *  Created on: 2013. 7. 28.
 *      Author: RODONGWAN
 */

#include "ACG_ECAP.h"

static Uint32 Period[6] = {0};

//Ecap APWM 초기화
void AcgECAP1_Setting(Uint32 period)
{
	Period[0] = period;

	//GPIO 핀을 Ecap으로 사용하도록 설정
	AcgECAP_GpioSetting(ECAP_01);

	//Interrupt Service Routine Re-mapping
	EALLOW;
	PieVectTable.ECAP1_INT = &AcgECAP1_ISR;
	EDIS;

	/* Enable PIE group 4 interrupt 1 for ECAP1_INT */
    PieCtrlRegs.PIEIER4.all = M_INT1;

	/* Enable CPU INT4 for ECAP1_INT */
	IER |= M_INT4;

}

void AcgECAP1(int dutycycle)
{
	//Ecap Register Setting
	AcgECAP_RgSetting(ECAP_01, Period[0],dutycycle);

}

void AcgECAP2_Setting(Uint32 period)
{
	Period[1] = period;

	//GPIO 핀을 Ecap으로 사용하도록 설정
	AcgECAP_GpioSetting(ECAP_02);

	//Interrupt Service Routine Re-mapping
	EALLOW;
	PieVectTable.ECAP2_INT = &AcgECAP2_ISR;
	EDIS;

	/* Enable PIE group 4 interrupt 2 for ECAP2_INT */
    PieCtrlRegs.PIEIER4.all = M_INT2;

	/* Enable CPU INT4 for ECAP2_INT */
	IER |= M_INT4;

}

void AcgECAP2(int dutycycle)
{
	//Ecap Register Setting
	AcgECAP_RgSetting(ECAP_02, Period[1],dutycycle);

}

void AcgECAP3_Setting(Uint32 period)
{
	Period[2] = period;

	//GPIO 핀을 Ecap으로 사용하도록 설정
	AcgECAP_GpioSetting(ECAP_03);

	//Interrupt Service Routine Re-mapping
	EALLOW;
	PieVectTable.ECAP3_INT = &AcgECAP3_ISR;
	EDIS;

	/* Enable PIE group 4 interrupt 3 for ECAP3_INT */
    PieCtrlRegs.PIEIER4.all = M_INT3;

	/* Enable CPU INT4 for ECAP3_INT */
	IER |= M_INT4;

}

void AcgECAP3(int dutycycle)
{
	//Ecap Register Setting
	AcgECAP_RgSetting(ECAP_03, Period[2],dutycycle);

}

void AcgECAP4_Setting(Uint32 period)
{
	Period[3] = period;

	//GPIO 핀을 Ecap으로 사용하도록 설정
	AcgECAP_GpioSetting(ECAP_04);


	//Interrupt Service Routine Re-mapping
	EALLOW;
	PieVectTable.ECAP4_INT = &AcgECAP4_ISR;
	EDIS;

	/* Enable PIE group 4 interrupt 4 for ECAP4_INT */
    PieCtrlRegs.PIEIER4.all = M_INT4;

	/* Enable CPU INT4 for ECAP4_INT */
	IER |= M_INT4;

}

void AcgECAP4(int dutycycle)
{
	//Ecap Register Setting
	AcgECAP_RgSetting(ECAP_04, Period[3],dutycycle);

}


void AcgECAP5_Setting(Uint32 period)
{
	Period[4] = period;

	//GPIO 핀을 Ecap으로 사용하도록 설정
	AcgECAP_GpioSetting(ECAP_05);

	//Interrupt Service Routine Re-mapping
	EALLOW;
	PieVectTable.ECAP5_INT = &AcgECAP5_ISR;
	EDIS;

	/* Enable PIE group 4 interrupt 5 for ECAP5_INT */
    PieCtrlRegs.PIEIER4.all = M_INT5;

	/* Enable CPU INT4 for ECAP5_INT */
	IER |= M_INT4;

}

void AcgECAP5(int dutycycle)
{
	//Ecap Register Setting
	AcgECAP_RgSetting(ECAP_05, Period[4],dutycycle);

}


void AcgECAP6_Setting(Uint32 period)
{
	Period[5] = period;

	//GPIO 핀을 Ecap으로 사용하도록 설정
	AcgECAP_GpioSetting(ECAP_06);


	//Interrupt Service Routine Re-mapping
	EALLOW;
	PieVectTable.ECAP6_INT = &AcgECAP6_ISR;
	EDIS;

	/* Enable PIE group 4 interrupt 6 for ECAP6_INT */
    PieCtrlRegs.PIEIER4.all = M_INT6;

	/* Enable CPU INT4 for ECAP6_INT */
	IER |= M_INT4;

}

void AcgECAP6(int dutycycle)
{
	//Ecap Register Setting
	AcgECAP_RgSetting(ECAP_06, Period[5],dutycycle);

}


//내부 함수
void AcgECAP_GpioSetting(ECAPChannel ch)
{
	//GPIO핀을 ECAP으로 사용하도록 설정
	EALLOW;

	// GPIO 34 : Ecap1
	if(ch == ECAP_01)
	{

		GpioCtrlRegs.GPBPUD.bit.GPIO34   = 0;	/* Enable pull-up on GPI34 (CAP1) */
		GpioCtrlRegs.GPBQSEL1.bit.GPIO34 = 0;	/* Synch to SYSCLKOUT GPI34 (CAP1) */
		GpioCtrlRegs.GPBMUX1.bit.GPIO34  = 1;	/* Configure GPI34 as CAP1 */

	}

	// GPIO 37 : Ecap2
	else if(ch == ECAP_02)
	{

		GpioCtrlRegs.GPBPUD.bit.GPIO37   = 0;	/* Enable pull-up on GPI37 (CAP2) */
		GpioCtrlRegs.GPBQSEL1.bit.GPIO37 = 0;	/* Synch to SYSCLKOUT GPI37 (CAP2) */
		GpioCtrlRegs.GPBMUX1.bit.GPIO37  = 1;	/* Configure GPI37 as CAP2 */
	}

	// GPIO 26 : Ecap3
	else if(ch == ECAP_03)
	{

		GpioCtrlRegs.GPAPUD.bit.GPIO26   = 0;	/* Enable pull-up on GPI26 (CAP3) */
		GpioCtrlRegs.GPAQSEL2.bit.GPIO26 = 0;	/* Synch to SYSCLKOUT GPI26 (CAP3) */
		GpioCtrlRegs.GPAMUX2.bit.GPIO26  = 1;	/* Configure GPI26 as CAP3 */
	}

	// GPIO 27 : Ecap4
	else if(ch == ECAP_04)
	{

		GpioCtrlRegs.GPAPUD.bit.GPIO27   = 0;	/* Enable pull-up on GPI27 (CAP4) */
		GpioCtrlRegs.GPAQSEL2.bit.GPIO27 = 0;	/* Synch to SYSCLKOUT GPI27 (CAP4) */
		GpioCtrlRegs.GPAMUX2.bit.GPIO27  = 1;	/* Configure GPI27 as CAP4 */
	}

	// GPIO 48 : Ecap5
	else if(ch == ECAP_05)
	{

		GpioCtrlRegs.GPBPUD.bit.GPIO34   = 0;	/* Enable pull-up on GPI48 (CAP5) */
		GpioCtrlRegs.GPBQSEL1.bit.GPIO34 = 0;	/* Synch to SYSCLKOUT GPI48 (CAP5) */
		GpioCtrlRegs.GPBMUX1.bit.GPIO34  = 1;	/* Configure GPI48 as CAP5 */
	}

	// GPIO 49 : Ecap6
	else
	{
		GpioCtrlRegs.GPBPUD.bit.GPIO34   = 0;	/* Enable pull-up on GPI49 (CAP6) */
		GpioCtrlRegs.GPBQSEL1.bit.GPIO34 = 0;	/* Synch to SYSCLKOUT GPI49 (CAP6) */
		GpioCtrlRegs.GPBMUX1.bit.GPIO34  = 1;	/* Configure GPI49 as CAP6 */
	}



    //Initialize Peripheral Interrupt Expansion circuit
   	InitPieCtrl();


    //Pie Vector Table Re-allocation
    InitPieVectTable();




	EDIS;
}

void AcgECAP_RgSetting(ECAPChannel ch,Uint32 period,Uint32 dutycycle)
{
	volatile struct ECAP_REGS *EcapPtr;
	double EcapPeriod = (double) ((double)period/1000000.);  // us 단위 -> sec 단위로 변환
	Uint32 EcapSysClock = SystemClock * 1000000; // MHz -> Hz 단위로 변환
	Uint64 temp = 0;

	if(ch == ECAP_01)
		EcapPtr = &ECap1Regs;

	else if(ch == ECAP_02)
		EcapPtr = &ECap2Regs;

	else if(ch == ECAP_03)
		EcapPtr = &ECap3Regs;

	else if(ch == ECAP_04)
		EcapPtr = &ECap4Regs;

	else if(ch == ECAP_05)
		EcapPtr = &ECap5Regs;

	else if(ch == ECAP_06)
		EcapPtr = &ECap6Regs;

	/* Configure peripheral registers */
	EcapPtr->ECCTL2.bit.CAP_APWM = 1;		/* Enable APWM mode */
	EcapPtr->ECCTL2.bit.APWMPOL = 0;		/* APWM output polarity select (Active High)*/


	/*        Set Period       */
	// Period = CAP1 / SystemClock
	//  CAP1 = Period (us) * SystemClock (Hz)
	EcapPtr->CAP1 = (Uint32) (EcapPeriod * EcapSysClock);

	/* Set Compare value (duty setting)  */
	// duty = (CAP2 / SystemClock) / period * 100
	// CAP2 = (duty / 100) * period (us) * SystemClock(Hz)

	temp = (Uint64)dutycycle  * EcapPeriod * EcapSysClock;
	EcapPtr->CAP2 = (Uint32)(temp/100);


	EcapPtr->ECCLR.all = 0x0FF;			/* Clear pending interrupts */
	EcapPtr->ECEINT.bit.CTR_EQ_PRD = 1;	/* Enable Period Equal Int */

	EcapPtr->ECCTL2.bit.TSCTRSTOP = 1;		/* Start Counter */


}

//Ecap APWM Interrupt 함수
interrupt void AcgECAP1_ISR(void)
{
	/* eCapture 1 Interrupt clear */
    ECap1Regs.ECCLR.bit.CTR_EQ_PRD = 1;
    ECap1Regs.ECCLR.bit.INT = 1;

	/* Acknowledge this interrupt to receive more interrupts from group 4 */
	PieCtrlRegs.PIEACK.bit.ACK4 = 1;

	ECAP_01_interrupt();
}

interrupt void AcgECAP2_ISR(void)
{
	/* eCapture 2 Interrupt clear */
    ECap5Regs.ECCLR.bit.CTR_EQ_PRD = 1;
    ECap5Regs.ECCLR.bit.INT = 1;

	/* Acknowledge this interrupt to receive more interrupts from group 4 */
	PieCtrlRegs.PIEACK.bit.ACK4 = 1;

	ECAP_02_interrupt();
}

interrupt void AcgECAP3_ISR(void)
{
	/* eCapture 3 Interrupt clear */
    ECap5Regs.ECCLR.bit.CTR_EQ_PRD = 1;
    ECap5Regs.ECCLR.bit.INT = 1;

	/* Acknowledge this interrupt to receive more interrupts from group 4 */
	PieCtrlRegs.PIEACK.bit.ACK4 = 1;

	ECAP_03_interrupt();
}

interrupt void AcgECAP4_ISR(void)
{
	/* eCapture 4 Interrupt clear */
    ECap5Regs.ECCLR.bit.CTR_EQ_PRD = 1;
    ECap5Regs.ECCLR.bit.INT = 1;

	/* Acknowledge this interrupt to receive more interrupts from group 4 */
	PieCtrlRegs.PIEACK.bit.ACK4 = 1;

	ECAP_04_interrupt();
}

interrupt void AcgECAP5_ISR(void)
{
	/* eCapture 5 Interrupt clear */
    ECap5Regs.ECCLR.bit.CTR_EQ_PRD = 1;
    ECap5Regs.ECCLR.bit.INT = 1;

	/* Acknowledge this interrupt to receive more interrupts from group 4 */
	PieCtrlRegs.PIEACK.bit.ACK4 = 1;

	ECAP_05_interrupt();
}

interrupt void AcgECAP6_ISR(void)
{
	/* eCapture 6 Interrupt clear */
    ECap6Regs.ECCLR.bit.CTR_EQ_PRD = 1;
    ECap6Regs.ECCLR.bit.INT = 1;

	/* Acknowledge this interrupt to receive more interrupts from group 4 */
	PieCtrlRegs.PIEACK.bit.ACK4 = 1;

	ECAP_06_interrupt();

}
