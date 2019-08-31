#ifndef QEP_H
#define QEP_H

#include "DSP28x_Project.h"

//	Pin Map for QEP
//
//	QEP1A : Pin 64 (GPIO_20)
//	QEP1B : Pin 65 (GPIO_21)
//	QEP1S : Pin 66 (GPIO_22)
//	QEP1I : Pin 67 (GPIO_23)
//
//	QEP2A : Pin 68 (GPIO_24)
//	QEP2B : Pin 69 (GPIO_25)
//	QEP2S : Pin 73 (GPIO_27)
//	QEP2I : Pin 72 (GPIO_26)
//
//	dsp�� �ִ� 4����� �����ϴ�


// max���� ���ڴ��� ī������ �ִ밪  max val : 2^32 - 1
void AcgENC1_Setting(Uint32 max);
void AcgENC2_Setting(Uint32 max);

// ���ڴ� ��� �Լ�
Uint32 AcgENC1(void);
Uint32 AcgENC2(void);


interrupt void AcgENC1_ISR(void);
interrupt void AcgENC2_ISR(void);

#endif
