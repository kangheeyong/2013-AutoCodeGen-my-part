/*
 * ACG_I2C.h
 *
 *  Created on: 2013. 7. 18.
 *      Author: ssm
 */

#ifndef ACG_I2C_H_
#define ACG_I2C_H_

#include "DSP28x_Project.h"

//	Pin Map for I2C
//
//	SCLA (Serial Clock A) : Pin 75 (GPIO_33)
//	SDAA (Serial Data A)  : Pin 74 (GPIO_32)
//

//	I2C 전송 속도
typedef enum
{
    FAST ,    //Fast Mode     400kbps
    STANDARD  //Standard Mode 100kbps

}BitRate;

//	I2C 초기화 함수
void AcgI2C_Setting(BitRate bitRate);






#endif /* ACG_I2C_H_ */
