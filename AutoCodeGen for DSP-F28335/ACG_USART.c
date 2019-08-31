/*
 * ACG_TMS320F28335_SCI.c
 *
 *  Created on: 2013. 7. 7.
 *      Author: ssm
 */


#include "ACG_USART.h"
#include "DSP2833x_Sci.h"


// Receive Complete Flag
// �������� ���� rxn_Data�� ������ 1�� Set
// �̸� �о rxn_Data�� ����ִ� �����̸� 0���� Clear

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


	SciaRegs.SCICTL1.bit.SWRESET = 0;		// SCI ����Ʈ���� ����

	AcgUsart_SetBaudRate(USART_0,baudRate); //BaudRate Setting

	/* test */
	SciaRegs.SCICCR.bit.LOOPBKENA = 0;		// SCI ������ �׽�Ʈ ��� Disable
   /*  test loopback  */

	SciaRegs.SCICCR.bit.SCICHAR = wordLength;		// SCI �ۼ��� Charcter-length ���� : WordLength-1 bit
	SciaRegs.SCICCR.bit.STOPBITS = stopBit;


	//Parity Mode Setting
	AcgUsart_ParitySetting(USART_0,parity);


	SciaRegs.SCICTL1.bit.RXENA = 1;			// SCI �۽ű�� Enable
	SciaRegs.SCICTL1.bit.TXENA = 1;			// SCI ���ű�� Enable


	AcgUsart_FIFOSetting(USART_0);


	SciaRegs.SCICTL1.bit.SWRESET = 1;		// SCI ����Ʈ���� ���� ����

	PieCtrlRegs.PIEIER9.bit.INTx1 = 1;		// PIE ���ͷ�Ʈ(SCIRXINTA) : Enable
	IER |= M_INT9;							// CPU ���ͷ�Ʈ(INT9) : Enable




}


void AcgUSART1_Setting(BaudRate baudRate,WordLength wordLength,StopBit stopBit,ParityBit parity)
{
	InitScibGpio();

	AcgUsart_InterruptSetting(USART_1);

	SCI_RXintCount2=0;
	rcvCompleteFlag1=0;


	ScibRegs.SCICTL1.bit.SWRESET = 0;		// SCI ����Ʈ���� ����

	AcgUsart_SetBaudRate(USART_1,baudRate); //BaudRate Setting

	/* test */
	ScibRegs.SCICCR.bit.LOOPBKENA = 0;		// SCI ������ �׽�Ʈ ��� Disable
   /*  test loopback  */

	ScibRegs.SCICCR.bit.SCICHAR = wordLength;		// SCI �ۼ��� Charcter-length ���� : WordLength-1 bit
	ScibRegs.SCICCR.bit.STOPBITS = stopBit;

	//Parity Mode Setting
	AcgUsart_ParitySetting(USART_1,parity);


	ScibRegs.SCICTL1.bit.RXENA = 1;			// SCI �۽ű�� Enable
	ScibRegs.SCICTL1.bit.TXENA = 1;			// SCI ���ű�� Enable


	AcgUsart_FIFOSetting(USART_1);


	ScibRegs.SCICTL1.bit.SWRESET = 1;		// SCI ����Ʈ���� ���� ����

	PieCtrlRegs.PIEIER9.bit.INTx3 = 1;		// PIE ���ͷ�Ʈ(SCIRXINTB) : Enable
	IER |= M_INT9;							// CPU ���ͷ�Ʈ(INT9) : Enable



}


void AcgUSART2_Setting(BaudRate baudRate,WordLength wordLength,StopBit stopBit,ParityBit parity)
{
	InitScicGpio();

	AcgUsart_InterruptSetting(USART_2);

	SCI_RXintCount3=0;
	rcvCompleteFlag2=0;

	ScicRegs.SCICTL1.bit.SWRESET = 0;		// SCI ����Ʈ���� ����

	AcgUsart_SetBaudRate(USART_2,baudRate); //BaudRate Setting

	/* test */
	ScicRegs.SCICCR.bit.LOOPBKENA = 0;		// SCI ������ �׽�Ʈ ��� Disable
   /*  test loopback  */

	ScicRegs.SCICCR.bit.SCICHAR = wordLength;		// SCI �ۼ��� Charcter-length ���� : WordLength-1 bit
	ScicRegs.SCICCR.bit.STOPBITS = stopBit;

	//Parity Mode Setting
	AcgUsart_ParitySetting(USART_2,parity);


	ScicRegs.SCICTL1.bit.RXENA = 1;			// SCI �۽ű�� Enable
	ScicRegs.SCICTL1.bit.TXENA = 1;			// SCI ���ű�� Enable


	AcgUsart_FIFOSetting(USART_2);


	ScicRegs.SCICTL1.bit.SWRESET = 1;		// SCI ����Ʈ���� ���� ����

	PieCtrlRegs.PIEIER8.bit.INTx5 = 1;		// PIE ���ͷ�Ʈ(SCIRXINTB) : Enable
	IER |= M_INT8;							// CPU ���ͷ�Ʈ(INT8) : Enable


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


	// SCI Baudrate ����
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


	// SCI�� �۽� FIFO ����
    SCIptr->SCIFFTX.bit.SCIFFENA = 1;		// SCI FIFO ��� ���� Enable
    SCIptr->SCIFFTX.bit.TXFFINTCLR = 1;	// SCI �۽� FIFO ���ͷ�Ʈ �÷��� Ŭ����
    SCIptr->SCIFFTX.bit.TXFIFOXRESET = 1;	// SCI �۽� FIFO RE-enable
    SCIptr->SCIFFTX.bit.SCIRST = 1;		// SCI ���� ����


	// SCI�� ���� FIFO ����
    SCIptr->SCIFFRX.bit.RXFFINTCLR = 1;	// SCI ���� FIFO ���ͷ�Ʈ �÷��� Ŭ����
    SCIptr->SCIFFRX.bit.RXFFIENA = 1;		// SCI ���� FIFO ���ͷ�Ʈ Enable
    SCIptr->SCIFFRX.bit.RXFIFORESET = 1;	// SCI ���� FIFO RE-enable
    SCIptr->SCIFFRX.bit.RXFFIL = 1;		// SCI ���� FIFO ���ͷ�Ʈ ���� ����


}





//============================================================================================
//	Local Interrupt Service Routine : SCI ���� FIFO ���ͷ�Ʈ ���� ��ƾ
//--------------------------------------------------------------------------------------------
//	SCIFFRX ���������� RSFFST�� ���� RXFFIL�� ������ ������ ũ�ų� ������ ����.
//  SCI RXFIFO�� ���ŵ� �����͸� �޷θ��� ������.
//--------------------------------------------------------------------------------------------


interrupt void AcgUsart0_RxISR(void)
{

	rcvCompleteFlag0 = 1;

	SciaRegs.SCIFFRX.bit.RXFIFORESET = 0;		// SCI ���� FIFO ���ͷ�Ʈ Enable
	rx0_Data = SciaRegs.SCIRXBUF.bit.RXDT;


	SCI_RXintCount1++;


	SciaRegs.SCIFFRX.bit.RXFFOVRCLR = 1;			// Clear Overflow flag
	SciaRegs.SCIFFRX.bit.RXFFINTCLR = 1;			// Clear Interrupt flag
	SciaRegs.SCIFFRX.bit.RXFIFORESET = 1;		// SCI ���� FIFO ���ͷ�Ʈ Enable

	PieCtrlRegs.PIEACK.all = PIEACK_GROUP9;			// Acknowledge interrupt to PIE
}


interrupt void AcgUsart1_RxISR(void)
{
	rcvCompleteFlag1 = 1;

	ScibRegs.SCIFFRX.bit.RXFIFORESET = 0;		// SCI ���� FIFO ���ͷ�Ʈ Enable
	rx1_Data = ScibRegs.SCIRXBUF.bit.RXDT;

	SCI_RXintCount2++;


	ScibRegs.SCIFFRX.bit.RXFFOVRCLR = 1;			// Clear Overflow flag
	ScibRegs.SCIFFRX.bit.RXFFINTCLR = 1;			// Clear Interrupt flag
	ScibRegs.SCIFFRX.bit.RXFIFORESET = 1;		// SCI ���� FIFO ���ͷ�Ʈ Enable
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP9;			// Acknowledge interrupt to PIE
}


interrupt void AcgUsart2_RxISR(void)
{
	rcvCompleteFlag2 = 1;

	ScicRegs.SCIFFRX.bit.RXFIFORESET = 0;		// SCI ���� FIFO ���ͷ�Ʈ Enable
	rx2_Data = ScicRegs.SCIRXBUF.bit.RXDT;

	SCI_RXintCount3++;

	ScicRegs.SCIFFRX.bit.RXFFOVRCLR = 1;			// Clear Overflow flag
	ScicRegs.SCIFFRX.bit.RXFFINTCLR = 1;			// Clear Interrupt flag
	ScicRegs.SCIFFRX.bit.RXFIFORESET = 1;		// SCI ���� FIFO ���ͷ�Ʈ Enable
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP8;			// Acknowledge interrupt to PIE
}
//============================================================================================



//����� Ȱ�� �Լ�
void AcgUSART0_txc(char c)      //char �۽� �Լ�  (channel , ���� ����)
{
	// ���� �����Ͱ� ���� ���� ��� ���� ������ ��ٸ���.
	while(SciaRegs.SCIFFTX.bit.TXFFST != 0);

	// �޸𸮿� ����� �����͸� SCI�� ����
	SciaRegs.SCITXBUF = (Uint16)(c & 0x00FF);
}

void AcgUSART1_txc(char c)
{
	// ���� �����Ͱ� ���� ���� ��� ���� ������ ��ٸ���.
	while(ScibRegs.SCIFFTX.bit.TXFFST != 0);

	// �޸𸮿� ����� �����͸� SCI�� ����
	ScibRegs.SCITXBUF = (Uint16)(c & 0x00FF);
}

void AcgUSART2_txc(char c)
{
	// ���� �����Ͱ� ���� ���� ��� ���� ������ ��ٸ���.
	while(ScicRegs.SCIFFTX.bit.TXFFST != 0);

	// �޸𸮿� ����� �����͸� SCI�� ����
	ScicRegs.SCITXBUF = (Uint16)(c & 0x00FF);
}

char AcgUSART0_rxc()             //char ���� �Լ�  (channel)   return ������ ����
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






