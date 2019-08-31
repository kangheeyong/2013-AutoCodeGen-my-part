/*
 * ACG_TMS320F28335_GPIO.h
 *
 *  Created on: 2013. 7. 5.
 *      Author: ssm
 */
#ifndef GPIO_H
#define GPIO_H

#include "DSP28x_Project.h"

//	Pin Map for GPIO
//
//  GPIO_A : GPIO_00 ~ GPIO_31
//	GPIO_B : GPIO_32 ~ GPIO_63
//	GPIO_C : GPIO_64 ~ GPIO_87


#define AcgGPIOOut_A        (*((BitType*)(&GpioDataRegs.GPADAT.all)))
#define AcgGPIOOut_B        (*((BitType*)(&GpioDataRegs.GPBDAT.all)))
#define AcgGPIOOut_C        (*((BitType*)(&GpioDataRegs.GPCDAT.all)))

#define AcgGPIOIn_A        (*((BitType*)(&GpioDataRegs.GPADAT.all)))
#define AcgGPIOIn_B        (*((BitType*)(&GpioDataRegs.GPBDAT.all)))
#define AcgGPIOIn_C        (*((BitType*)(&GpioDataRegs.GPCDAT.all)))

#define GPIO_Pin_00		   ((0x00000001) << 0)
#define GPIO_Pin_01		   ((0x00000001) << 1)
#define GPIO_Pin_02		   ((0x00000001) << 2)
#define GPIO_Pin_03		   ((0x00000001) << 3)
#define GPIO_Pin_04		   ((0x00000001) << 4)
#define GPIO_Pin_05		   ((0x00000001) << 5)
#define GPIO_Pin_06		   ((0x00000001) << 6)
#define GPIO_Pin_07		   ((0x00000001) << 7)
#define GPIO_Pin_08		   ((0x00000001) << 8)
#define GPIO_Pin_09		   ((0x00000001) << 9)
#define GPIO_Pin_10		   ((0x00000001) << 10)
#define GPIO_Pin_11		   ((0x00000001) << 11)
#define GPIO_Pin_12		   ((0x00000001) << 12)
#define GPIO_Pin_13		   ((0x00000001) << 13)
#define GPIO_Pin_14		   ((0x00000001) << 14)
#define GPIO_Pin_15		   ((0x00000001) << 15)
#define GPIO_Pin_16		   ((0x00000001) << 16)
#define GPIO_Pin_17		   ((0x00000001) << 17)
#define GPIO_Pin_18		   ((0x00000001) << 18)
#define GPIO_Pin_19		   ((0x00000001) << 19)
#define GPIO_Pin_20		   ((0x00000001) << 20)
#define GPIO_Pin_21		   ((0x00000001) << 21)
#define GPIO_Pin_22		   ((0x00000001) << 22)
#define GPIO_Pin_23		   ((0x00000001) << 23)
#define GPIO_Pin_24		   ((0x00000001) << 24)
#define GPIO_Pin_25		   ((0x00000001) << 25)
#define GPIO_Pin_26		   ((0x00000001) << 26)
#define GPIO_Pin_27		   ((0x00000001) << 27)
#define GPIO_Pin_28		   ((0x00000001) << 28)
#define GPIO_Pin_29		   ((0x00000001) << 29)
#define GPIO_Pin_30		   ((0x00000001) << 30)
#define GPIO_Pin_31		   ((0x00000001) << 31)


struct BITS{
    unsigned long GPIO_00 : 1;
    unsigned long GPIO_01 : 1;
    unsigned long GPIO_02 : 1;
    unsigned long GPIO_03 : 1;
    unsigned long GPIO_04 : 1;
    unsigned long GPIO_05 : 1;
    unsigned long GPIO_06 : 1;
    unsigned long GPIO_07 : 1;
    unsigned long GPIO_08 : 1;
    unsigned long GPIO_09 : 1;
    unsigned long GPIO_10 : 1;
    unsigned long GPIO_11 : 1;
    unsigned long GPIO_12 : 1;
    unsigned long GPIO_13 : 1;
    unsigned long GPIO_14 : 1;
    unsigned long GPIO_15 : 1;
    unsigned long GPIO_16 : 1;
    unsigned long GPIO_17 : 1;
    unsigned long GPIO_18 : 1;
    unsigned long GPIO_19 : 1;
    unsigned long GPIO_20 : 1;
    unsigned long GPIO_21 : 1;
    unsigned long GPIO_22 : 1;
    unsigned long GPIO_23 : 1;
    unsigned long GPIO_24 : 1;
    unsigned long GPIO_25 : 1;
    unsigned long GPIO_26 : 1;
    unsigned long GPIO_27 : 1;
    unsigned long GPIO_28 : 1;
    unsigned long GPIO_29 : 1;
    unsigned long GPIO_30 : 1;
    unsigned long GPIO_31 : 1;
};

typedef union{
      unsigned long All;
      struct BITS Bit;
}BitType;




// GPIO PORT
typedef enum
{
    GPIO_A,  // GPIO_00 ~ GPIO_31
    GPIO_B,  // GPIO_32 ~ GPIO_63
    GPIO_C   // GPIO_64 ~ GPIO_87

}GPIOPort;


// GPIO ����� ���� (���� �Լ����� ���)
typedef enum
{
	INPUT,
	OUTPUT

}GPIODir;  // GPIO ����� ����



//GPIO �ʱ�ȭ �Լ�
void AcgGPIO_OutputSetting(GPIOPort GPIOx ,unsigned long GPIO_Pin);  // GPIO ������� ����
void AcgGPIO_InputSetting(GPIOPort GPIOx ,unsigned long GPIO_Pin);   // GPIO �Է����� ����


//GPIO ����� Ȱ�� �Լ�
void AcgGPIO_OutPort(GPIOPort GPIOx,unsigned long GPIO_Pin); // PORTx�� GPIO_Pin(0x00000000 ~ 0xFFFFFFFF)�� ���
void AcgGPIO_OutPin(GPIOPort GPIOx, int pin, int data);      // PORTx�� pin(0~31)�� data ���� ��� (Portc�� ���  0 ~ 23)
unsigned long AcgGPIO_InPort(GPIOPort GPIOx);                // PORTx�� �Է����� ������ �� ���� ��ȯ
int AcgGPIO_InPin(GPIOPort GPIOx,int GPIO_Pin);              // PORTx�� PINx�� ������  �� ���� ��ȯ


//���� �Լ�
void AcgGPIO_CtrlRgSetting(GPIOPort GPIOx,unsigned long GPIO_Pin,GPIODir dir);   // GPIO control Rg ����    �Ķ���� :  �����  Port , ��� �� , ����� ����
void AcgGPIO_DirSetting(GPIOPort GPIOx,unsigned long GPIO_Pin,GPIODir dir);      // GPIO ����� ���� ����             �Ķ���� :  �����  Port , ��� ��  , ����� ����
void AcgGPIO_MuxSetting(GPIOPort GPIOx,unsigned long n);                         // ���� GPIO�� ��� ����              �Ķ���� :  �����  Port , n���� ��     // n : 0 ~ 31 (Portc�� ���  0 ~ 23)









#endif
