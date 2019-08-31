#ifndef ACG_GPIO_H
#define ACG_GPIO_H

#include "ACG_datatype.h"

 // Pin Map for GPIO 

 //  GPIO_A  : PA0 ~ PA15
 //  GPIO_B  : PB0 ~ PB15
 //  GPIO_C  : PC0 ~ PC15
 //  GPIO_D  : PD0 ~ PD15
 //  GPIO_E  : PE0 ~ PE15
 //  GPIO_F  : PF0 ~ PF15
 //  GPIO_G  : PG0 ~ PG15

#define AcgGpioOut_A        (*((BitType*)(&(GPIOA->ODR))))
#define AcgGpioOut_B        (*((BitType*)(&(GPIOB->ODR))))
#define AcgGpioOut_C        (*((BitType*)(&(GPIOC->ODR))))
#define AcgGpioOut_D        (*((BitType*)(&(GPIOD->ODR))))
#define AcgGpioOut_E        (*((BitType*)(&(GPIOE->ODR))))
#define AcgGpioOut_F        (*((BitType*)(&(GPIOF->ODR))))
#define AcgGpioOut_G        (*((BitType*)(&(GPIOG->ODR))))

#define AcgGpioIn_A        (*((BitType*)(&(GPIOA->iDR))))
#define AcgGpioIn_B        (*((BitType*)(&(GPIOB->iDR))))
#define AcgGpioIn_C        (*((BitType*)(&(GPIOC->iDR))))
#define AcgGpioIn_D        (*((BitType*)(&(GPIOD->iDR))))
#define AcgGpioIn_E        (*((BitType*)(&(GPIOE->iDR))))
#define AcgGpioIn_F        (*((BitType*)(&(GPIOF->iDR))))
#define AcgGpioIn_G        (*((BitType*)(&(GPIOG->iDR))))

#define GPIO_Pin_00		   0x0001
#define GPIO_Pin_01		   0x0002
#define GPIO_Pin_02		   0x0004
#define GPIO_Pin_03		   0x0008
#define GPIO_Pin_04		   0x0010
#define GPIO_Pin_05		   0x0020
#define GPIO_Pin_06		   0x0040
#define GPIO_Pin_07		   0x0080
#define GPIO_Pin_08		   0x0100
#define GPIO_Pin_09		   0x0200
//원래 헤더에 선언되있음
//#define GPIO_Pin_10		   0x0400   
//#define GPIO_Pin_11		   0x0800
//#define GPIO_Pin_12		   0x1000
//#define GPIO_Pin_13		   0x2000
//#define GPIO_Pin_14		   0x4000
//#define GPIO_Pin_15		   0x8000


struct BITS{
    unsigned char GPIO_00 : 1; 
    unsigned char GPIO_01 : 1;
    unsigned char GPIO_02 : 1;
    unsigned char GPIO_03 : 1;
    unsigned char GPIO_04 : 1;
    unsigned char GPIO_05 : 1;
    unsigned char GPIO_06 : 1;
    unsigned char GPIO_07 : 1;
    unsigned char GPIO_08 : 1;
    unsigned char GPIO_09 : 1;
    unsigned char GPIO_10 : 1;
    unsigned char GPIO_11 : 1;
    unsigned char GPIO_12 : 1;
    unsigned char GPIO_13 : 1;
    unsigned char GPIO_14 : 1;
    unsigned char GPIO_15 : 1;
};

typedef union{
      unsigned char All;
      struct BITS Bit;
}BitType;

typedef enum
{
    GPIO_A,   //PA0 ~ PA15
    GPIO_B,   //PB0 ~ PB15
    GPIO_C,   //PC0 ~ PC15 
    GPIO_D,   //PD0 ~ PD15
    GPIO_E,   //PE0 ~ PE15
    GPIO_F,   //PF0 ~ PF15
    GPIO_G    //PG0 ~ PG15
}GpioPort;

//GPIO 초기화 함수
void AcgGPIO_OutputSetting(GpioPort GPIOx ,UINT16 GPIO_Pin);  //GPIO 출력etting
void AcgGPIO_InputSetting(GpioPort GPIOx ,UINT16 GPIO_Pin);   //GPIO 입력etting


//GPIO 사용자 활용 함수 
void AcgGPIO_OutPort(GpioPort GPIOx, UINT16 GPIO_Pin);            //PORTx에 GPIO_Pin(0x0000~ 0xFFFF)을 출력
void AcgGPIO_OutPin(GpioPort GPIOx,uint16_t pin, uint8_t data);   //PORTx의 pin(0~15) 값을 출력 
uint16_t AcgGPIO_InPort(GpioPort GPIOx);                          //PORTx에 입력으로 들어오는 핀값을 반환
uint8_t AcgGPIO_InPin(GpioPort GPIOx,uint16_t pin);               //PORTx의 pin(0~15) 값으로 들어오는 핀값을 반환 

#endif