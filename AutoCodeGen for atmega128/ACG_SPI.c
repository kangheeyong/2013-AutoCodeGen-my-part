#include "ACG_SPI.h"


 //SPI Master 초기화  
void AcgSPI_MasterSetting(SerialClock clock,SPIMode spiMode,CharLength charLength)
{

    PORTB |= (1<<SS);
	DDRB |= ((1<<SS) | (1<<SCK) | (1<<MOSI));

	SPCR |= ((1<<SPE) | (1<<MSTR) | (0<< DORD));
	//SPE : SPI Enable,  MSTR : 1이면 MASTER로 0이면 Slave , DORD : 0 (MSB)
	


    AcgSck_ClockSetting(clock);    //SCK Clock 설정
    AcgSPI_ModeSetting(spiMode);  //SPI Mode 설정

}



void AcgSck_ClockSetting(SerialClock clock) //SCK Clock 설정
{
    SPCR |= clock ;  
}

void AcgSPI_ModeSetting(SPIMode spiMode) //SPI Mode 설정
{
    SPCR |= (spiMode << 2);
}

