#include "ACG_SPI.h"


 //SPI Master �ʱ�ȭ  
void AcgSPI_MasterSetting(SerialClock clock,SPIMode spiMode,CharLength charLength)
{

    PORTB |= (1<<SS);
	DDRB |= ((1<<SS) | (1<<SCK) | (1<<MOSI));

	SPCR |= ((1<<SPE) | (1<<MSTR) | (0<< DORD));
	//SPE : SPI Enable,  MSTR : 1�̸� MASTER�� 0�̸� Slave , DORD : 0 (MSB)
	


    AcgSck_ClockSetting(clock);    //SCK Clock ����
    AcgSPI_ModeSetting(spiMode);  //SPI Mode ����

}



void AcgSck_ClockSetting(SerialClock clock) //SCK Clock ����
{
    SPCR |= clock ;  
}

void AcgSPI_ModeSetting(SPIMode spiMode) //SPI Mode ����
{
    SPCR |= (spiMode << 2);
}

