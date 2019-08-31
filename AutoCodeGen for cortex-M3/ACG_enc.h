#ifndef ACG_ENC_H
#define ACG_ENC_H

#include "ACG_datatype.h"

//  Pin Map for External Interrupt

//	ENC1 : PE9, PE11
//	ENC2 : PA0, PA1
//	ENC3 : PA6, PA7
//	ENC4 : PB6, PB7
//	ENC5 : PA0, PA1
//	ENC8 : PC6, PC7

// max에는 엔코더의 카운터의 최대값  max val : 65535
void AcgENC1_Setting(int max); 
void AcgENC2_Setting(int max); 
void AcgENC3_Setting(int max); 
void AcgENC4_Setting(int max); 
void AcgENC5_Setting(int max); 
void AcgENC8_Setting(int max); 

// 엔코더 사용 함수 
UINT16 AcgENC1();
UINT16 AcgENC2();
UINT16 AcgENC3();
UINT16 AcgENC4();
UINT16 AcgENC5();
UINT16 AcgENC8();

#endif
