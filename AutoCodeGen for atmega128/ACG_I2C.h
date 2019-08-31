#ifndef I2C_H
#define I2C_H

#include <avr/io.h>
#include <avr/delay.h>


//	Pin Map for I2C

//	SCL (Serial Clock) : PD0
//	SDA (Serial Data)  : PD1


//I2C 전송 속도
typedef enum
{
   FAST = 12,      //Fast Mode     400kbps (TWBR =12 , TWPS =0)
   STANDARD = 72   //Standard Mode 100kbps (TWBR =72 , TWPS =0)

}BitRate;


//I2C 초기화 함수
void AcgI2C_Setting(BitRate bitRate);  //  parameter : 전송 속도 (FastMode or StandardMode)



#endif
