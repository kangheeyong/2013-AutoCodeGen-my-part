#include "ACG_USART.h"


// Receive Complete Flag
// 읽혀지지 않은 rxn_Data가 있으면 1로 Set
// 이를 읽어서 rxn_Data가 비어있는 상태이면 0으로 Clear

volatile char rcvCompleteFlag0 = 0;  
volatile char rcvCompleteFlag1 = 0;

volatile char rx0_Data;
volatile char rx1_Data;


//USART0 Setting( BaudRate, WordLength, StopBit, Parity )
void AcgUSART0_Setting(BaudRate baudRate, WordLength wordLength, StopBit stopBit, ParityBit parity)
{
      SREG &= (~0x80); // global Interrupt disable 
    
      UCSR0A = 0;    
      UCSR0B = ((unsigned char)wordLength>>2)<<2 | 0x98;
      UCSR0C = ((unsigned char)wordLength<<1)&0x6 | (unsigned char)stopBit<<3 |(unsigned char)parity << 4; 

      
      UBRR0H = (unsigned char)((int)baudRate>>8);
      UBRR0L = (unsigned char)baudRate;
      
      SREG |= 0x80;
}


//USART1 Setting( BaudRate, WordLength, StopBit, Parity )
void AcgUSART1_Setting(BaudRate baudRate, WordLength wordLength, StopBit stopBit, ParityBit parity)
{
      SREG &= (~0x80); // global Interrupt disable 
    
      UCSR0A = 0;    
      UCSR1B = ((unsigned char)wordLength>>2)<<2 | 0x98;
      UCSR1C = ((unsigned char)wordLength<<1)&0x6 | (unsigned char)stopBit<<3 |(unsigned char)parity << 4; 

      
      UBRR1H = (unsigned char)((int)baudRate>>8);
      UBRR1L = (unsigned char)baudRate;
      
      SREG |= 0x80;
}







//USART 송신 함수  channel (0~1) , char 
void AcgUSART0_txc(char tx)
{
 
    while(!(UCSR0A & 0x20));
   
    UDR0 = tx;

}

void AcgUSART1_txc(char tx)
{
  
	while(!(UCSR1A & 0x20));

    UDR1 = tx;

}



//USART 수신 함수 channel (0~1)
char AcgUSART0_rxc()
{
    // Wait for data to be received
    while(!rcvCompleteFlag0);
    

	rcvCompleteFlag0 = 0;

    return rx0_Data;

}

char AcgUSART1_rxc()
{
    // Wait for data to be received
    while(!rcvCompleteFlag1);
    

	rcvCompleteFlag1 = 0;

    return rx1_Data;

}







ISR(USART0_RX_vect)  //Uart0 수신 Interrupt vector
{
    rcvCompleteFlag0 = 1;

    rx0_Data = UDR0;

}


ISR(USART1_RX_vect)  //Uart1 수신 Interrupt vector
{

    rcvCompleteFlag1 = 1;

    rx1_Data = UDR1;


}







