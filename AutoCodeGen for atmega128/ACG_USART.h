#ifndef USART_H
#define USART_H

#include <avr/io.h>
#include <avr/interrupt.h>


// Pin Map for USART

// USART0 : PE0(RX0) , PE1(TX0)
// USART1 : PD2(RX1) , PD3(TX1)


//Baudrate
typedef enum
{
  BAUDRATE_115200 = 8,
  BAUDRATE_57600 = 16,
  BAUDRATE_38400 = 25,
  BAUDRATE_19200 = 51,
  BAUDRATE_14400 = 68, 
  BAUDRATE_9600 = 103,
  BAUDRATE_4800 = 207,
  BAUDRATE_2400 = 416

}BaudRate;


//전송할 Data bit수
typedef enum
{
  WORDLENGTH_5 = 0x00, //000
  WORDLENGTH_6 = 0x01, //001 
  WORDLENGTH_7 = 0x02, //010
  WORDLENGTH_8 = 0x03, //011
  WORDLENGTH_9 = 0x07  //111

}WordLength;


//Stop bit
typedef enum
{
  STOPBIT_1 = 0x0,
  STOPBIT_2 = 0x1
  
}StopBit;


//Parit bit
typedef enum
{
  PARITY_NONE = 0x0,
  PARITY_EVEN = 0x2,
  PARITY_ODD = 0x3
  
}ParityBit;



//USARTx Setting( BaudRate, WordLength, StopBit, Parity )
void AcgUSART0_Setting(BaudRate baudRate, WordLength wordLength, StopBit stopBit, ParityBit parity);
void AcgUSART1_Setting(BaudRate baudRate, WordLength wordLength, StopBit stopBit, ParityBit parity);

//USART 송신 함수 
void AcgUSART0_txc(char tx);
void AcgUSART1_txc(char tx);


//USART 수신 함수 
char AcgUSART0_rxc();
char AcgUSART1_rxc();




#endif
