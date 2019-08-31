#ifndef ACG_SPI_H_
#define ACG_SPI_H_


#include "ACG_datatype.h"

//	Pin Map for SPI

//	SPI1  SS   (Slave Select) : PA4
//	      SCK  (Serial Clock) : PA5
//	      MOSI (Master Out Slave In) : PA6
//	      MISO (Master In Slave Out) : PA7

//	SPI2  SS   (Slave Select) : PB12
//	      SCK  (Serial Clock) : PB13
//	      MOSI (Master Out Slave In) : PB14
//	      MISO (Master In Slave Out) : PB15

//	SPI3  SS   (Slave Select) : PA15
//	      SCK  (Serial Clock) : PB3
//	      MOSI (Master Out Slave In) : PB4
//	      MISO (Master In Slave Out) : PB5

//Serial Clock
typedef enum
{
      SCLK_Divide_2      = ((uint16_t)0x0000),   //SYSTEMCLOCK / 2
      SCLK_Divide_4      = ((uint16_t)0x0008),   //SYSTEMCLOCK / 4
      SCLK_Divide_8      = ((uint16_t)0x0010),   //SYSTEMCLOCK / 8
      SCLK_Divide_16     = ((uint16_t)0x0018),   //SYSTEMCLOCK / 16
      SCLK_Divide_32     = ((uint16_t)0x0020),   //SYSTEMCLOCK / 32
      SCLK_Divide_64     = ((uint16_t)0x0028),   //SYSTEMCLOCK / 64
      SCLK_Divide_128    = ((uint16_t)0x0030),   //SYSTEMCLOCK / 128
      SCLK_Divide_256    = ((uint16_t)0x0038)    //SYSTEMCLOCK / 256
}SerialClock;


//SPI Mode 
typedef enum
{                //                     Leading edge      Trailing edge
        MODE_01,     // CPOL = 0, CPHA =0   Sample(Rising)    Setup(Falling)
	MODE_02,     // CPOL = 0, CPHA =1   Setup (Rising)    Sample(Falling)
	MODE_03,     // CPOL = 1, CPHA =0   Sample(Falling)   Setup(Rising) 
	MODE_04      // CPOL = 1, CPHA =1   Setup(Falling)    Sample(Risiing)

}SpiMode;


//Character Length  (데이터 전송 bit 수)
typedef enum
{
   CHARLENGTH_8  = ((uint16_t)0x0000),   // Char Length : 8bit
   CHARLENGTH_16 = ((uint16_t)0x0800)    // Char Length : 16bit

}CharLength;

//SPI 초기화 함수
void AcgSPI1_Setting(SerialClock clock,SpiMode spiMode,CharLength charLength); 
void AcgSPI2_Setting(SerialClock clock,SpiMode spiMode,CharLength charLength); 
void AcgSPI3_Setting(SerialClock clock,SpiMode spiMode,CharLength charLength);

#endif