#include "stm32f10x.h"
#include "ACG_usart.h"
#include "stdio.h"

uint16_t RX1,RX2,RX3;

void AcgUSART1_Setting(BaudRate baudRate,WordLength wordLength,StopBit stopBit,ParitBit parity,HWFlowControl hardwareFlowControl)
{
    USART_InitTypeDef USART_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE); 
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    //GPIO 환경설정
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    //USART 환경설정
    USART_InitStructure.USART_BaudRate   = baudRate;
    USART_InitStructure.USART_WordLength = wordLength;
    USART_InitStructure.USART_StopBits   = stopBit;
    USART_InitStructure.USART_Parity     = parity;
    USART_InitStructure.USART_HardwareFlowControl
                                         = hardwareFlowControl;
    USART_InitStructure.USART_Mode       = USART_Mode_Rx | USART_Mode_Tx;

    USART_Init(USART1, &USART_InitStructure);
    
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
    
    //인터럽트 핸들러와 우선순위 설정
    NVIC_InitStructure.NVIC_IRQChannel =  USART1_IRQn ;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 37;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 44;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    USART_Cmd(USART1, ENABLE); 
}



void AcgUSART2_Setting(BaudRate baudRate,WordLength wordLength,StopBit stopBit,ParitBit parity,HWFlowControl hardwareFlowControl)
{

    USART_InitTypeDef USART_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
    
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE); 
    RCC_APB2PeriphClockCmd( RCC_APB2Periph_AFIO | RCC_APB2Periph_GPIOD, ENABLE); 

    GPIO_PinRemapConfig ( GPIO_Remap_USART2  , ENABLE );
    //GPIO 환경설정
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOD, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOD, &GPIO_InitStructure);

    //USART 환경설정
    USART_InitStructure.USART_BaudRate   = baudRate;
    USART_InitStructure.USART_WordLength = wordLength;
    USART_InitStructure.USART_StopBits   = stopBit;
    USART_InitStructure.USART_Parity     = parity;
    USART_InitStructure.USART_HardwareFlowControl
                                         = hardwareFlowControl;
    USART_InitStructure.USART_Mode       = USART_Mode_Rx | USART_Mode_Tx;

    USART_Init(USART2, &USART_InitStructure);

    USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
    
    //인터럽트 핸들러와 우선순위 설정
    NVIC_InitStructure.NVIC_IRQChannel =  USART2_IRQn ;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 38;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 45;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    USART_Cmd(USART2, ENABLE); 
}




void AcgUSART3_Setting(BaudRate baudRate,WordLength wordLength,StopBit stopBit,ParitBit parity,HWFlowControl hardwareFlowControl)
{
    USART_InitTypeDef USART_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
    
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    //GPIO 환경설정
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
   
    //USART 환경설정
    USART_InitStructure.USART_BaudRate   = baudRate;
    USART_InitStructure.USART_WordLength = wordLength;
    USART_InitStructure.USART_StopBits   = stopBit;
    USART_InitStructure.USART_Parity     = parity;
    USART_InitStructure.USART_HardwareFlowControl
                                         = hardwareFlowControl;
    USART_InitStructure.USART_Mode       = USART_Mode_Rx | USART_Mode_Tx;

    USART_Init(USART3, &USART_InitStructure);
    
    USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);
    
    //인터럽트 핸들러와 우선순위 설정
    NVIC_InitStructure.NVIC_IRQChannel =  USART3_IRQn ;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 39;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 46;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    USART_Cmd(USART3, ENABLE); 
}





void AcgUSART1_txc(uint16_t tx)
{
  USART_SendData(USART1,tx);
}
void AcgUSART2_txc(uint16_t tx)
{
  USART_SendData(USART2,tx);
}
void AcgUSART3_txc(uint16_t tx)
{
  USART_SendData(USART3,tx);
}

uint16_t AcgUSART1_rxc()
{
  return RX1;
}
uint16_t AcgUSART2_rxc()
{
  return RX2;
}
uint16_t AcgUSART3_rxc()
{
  return RX3;
}

void USART1_IRQHandler(void)
{
  if(USART_GetITStatus(USART1, USART_IT_RXNE) == SET)
  {
    RX1 = USART_ReceiveData(USART1);
    USART_ClearITPendingBit(USART1, USART_IT_RXNE);
  }
}

void USART2_IRQHandler(void)
{
  if(USART_GetITStatus(USART2, USART_IT_RXNE) == SET)
  {
    RX2 = USART_ReceiveData(USART2);
    USART_ClearITPendingBit(USART2, USART_IT_RXNE);
  }
}


void USART3_IRQHandler(void)
{
  if(USART_GetITStatus(USART3, USART_IT_RXNE) == SET)
  {
    RX3 = USART_ReceiveData(USART3);
    USART_ClearITPendingBit(USART3, USART_IT_RXNE);
  }
}

#ifdef __GNUC__
  #define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
  #define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */


PUTCHAR_PROTOTYPE
{
    /* Write a character to the USART */  
    if( ch == '\n') {
        USART_SendData(ACG_USART, '\r');
        while(USART_GetFlagStatus(ACG_USART, USART_FLAG_TXE) == RESET);
        USART_SendData(ACG_USART, '\n');
    }else {
        USART_SendData(ACG_USART, (uint8_t) ch);
    }

    /* Loop until the end of transmission */
    while(USART_GetFlagStatus(ACG_USART, USART_FLAG_TXE) == RESET);

    return ch;
}



