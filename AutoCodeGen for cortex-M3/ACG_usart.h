#ifndef ACG_UART_H
#define ACG_UART_H

#include "ACG_datatype.h"

// Pin Map for USART

// USART1 : PA10(RX1) , PA9(TX1)
// USART2 : PD6 (RX2) , PD5(TX2)
// USART3 : PB11(RX3) , B10(TX3)

#define ACG_USART       USART1

//Baudrate
typedef enum
{
    BAUDRATE_256000 = 256000,
    BAUDRATE_128000 = 128000,
    BAUDRATE_115200 = 115200,
    BAUDRATE_57600 = 57600,
    BAUDRATE_56000 = 56000,
    BAUDRATE_38400 = 38400,
    BAUDRATE_19200 = 19200,
    BAUDRATE_14400 = 14400,
    BAUDRATE_9600 = 9600,
    BAUDRATE_4800 = 4800,
    BAUDRATE_2400 = 2400,
    BAUDRATE_1200 = 1200    
}BaudRate;

//전송할 Data bit수
typedef enum
{
    WORDLENGTH_8 = ((uint16_t)0x0000),
    WORDLENGTH_9 = ((uint16_t)0x1000)
}WordLength;

//Stop bit
typedef enum
{
    STOPBIT_1       = ((uint16_t)0x0000),
    STOPBIT_0_DOT_5 = ((uint16_t)0x1000),
    STOPBIT_2       = ((uint16_t)0x2000),
    STOPBIT_1_DOT_5 = ((uint16_t)0x3000)
}StopBit;

//Parit bit
typedef enum
{
    PARITY_NONE = ((uint16_t)0x0000),
    PARITY_EVEN = ((uint16_t)0x0400),
    PARITY_ODD  = ((uint16_t)0x0600) 
}ParitBit;

//Hardwaew control
typedef enum
{
    HWFLOWCONTROL_NONE   = ((uint16_t)0x0000),
    HWFLOWCONTROL_RTS    = ((uint16_t)0x0100),
    HWFLOWCONTROL_CTS    = ((uint16_t)0x0200),
    HWFLOWCONTROL_CRTS   = ((uint16_t)0x0300)
}HWFlowControl;



//USARTx Setting( BaudRate, WordLength, StopBit, Parity, Hardwaew control)
void AcgUSART1_Setting(BaudRate baudRate,WordLength wordLength,StopBit stopBit,ParitBit parity,HWFlowControl hardwareFlowControl);
void AcgUSART2_Setting(BaudRate baudRate,WordLength wordLength,StopBit stopBit,ParitBit parity,HWFlowControl hardwareFlowControl);
void AcgUSART3_Setting(BaudRate baudRate,WordLength wordLength,StopBit stopBit,ParitBit parity,HWFlowControl hardwareFlowControl);

//USART 송신 함수 
void AcgUSART1_txc(uint16_t tx);
void AcgUSART2_txc(uint16_t tx);
void AcgUSART3_txc(uint16_t tx);

//USART 수신 함수 
uint16_t AcgUSART1_rxc();
uint16_t AcgUSART2_rxc();
uint16_t AcgUSART3_rxc();

#endif