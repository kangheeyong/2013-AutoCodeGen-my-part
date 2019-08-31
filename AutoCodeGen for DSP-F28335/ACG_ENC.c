#include "ACG_ENC.h"



Uint32	UTimeOutPositionLatch[2];
Uint32	PastUTimeOutPositionLatch[2];
Uint32	Displacement[2];

interrupt void UnitEQEP1_Isr(void)
{

	/* Backup Past Position Latch Value */
	PastUTimeOutPositionLatch[0] = UTimeOutPositionLatch[0];

	/* Check Current Position Latch on Unit Time Out Event */
	UTimeOutPositionLatch[0] = EQep1Regs.QPOSLAT;

	/* Calculate Position Displacement & Speed in RPM */
	if((EQep1Regs.QFLG.bit.PCO || EQep1Regs.QFLG.bit.PCU))
	{
		/* Position Counter overflowed or underflowed, hence do no compute displacement */
		EQep1Regs.QCLR.bit.PCO = 1;
		EQep1Regs.QCLR.bit.PCU = 1;
	}
	else
	{
		Displacement[1] = UTimeOutPositionLatch[1] - PastUTimeOutPositionLatch[1];
	}

	EQep1Regs.QCLR.bit.UTO = 1;
	EQep1Regs.QCLR.bit.INT = 1;
	PieCtrlRegs.PIEACK.bit.ACK5 = 1;
}

interrupt void UnitEQEP2_Isr(void)
{

	/* Backup Past Position Latch Value */
	PastUTimeOutPositionLatch[1] = UTimeOutPositionLatch[1];

	/* Check Current Position Latch on Unit Time Out Event */
	UTimeOutPositionLatch[1] = EQep2Regs.QPOSLAT;

	/* Calculate Position Displacement & Speed in RPM */
	if((EQep2Regs.QFLG.bit.PCO || EQep2Regs.QFLG.bit.PCU))
	{
		/* Position Counter overflowed or underflowed, hence do no compute displacement */
		EQep2Regs.QCLR.bit.PCO = 1;
		EQep2Regs.QCLR.bit.PCU = 1;
	}
	else
	{
		Displacement[1] = UTimeOutPositionLatch[1] - PastUTimeOutPositionLatch[1];
	}

	EQep2Regs.QCLR.bit.UTO = 1;
	EQep2Regs.QCLR.bit.INT = 1;
	PieCtrlRegs.PIEACK.bit.ACK5 = 1;
}


void AcgENC1_Setting(Uint32 max)
{


	/* Interrupt Service Routine Re-mapping */
	EALLOW;
	PieVectTable.EQEP1_INT = &UnitEQEP1_Isr;
	EDIS;

	/* Enable PIE group 5 interrupt 1 for EQEP2_INT */
	PieCtrlRegs.PIEIER5.bit.INTx1 = 1;

	/* Enable CPU INT5 for EQEP2_INT */
	IER |= M_INT5;

	/* for Qep */
	InitEQep1Gpio();
	//-----------------------------------------------------------------------------

	EQep1Regs.QUPRD = 150E6/2;	/* Unit Timer for 2Hz at 150 MHz SYSCLKOUT */

	EQep1Regs.QDECCTL.bit.QSRC = 0;			/* Quadrature count mode */
	EQep1Regs.QEPCTL.bit.FREE_SOFT = 2;
	EQep1Regs.QEPCTL.bit.UTE = 1; 			/* Unit Timer Enable */
	EQep1Regs.QEPCTL.bit.QCLM = 1; 			/* Position counter latch on unit time out */
	EQep1Regs.QEPCTL.bit.PCRM = 1;			/* Position Counter Reset on Maximum Position */
	EQep1Regs.QPOSMAX = max;
	EQep1Regs.QEPCTL.bit.QPEN = 1; 			/* QEP enable */
	EQep1Regs.QEINT.bit.UTO = 1;			/* Unit Time Out Interrupt Enable */
}

Uint32 AcgENC1(void)
{
	return EQep1Regs.QPOSCNT;
}

void AcgENC2_Setting(Uint32 max)
{


	/* Interrupt Service Routine Re-mapping */
	EALLOW;
	PieVectTable.EQEP2_INT = &UnitEQEP2_Isr;
	EDIS;

	/* Enable PIE group 5 interrupt 1 for EQEP2_INT */
	PieCtrlRegs.PIEIER5.bit.INTx2 = 1;

	/* Enable CPU INT5 for EQEP2_INT */
	IER |= M_INT5;

	/* for Qep */
	InitEQep2Gpio();
	//-----------------------------------------------------------------------------

	EQep2Regs.QUPRD = 150E6/2;	/* Unit Timer for 2Hz at 150 MHz SYSCLKOUT */

	EQep2Regs.QDECCTL.bit.QSRC = 0;			/* Quadrature count mode */
	EQep2Regs.QEPCTL.bit.FREE_SOFT = 2;
	EQep2Regs.QEPCTL.bit.UTE = 1; 			/* Unit Timer Enable */
	EQep2Regs.QEPCTL.bit.QCLM = 1; 			/* Position counter latch on unit time out */
	EQep2Regs.QEPCTL.bit.PCRM = 1;			/* Position Counter Reset on Maximum Position */
	EQep2Regs.QPOSMAX = max;	/* 24 pulse @ 1 revolution */
	EQep2Regs.QEPCTL.bit.QPEN = 1; 			/* QEP enable */
	EQep2Regs.QEINT.bit.UTO = 1;			/* Unit Time Out Interrupt Enable */
}

Uint32 AcgENC2(void)
{
	return EQep2Regs.QPOSCNT;
}

