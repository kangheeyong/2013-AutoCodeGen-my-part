#include "ACG_ADC.h"



void AcgADC_Setting()
{
	EALLOW;
	SysCtrlRegs.HISPCP.bit.HSPCLK = 1;  			// HSPCLK = SYSCLKOUT/(HISPCP*2)
	EDIS;											// HSPCLK = 150MHz/(1*2) = 75MHz

	InitAdc();

	// ADC 설정
	AdcRegs.ADCTRL3.bit.ADCCLKPS = 3;	   		// ADCCLK = HSPCLK/(ADCCLKPS*2)/(CPS+1)
	AdcRegs.ADCTRL1.bit.CPS = 1;				// ADCCLK = 75MHz/(3*2)/(1+1) = 6.25MHz
	AdcRegs.ADCTRL1.bit.ACQ_PS = 3;				// 샘플/홀드 사이클 = ACQ_PS + 1 = 4 (ADCCLK기준)
	AdcRegs.ADCTRL1.bit.SEQ_CASC = 1;			// 시퀀스 모드 설정: 직렬 시퀀스 모드 (0:병렬 모드, 1:직렬 모드)
}


Uint16 AcgADC(ADCChannel ch)
{

	AdcRegs.ADCMAXCONV.bit.MAX_CONV1 = 0;   	// ADC 채널수 설정: 1개(=MAX_CONV+1)채널을 ADC
	AdcRegs.ADCCHSELSEQ1.bit.CONV00 = ch; 		// ADC 순서 설정: 첫번째로 ADCINA0 채널을 ADC
	AdcRegs.ADCTRL2.bit.SOC_SEQ1 = 1;					// ADC 시퀀스 시작
	DELAY_US(1.72L);									// ADC 시퀀스 변환시간(약1.72usec)만큼 지연

	AdcRegs.ADCTRL2.bit.RST_SEQ1 = 1;					// ADC 시퀀서 리셋
	DELAY_US(0.64L);									// ADC 시퀀서 리셋시간(약0.64usec)만큼 지연

	return AdcRegs.ADCRESULT0;
}
