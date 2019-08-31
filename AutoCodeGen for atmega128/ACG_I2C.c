#include "ACG_I2C.h"


//I2C 초기화 함수
void AcgI2C_Setting(BitRate bitRate)  //  parameter : 전송 속도 (FastMode or StandardMode)
{
    TWBR = bitRate;  //전송 속도 mode 설정
	TWSR = 0x00;     //TWPS = 0
	     
}

