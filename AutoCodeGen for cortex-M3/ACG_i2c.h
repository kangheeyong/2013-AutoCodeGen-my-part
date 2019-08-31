#ifndef ACG_I2C_H_
#define ACG_I2C_H_

#include "ACG_datatype.h"

//	Pin Map for I2C

//	I2C1 SCL (Serial Clock) : PB6
//	     SDA (Serial Data)  : PB7
//	I2C2 SCL (Serial Clock) : PB10
//	     SDA (Serial Data)  : PB11

typedef enum
{
   FAST     = 400000,      //Fast Mode     400kbps 
   STANDARD = 100000       //Standard Mode 100kbps

}BitRate;

//I2C 초기화 함수
void AcgI2C1_setting(BitRate bitRate); 
void AcgI2C2_setting(BitRate bitRate);  

#endif