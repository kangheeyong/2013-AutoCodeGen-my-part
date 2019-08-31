#include "ACG_ADC.h"



void AcgADC_Setting()
{
	EALLOW;
	SysCtrlRegs.HISPCP.bit.HSPCLK = 1;  			// HSPCLK = SYSCLKOUT/(HISPCP*2)
	EDIS;											// HSPCLK = 150MHz/(1*2) = 75MHz

	InitAdc();

	// ADC ����
	AdcRegs.ADCTRL3.bit.ADCCLKPS = 3;	   		// ADCCLK = HSPCLK/(ADCCLKPS*2)/(CPS+1)
	AdcRegs.ADCTRL1.bit.CPS = 1;				// ADCCLK = 75MHz/(3*2)/(1+1) = 6.25MHz
	AdcRegs.ADCTRL1.bit.ACQ_PS = 3;				// ����/Ȧ�� ����Ŭ = ACQ_PS + 1 = 4 (ADCCLK����)
	AdcRegs.ADCTRL1.bit.SEQ_CASC = 1;			// ������ ��� ����: ���� ������ ��� (0:���� ���, 1:���� ���)
}


Uint16 AcgADC(ADCChannel ch)
{

	AdcRegs.ADCMAXCONV.bit.MAX_CONV1 = 0;   	// ADC ä�μ� ����: 1��(=MAX_CONV+1)ä���� ADC
	AdcRegs.ADCCHSELSEQ1.bit.CONV00 = ch; 		// ADC ���� ����: ù��°�� ADCINA0 ä���� ADC
	AdcRegs.ADCTRL2.bit.SOC_SEQ1 = 1;					// ADC ������ ����
	DELAY_US(1.72L);									// ADC ������ ��ȯ�ð�(��1.72usec)��ŭ ����

	AdcRegs.ADCTRL2.bit.RST_SEQ1 = 1;					// ADC ������ ����
	DELAY_US(0.64L);									// ADC ������ ���½ð�(��0.64usec)��ŭ ����

	return AdcRegs.ADCRESULT0;
}
