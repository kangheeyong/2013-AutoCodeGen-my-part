#ifndef SPI_H
#define SPI_H

#include <avr/io.h>

#define SS PB0
#define SCK PB1
#define MOSI PB2
#define MISO PB3



//	Pin Map for SPI

//	SS   (Slave Select) : PB0
//	SCK  (Serial Clock) : PB1
//	MOSI (Master Out Slave In) : PB2
//	MISO (Master In Slave Out) : PB3

//Serial Clock
typedef enum
{
    SCLK_4000000,   // 16Mhz / 4  = 4Mhz
	SCLK_1000000,   // 16Mhz / 16 = 1Mhz
	SCLK_250000,    // 16Mhz / 64 = 250kHz
	SCLK_125000     // 16Mhz / 128= 125kHz

}SerialClock;




//SPI Mode 
typedef enum
{                //                     Leading edge      Trailing edge
    MODE_01,     // CPOL = 0, CPHA =0   Sample(Rising)    Setup(Falling)
	MODE_02,     // CPOL = 0, CPHA =1   Setup (Rising)    Sample(Falling)
	MODE_03,     // CPOL = 1, CPHA =0   Sample(Falling)   Setup(Rising) 
	MODE_04      // CPOL = 1, CPHA =1   Setup(Falling)    Sample(Risiing)

}SPIMode;


//Character Length  (������ ���� bit ��)
typedef enum
{
   CHARLENGTH_8  // Char Length : 8bit

}CharLength;





//SPI �ʱ�ȭ �Լ�             

//SPI Master �ʱ�ȭ  (SCK Clock , SPI_Mode) 
void AcgSPI_Setting(SerialClock clock,SPIMode spiMode,CharLength charLength);



//���� �Լ�
void AcgSCK_ClockSetting(SerialClock clock); //SCK Clock ����
void AcgSPI_ModeSetting(SPIMode spiMode); //SPI Mode ����





#endif
