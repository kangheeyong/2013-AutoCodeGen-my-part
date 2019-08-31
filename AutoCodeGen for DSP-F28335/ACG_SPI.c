/*
 * ACG_SPI.c
 *
 *  Created on: 2013. 7. 26.
 *      Author: RODONGWAN
 */

#include "ACG_SPI.h"
#include "DSP28x_Project.h"
//SPI Master �ʱ�ȭ
void AcgSPI_Setting(SerialClock clock, SPIMode spiMode, CharLength charLength)
{
	InitSpiaGpio();

	// SPI �ֿ伳��
	SpiaRegs.SPICCR.bit.SPISWRESET=0;		// SPI ����Ʈ���� ����

	SpiaRegs.SPICCR.bit.SPICHAR = charLength;		// SPI �ۼ��� Charcter-length ���� : 16bit
	SpiaRegs.SPICTL.bit.MASTER_SLAVE = 1;	// SPI Master/Slave ���� : Master ���
	SpiaRegs.SPICTL.bit.TALK = 1; 			// SPI Master/Slave ��� Enable
	SpiaRegs.SPIBRR = clock;					// SPI ��żӵ� ����: 37.5MHz/(SPIBRR+1) = 1.5MHz

	SpiaRegs.SPICCR.bit.SPISWRESET=1;		// SPI ����Ʈ���� ���� ����
}


void AcgSPI_ModeSetting(SPIMode spiMode)
{
	if(spiMode ==0)
	{
		SpiaRegs.SPICCR.bit.CLKPOLARITY = 0;
		SpiaRegs.SPICTL.bit.CLK_PHASE =0;
	}

	else if(spiMode == 1)
	{
		SpiaRegs.SPICCR.bit.CLKPOLARITY = 0;
		SpiaRegs.SPICTL.bit.CLK_PHASE =1;
	}

	else if(spiMode == 2)
	{
		SpiaRegs.SPICCR.bit.CLKPOLARITY = 1;
		SpiaRegs.SPICTL.bit.CLK_PHASE =0;
	}

	else
	{
		SpiaRegs.SPICCR.bit.CLKPOLARITY = 1;
		SpiaRegs.SPICTL.bit.CLK_PHASE =1;
	}
}



