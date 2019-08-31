/*
 * ACG_I2C.c
 *
 *  Created on: 2013. 7. 18.
 *      Author: ssm
 */


#include "ACG_I2C.h"


void AcgI2C_Setting(BitRate bitRate)
{
	// Initialize I2-A PIN
	InitI2CGpio();							// GPIO�� I2C ��� ������ ����

	// Initialize internal I2C peripheral module
	I2caRegs.I2CMDR.bit.IRS = 0;

	if(bitRate == STANDARD) //100kbps
	{
		I2caRegs.I2CPSC.all = 9;				// Prescaler - need 7-12 Mhz on module clk
		I2caRegs.I2CCLKL = 100;					// NOTE: must be non zero
		I2caRegs.I2CCLKH = 40;					// NOTE: must be non zero
	}

	else if(bitRate == FAST) //400kbps
	{
		I2caRegs.I2CPSC.all = 4;				// Prescaler - need 7-12 Mhz on module clk
		I2caRegs.I2CCLKL = 40;					// NOTE: must be non zero
		I2caRegs.I2CCLKH = 25;					// NOTE: must be non zero
	}

	I2caRegs.I2COAR = 0x01;
	I2caRegs.I2CIER.bit.SCD = 1;			// Enable SCD interrupts
	I2caRegs.I2CFFTX.all = 0x6000;			// Enable FIFO mode and TXFIFO
	I2caRegs.I2CFFRX.all = 0x2040;			// Enable RXFIFO, clear RXFFINT,
	I2caRegs.I2CMDR.bit.IRS = 1;

	// PIE�� ADC ���ͷ�Ʈ Ȱ��ȭ
	PieCtrlRegs.PIEIER8.bit.INTx1 = 1;				// PIE ���ͷ�Ʈ(I2CINT1A) Ȱ��ȭ
	IER |= M_INT8; 									// CPU ���ͷ�Ʈ(INT8)  Ȱ��ȭ
	//============================================================================================

}



