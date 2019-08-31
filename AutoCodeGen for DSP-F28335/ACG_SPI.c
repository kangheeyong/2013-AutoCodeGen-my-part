/*
 * ACG_SPI.c
 *
 *  Created on: 2013. 7. 26.
 *      Author: RODONGWAN
 */

#include "ACG_SPI.h"
#include "DSP28x_Project.h"
//SPI Master 초기화
void AcgSPI_Setting(SerialClock clock, SPIMode spiMode, CharLength charLength)
{
	InitSpiaGpio();

	// SPI 주요설정
	SpiaRegs.SPICCR.bit.SPISWRESET=0;		// SPI 소프트웨어 리셋

	SpiaRegs.SPICCR.bit.SPICHAR = charLength;		// SPI 송수신 Charcter-length 설정 : 16bit
	SpiaRegs.SPICTL.bit.MASTER_SLAVE = 1;	// SPI Master/Slave 설정 : Master 모드
	SpiaRegs.SPICTL.bit.TALK = 1; 			// SPI Master/Slave 통신 Enable
	SpiaRegs.SPIBRR = clock;					// SPI 통신속도 설정: 37.5MHz/(SPIBRR+1) = 1.5MHz

	SpiaRegs.SPICCR.bit.SPISWRESET=1;		// SPI 소프트웨어 리셋 해제
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



