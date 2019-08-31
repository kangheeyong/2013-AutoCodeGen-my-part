#include "stm32f10x.h"
#include "ACG_spi.h"



void AcgSpi1_Setting(SerialClock clock,SpiMode spiMode,CharLength charLength)
{
    SPI_InitTypeDef SPI_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;
    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE); 
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_7;  //PA5 SCK,CK   PA7 MOSI,SDI 
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;  //PA6 MISO,SDO
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;  //PA4 CS,NSS 
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    

    SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
    SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
    SPI_InitStructure.SPI_DataSize = charLength;
    if(spiMode == MODE_01)
    {
         SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;  
         SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
    }
    else if(spiMode == MODE_02)
    {
          SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;  
          SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge; 
    }
    else if(spiMode == MODE_03)
    {
          SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;  
          SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;       
    }
    else 
    {
          SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;  
          SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;       
    }
    SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
    SPI_InitStructure.SPI_BaudRatePrescaler = clock;
    SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
    SPI_InitStructure.SPI_CRCPolynomial = 7;

    SPI_Init(SPI1,&SPI_InitStructure);

    SPI_Cmd(SPI1,ENABLE);  
}

void AcgSpi2_Setting(SerialClock clock,SpiMode spiMode,CharLength charLength)
{
    SPI_InitTypeDef SPI_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;
    
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE); 
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_15;  //PB13 SCK,CK  PB15 MOSI,SDI 
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;  //PB14 MISO,SDO 
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;  //PB12 CS,NSS 
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    

    SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
    SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
    SPI_InitStructure.SPI_DataSize = charLength;
    if(spiMode == MODE_01)
    {
         SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;  
         SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
    }
    else if(spiMode == MODE_02)
    {
          SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;  
          SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge; 
    }
    else if(spiMode == MODE_03)
    {
          SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;  
          SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;       
    }
    else 
    {
          SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;  
          SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;       
    }
    SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
    SPI_InitStructure.SPI_BaudRatePrescaler = clock;
    SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
    SPI_InitStructure.SPI_CRCPolynomial = 7;

    SPI_Init(SPI2,&SPI_InitStructure);

    SPI_Cmd(SPI2,ENABLE);  
    
}


void AcgSpi3_Setting(SerialClock clock,SpiMode spiMode,CharLength charLength)
{
    SPI_InitTypeDef SPI_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;
    
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI3, ENABLE); 
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB, ENABLE);
    
    GPIO_PinRemapConfig(GPIO_Remap_SPI3, ENABLE);
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_5;  //PB3 SCK,CK   PB5 MOSI,SDI 
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;  //PB4 MISO,SDO
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;  //PA15 CS,NSS 
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    

    SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
    SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
    SPI_InitStructure.SPI_DataSize = charLength;
    if(spiMode == MODE_01)
    {
         SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;  
         SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
    }
    else if(spiMode == MODE_02)
    {
          SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;  
          SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge; 
    }
    else if(spiMode == MODE_03)
    {
          SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;  
          SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;       
    }
    else 
    {
          SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;  
          SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;       
    }
    SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
    SPI_InitStructure.SPI_BaudRatePrescaler = clock;
    SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
    SPI_InitStructure.SPI_CRCPolynomial = 7;

    SPI_Init(SPI3,&SPI_InitStructure);

    SPI_Cmd(SPI3,ENABLE);  
}
