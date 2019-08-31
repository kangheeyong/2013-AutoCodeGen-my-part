/*
 * ACG_TMS320F28335_SCI.h
 *
 *  Created on: 2013. 7. 7.
 *      Author: ssm
 */

#ifndef ACG_UART_H
#define ACG_UART_H

#include "DSP28x_Project.h"

#define SCI_FIFO_SIZE_OVER		0x0001
#define SCI_FIFO_NOT_EMPTY		0x0002
#define SCI_RX_ERROR			0x0003
#define SCI_SUCCESS 			0x0000

#define DEDAY_VALUE				20000000


//	Pin Map for USART
//
//	SCIRXDA : Pin 141 (GPIO_28)
//	SCITXDA : Pin 2   (GPIO_29)
//
//	SCIRXDB : Pin 63  (GPIO_19)
//	SCITXDB : Pin 62  (GPIO_18)
//
//	SCIRXDC : Pin 113 (GPIO_62)
//	SCITXDC : Pin 114 (GPIO_63)



//	USART Channel
//  내부 함수에서만 사용
typedef enum
{
	USART_0,
	USART_1,
	USART_2
}USARTChannel;


typedef enum
{
  BAUDRATE_115200 = 40,
  BAUDRATE_57600 = 80,
  BAUDRATE_38400 = 121,
  BAUDRATE_19200 = 243,
  BAUDRATE_14400 = 325,
  BAUDRATE_9600 = 487,
  BAUDRATE_4800 = 976,
  BAUDRATE_2400 = 1952
}BaudRate;

typedef enum
{
  WORDLENGTH_1,
  WORDLENGTH_2,
  WORDLENGTH_3,
  WORDLENGTH_4,
  WORDLENGTH_5,
  WORDLENGTH_6,
  WORDLENGTH_7,
  WORDLENGTH_8

}WordLength;

typedef enum
{
  STOPBIT_1 ,
  STOPBIT_2
}StopBit;


typedef enum
{
  PARITY_ODD = 0,
  PARITY_EVEN = 1,
  PARITY_NONE= 2


}ParityBit;


//USARTx 초기화 함수
void AcgUSART0_Setting(BaudRate baudRate,WordLength wordLength,StopBit stopBit,ParityBit parity);
void AcgUSART1_Setting(BaudRate baudRate,WordLength wordLength,StopBit stopBit,ParityBit parity);
void AcgUSART2_Setting(BaudRate baudRate,WordLength wordLength,StopBit stopBit,ParityBit parity);

//내부 함수
void AcgUsart_InterruptSetting(USARTChannel USARTx);
void AcgUsart_SetBaudRate(USARTChannel USARTx,BaudRate baudRate);
void AcgUsart_FIFOSetting(USARTChannel USARTx);
void AcgUsart_ParitySetting(USARTChannel USARTx, ParityBit parity);


//인터럽트 수신 벡터
interrupt void AcgUsart0_RxISR(void);
interrupt void AcgUsart1_RxISR(void);
interrupt void AcgUsart2_RxISR(void);


//사용자 활용 함수
void AcgUSART0_txc(char c);      //char 송신 함수  (channel , 보낼 문자)
void AcgUSART1_txc(char c);
void AcgUSART2_txc(char c);

char AcgUSART0_rxc();             //char 수신 함수  (channel)   return 수신한 문자
char AcgUSART1_rxc();
char AcgUSART2_rxc();


void scia_xmit(char a);
char scia_rxcv();



#endif
