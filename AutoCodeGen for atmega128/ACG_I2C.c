#include "ACG_I2C.h"


//I2C �ʱ�ȭ �Լ�
void AcgI2C_Setting(BitRate bitRate)  //  parameter : ���� �ӵ� (FastMode or StandardMode)
{
    TWBR = bitRate;  //���� �ӵ� mode ����
	TWSR = 0x00;     //TWPS = 0
	     
}

