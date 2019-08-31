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
	InitI2CGpio();							// GPIO를 I2C 통신 용으로 설정

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

	// PIE의 ADC 인터럽트 활성화
	PieCtrlRegs.PIEIER8.bit.INTx1 = 1;				// PIE 인터럽트(I2CINT1A) 활성화
	IER |= M_INT8; 									// CPU 인터럽트(INT8)  활성화
	//============================================================================================

}



