/*
 * ACG_TMS320F28335_SCI.c
 *
 *  Created on: 2013. 7. 7.
 *      Author: ssm
 */


#include "ACG_USART.h"
#include "DSP2833x_Sci.h"


// Receive Complete Flag
// 읽혀지지 않은 rxn_Data가 있으면 1로 Set
// 이를 읽어서 rxn_Data가 비어있는 상태이면 0으로 Clear

volatile int rcvCompleteFlag0 ;
volatile int rcvCompleteFlag1 ;
volatile int rcvCompleteFlag2 ;


Uint16 SCI_RXintCount1;
Uint16 SCI_RXintCount2;
Uint16 SCI_RXintCount3;

char rx0_Data;
char rx1_Data;
char rx2_Data;

void AcgUSART0_Setting(BaudRate baudRate,WordLength wordLength,StopBit stopBit,ParityBit parity)
{

	InitSciaGpio();

	AcgUsart_InterruptSetting(USART_0);

	SCI_RXintCount1=0;
	rcvCompleteFlag0=0;


	SciaRegs.SCICTL1.bit.SWRESET = 0;		// SCI 소프트웨어 리셋

	AcgUsart_SetBaudRate(USART_0,baudRate); //BaudRate Setting

	/* test */
	SciaRegs.SCICCR.bit.LOOPBKENA = 0;		// SCI 루프백 테스트 모드 Disable
   /*  test loopback  */

	SciaRegs.SCICCR.bit.SCICHAR = wordLength;		// SCI 송수신 Charcter-length 설정 : WordLength-1 bit
	SciaRegs.SCICCR.bit.STOPBITS = stopBit;


	//Parity Mode Setting
	AcgUsart_ParitySetting(USART_0,parity);


	SciaRegs.SCICTL1.bit.RXENA = 1;			// SCI 송신기능 Enable
	SciaRegs.SCICTL1.bit.TXENA = 1;			// SCI 수신기능 Enable


	AcgUsart_FIFOSetting(USART_0);


	SciaRegs.SCICTL1.bit.SWRESET = 1;		// SCI 소프트웨어 리셋 해제

	PieCtrlRegs.PIEIER9.bit.INTx1 = 1;		// PIE 인터럽트(SCIRXINTA) : Enable
	IER |= M_INT9;							// CPU 인터럽트(INT9) : Enable




}


void AcgUSART1_Setting(BaudRate baudRate,WordLength wordLength,StopBit stopBit,ParityBit parity)
{
	InitScibGpio();

	AcgUsart_InterruptSetting(USART_1);

	SCI_RXintCount2=0;
	rcvCompleteFlag1=0;


	ScibRegs.SCICTL1.bit.SWRESET = 0;		// SCI 소프트웨어 리셋

	AcgUsart_SetBaudRate(USART_1,baudRate); //BaudRate Setting

	/* test */
	ScibRegs.SCICCR.bit.LOOPBKENA = 0;		// SCI 루프백 테스트 모드 Disable
   /*  test loopback  */

	ScibRegs.SCICCR.bit.SCICHAR = wordLength;		// SCI 송수신 Charcter-length 설정 : WordLength-1 bit
	ScibRegs.SCICCR.bit.STOPBITS = stopBit;

	//Parity Mode Setting
	AcgUsart_ParitySetting(USART_1,parity);


	ScibRegs.SCICTL1.bit.RXENA = 1;			// SCI 송신기능 Enable
	ScibRegs.SCICTL1.bit.TXENA = 1;			// SCI 수신기능 Enable


	AcgUsart_FIFOSetting(USART_1);


	ScibRegs.SCICTL1.bit.SWRESET = 1;		// SCI 소프트웨어 리셋 해제

	PieCtrlRegs.PIEIER9.bit.INTx3 = 1;		// PIE 인터럽트(SCIRXINTB) : Enable
	IER |= M_INT9;							// CPU 인터럽트(INT9) : Enable



}


void AcgUSART2_Setting(BaudRate baudRate,WordLength wordLength,StopBit stopBit,ParityBit parity)
{
	InitScicGpio();

	AcgUsart_InterruptSetting(USART_2);

	SCI_RXintCount3=0;
	rcvCompleteFlag2=0;

	ScicRegs.SCICTL1.bit.SWRESET = 0;		// SCI 소프트웨어 리셋

	AcgUsart_SetBaudRate(USART_2,baudRate); //BaudRate Setting

	/* test */
	ScicRegs.SCICCR.bit.LOOPBKENA = 0;		// SCI 루프백 테스트 모드 Disable
   /*  test loopback  */

	ScicRegs.SCICCR.bit.SCICHAR = wordLength;		// SCI 송수신 Charcter-length 설정 : WordLength-1 bit
	ScicRegs.SCICCR.bit.STOPBITS = stopBit;

	//Parity Mode Setting
	AcgUsart_ParitySetting(USART_2,parity);


	ScicRegs.SCICTL1.bit.RXENA = 1;			// SCI 송신기능 Enable
	ScicRegs.SCICTL1.bit.TXENA = 1;			// SCI 수신기능 Enable


	AcgUsart_FIFOSetting(USART_2);


	ScicRegs.SCICTL1.bit.SWRESET = 1;		// SCI 소프트웨어 리셋 해제

	PieCtrlRegs.PIEIER8.bit.INTx5 = 1;		// PIE 인터럽트(SCIRXINTB) : Enable
	IER |= M_INT8;							// CPU 인터럽트(INT8) : Enable


}





void AcgUsart_InterruptSetting(USARTChannel USARTx)
{

	EALLOW;
	if(USARTx == USART_0)
		PieVectTable.SCIRXINTA = &AcgUsart0_RxISR;

	else if(USARTx == USART_1)
		PieVectTable.SCIRXINTB = &AcgUsart1_RxISR;

	else
		PieVectTable.SCIRXINTC = &AcgUsart2_RxISR;

	EDIS;

}


void AcgUsart_SetBaudRate(USARTChannel USARTx,BaudRate baudRate)
{
	volatile struct SCI_REGS *SCIptr;

	Uint16 BBRH;
	Uint16 BBRL;

	BBRH = (((Uint16)baudRate) >> 8 ) ;
	BBRL = ((Uint16)baudRate) & 0x00FF;

	if(USARTx == USART_0)
		SCIptr = &SciaRegs;

	else if(USARTx == USART_1)
		SCIptr = &ScibRegs;

	else
		SCIptr = &ScicRegs;


	// SCI Baudrate 설정
	SCIptr->SCIHBAUD = BBRH;
	SCIptr->SCILBAUD = BBRL;






}




void AcgUsart_ParitySetting(USARTChannel USARTx, ParityBit parity)
{
	volatile struct SCI_REGS *SCIptr;

	 if(USARTx == USART_0)
		SCIptr = &SciaRegs;

	else if(USARTx == USART_1)
		SCIptr = &ScibRegs;

	else
		SCIptr = &ScicRegs;


    //Parity Mode Setting
	if(parity == PARITY_NONE)
		SCIptr->SCICCR.bit.PARITYENA = 0;

	else
	{
		SCIptr->SCICCR.bit.PARITYENA = 1;
		SCIptr->SCICCR.bit.PARITY = parity;

	}
}



void AcgUsart_FIFOSetting(USARTChannel USARTx)
{
	volatile struct SCI_REGS *SCIptr;

    if(USARTx == USART_0)
    		SCIptr = &SciaRegs;

    else if(USARTx == USART_1)
    	SCIptr = &ScibRegs;

    else
    	SCIptr = &ScicRegs;


	// SCI의 송신 FIFO 설정
    SCIptr->SCIFFTX.bit.SCIFFENA = 1;		// SCI FIFO 사용 설정 Enable
    SCIptr->SCIFFTX.bit.TXFFINTCLR = 1;	// SCI 송신 FIFO 인터럽트 플래그 클리어
    SCIptr->SCIFFTX.bit.TXFIFOXRESET = 1;	// SCI 송신 FIFO RE-enable
    SCIptr->SCIFFTX.bit.SCIRST = 1;		// SCI 리셋 해제


	// SCI의 수신 FIFO 설정
    SCIptr->SCIFFRX.bit.RXFFINTCLR = 1;	// SCI 수신 FIFO 인터럽트 플래그 클리어
    SCIptr->SCIFFRX.bit.RXFFIENA = 1;		// SCI 수신 FIFO 인터럽트 Enable
    SCIptr->SCIFFRX.bit.RXFIFORESET = 1;	// SCI 수신 FIFO RE-enable
    SCIptr->SCIFFRX.bit.RXFFIL = 1;		// SCI 수신 FIFO 인터럽트 레벨 설정


}





//============================================================================================
//	Local Interrupt Service Routine : SCI 수신 FIFO 인터럽트 서비스 루틴
//--------------------------------------------------------------------------------------------
//	SCIFFRX 레지스터의 RSFFST의 값이 RXFFIL에 설정된 값보다 크거나 같으면 실행.
//  SCI RXFIFO에 수신된 데이터를 메로리에 저장함.
//--------------------------------------------------------------------------------------------


interrupt void AcgUsart0_RxISR(void)
{

	rcvCompleteFlag0 = 1;

	SciaRegs.SCIFFRX.bit.RXFIFORESET = 0;		// SCI 수신 FIFO 인터럽트 Enable
	rx0_Data = SciaRegs.SCIRXBUF.bit.RXDT;


	SCI_RXintCount1++;


	SciaRegs.SCIFFRX.bit.RXFFOVRCLR = 1;			// Clear Overflow flag
	SciaRegs.SCIFFRX.bit.RXFFINTCLR = 1;			// Clear Interrupt flag
	SciaRegs.SCIFFRX.bit.RXFIFORESET = 1;		// SCI 수신 FIFO 인터럽트 Enable

	PieCtrlRegs.PIEACK.all = PIEACK_GROUP9;			// Acknowledge interrupt to PIE
}


interrupt void AcgUsart1_RxISR(void)
{
	rcvCompleteFlag1 = 1;

	ScibRegs.SCIFFRX.bit.RXFIFORESET = 0;		// SCI 수신 FIFO 인터럽트 Enable
	rx1_Data = ScibRegs.SCIRXBUF.bit.RXDT;

	SCI_RXintCount2++;


	ScibRegs.SCIFFRX.bit.RXFFOVRCLR = 1;			// Clear Overflow flag
	ScibRegs.SCIFFRX.bit.RXFFINTCLR = 1;			// Clear Interrupt flag
	ScibRegs.SCIFFRX.bit.RXFIFORESET = 1;		// SCI 수신 FIFO 인터럽트 Enable
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP9;			// Acknowledge interrupt to PIE
}


interrupt void AcgUsart2_RxISR(void)
{
	rcvCompleteFlag2 = 1;

	ScicRegs.SCIFFRX.bit.RXFIFORESET = 0;		// SCI 수신 FIFO 인터럽트 Enable
	rx2_Data = ScicRegs.SCIRXBUF.bit.RXDT;

	SCI_RXintCount3++;

	ScicRegs.SCIFFRX.bit.RXFFOVRCLR = 1;			// Clear Overflow flag
	ScicRegs.SCIFFRX.bit.RXFFINTCLR = 1;			// Clear Interrupt flag
	ScicRegs.SCIFFRX.bit.RXFIFORESET = 1;		// SCI 수신 FIFO 인터럽트 Enable
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP8;			// Acknowledge interrupt to PIE
}
//============================================================================================



//사용자 활용 함수
void AcgUSART0_txc(char c)      //char 송신 함수  (channel , 보낼 문자)
{
	// 기존 데이터가 남아 있을 경우 보낼 때까지 기다린다.
	while(SciaRegs.SCIFFTX.bit.TXFFST != 0);

	// 메모리에 저장된 데이터를 SCI로 전송
	SciaRegs.SCITXBUF = (Uint16)(c & 0x00FF);
}

void AcgUSART1_txc(char c)
{
	// 기존 데이터가 남아 있을 경우 보낼 때까지 기다린다.
	while(ScibRegs.SCIFFTX.bit.TXFFST != 0);

	// 메모리에 저장된 데이터를 SCI로 전송
	ScibRegs.SCITXBUF = (Uint16)(c & 0x00FF);
}

void AcgUSART2_txc(char c)
{
	// 기존 데이터가 남아 있을 경우 보낼 때까지 기다린다.
	while(ScicRegs.SCIFFTX.bit.TXFFST != 0);

	// 메모리에 저장된 데이터를 SCI로 전송
	ScicRegs.SCITXBUF = (Uint16)(c & 0x00FF);
}

char AcgUSART0_rxc()             //char 수신 함수  (channel)   return 수신한 문자
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

char AcgUSART2_rxc()
{
    // Wait for data to be received
    while(!rcvCompleteFlag2);


    rcvCompleteFlag2 = 0;

	return rx2_Data;
}






