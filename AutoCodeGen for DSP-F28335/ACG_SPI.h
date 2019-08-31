/*
 * ACG_SPI.h
 *
 *  Created on: 2013. 7. 26.
 *      Author: RODONGWAN
 */

#ifndef SPI_H
#define SPI_H


//	Pin Map for SPI
//
//	SPISIMOA ( slave in, master out)   : Pin 27 (GPIO_16)
//	SPISOMIA ( slave out, master in)   : Pin 28 (GPIO_17)
//	SPICLKA  ( Clock input/output)     : Pin 62 (GPIO_18)
//	SPISTEA  ( slave transmit enable input/output) : Pin 63 (GPIO_19)

//Serial Clock
typedef enum
{                      // 통신 속도 : 37.5Mhz / (BRR+1)
	SCLK_7500000 = 4,  // 7.5MHz   (BRR : 4)
	SCLK_6250000 = 5,  // 6.25Mhz
	SCLK_3750000 = 9,  // 3.75Mhz
	SCLK_2500000 = 14, // 2.5Mhz
	SCLK_1500000 = 24, // 1.5Mhz
	SCLK_1250000 = 29, // 1.25Mhz
	SCLK_750000  = 49, // 750kHz
	SCLK_625000  = 59, // 625kHz
	SCLK_500000  = 74, // 500kHz
	SCLK_375000  = 99, // 375kHz
	SCLK_300000  = 124// 300kHz

}SerialClock;

//SPI Mode
typedef enum
{              //                               Clock Polarity       Clock Phase
	MODE_01,   // Rising edge without delay           0                   0
	MODE_02,   // Rising edge with delay              0                   1
	MODE_03,   // Falling edge without delay          1                   0
	MODE_04    // Falling edge with delay             1                   1

}SPIMode;

//character length (데이터 전송 bit 수)
typedef enum
{
	CHARLENGTH_1,
	CHARLENGTH_2,
	CHARLENGTH_3,
	CHARLENGTH_4,
	CHARLENGTH_5,
	CHARLENGTH_6,
	CHARLENGTH_7,
	CHARLENGTH_8,
	CHARLENGTH_9,
	CHARLENGTH_10,
	CHARLENGTH_11,
	CHARLENGTH_12,
	CHARLENGTH_13,
	CHARLENGTH_14,
	CHARLENGTH_15,
	CHARLENGTH_16

}CharLength;

//SPI 초기화 함수

//SPI Master 초기화
void AcgSPI_Setting(SerialClock clock, SPIMode spiMode, CharLength charLength);



//내부 함수
void AcgSPI_ModeSetting(SPIMode spiMode);


#endif


