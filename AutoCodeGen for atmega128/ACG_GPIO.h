#ifndef GPIO_H
#define GPIO_H

#include <avr/io.h>

 // Pin Map for GPIO 

 //  GPIO_A  : PA0 ~ PA7
 //  GPIO_B  : PB0 ~ PB7
 //  GPIO_C  : PC0 ~ PC7
 //  GPIO_D  : PD0 ~ PD7
 //  GPIO_E  : PE0 ~ PD7
 //  GPIO_F  : PF0 ~ PF7
 //  GPIO_G  : PG0 ~ PG4

#define AcgGPIOOut_A        (*((BitType*)(&PORTA)))
#define AcgGPIOOut_B        (*((BitType*)(&PORTB)))
#define AcgGPIOOut_C        (*((BitType*)(&PORTC)))
#define AcgGPIOOut_D        (*((BitType*)(&PORTD)))
#define AcgGPIOOut_E        (*((BitType*)(&PORTE)))
#define AcgGPIOOut_F        (*((BitType*)(&PORTF)))
#define AcgGPIOOut_G        (*((BitType*)(&PORTG)))

#define AcgGPIOIn_A        (*((BitType*)(&PINA)))
#define AcgGPIOIn_B        (*((BitType*)(&PINB)))
#define AcgGPIOIn_C        (*((BitType*)(&PINC)))
#define AcgGPIOIn_D        (*((BitType*)(&PIND)))
#define AcgGPIOIn_E        (*((BitType*)(&PINE)))
#define AcgGPIOIn_F        (*((BitType*)(&PINF)))
#define AcgGPIOIn_G        (*((BitType*)(&PING)))

#define GPIO_Pin_00		   0x01
#define GPIO_Pin_01		   0x02
#define GPIO_Pin_02		   0x04
#define GPIO_Pin_03		   0x08
#define GPIO_Pin_04		   0x10
#define GPIO_Pin_05		   0x20
#define GPIO_Pin_06		   0x40
#define GPIO_Pin_07		   0x80


struct BITS{
    unsigned char GPIO_00 : 1; 
    unsigned char GPIO_01 : 1;
    unsigned char GPIO_02 : 1;
    unsigned char GPIO_03 : 1;
    unsigned char GPIO_04 : 1;
    unsigned char GPIO_05 : 1;
    unsigned char GPIO_06 : 1;
    unsigned char GPIO_07 : 1;
};

typedef union{
      unsigned char All;
      struct BITS Bit;
}BitType;

//GPIO PORT
typedef enum
{
   GPIO_A, //PA0 ~ PA7
   GPIO_B, //PB0 ~ PB7
   GPIO_C, //PC0 ~ PC7
   GPIO_D, //PD0 ~ PD7
   GPIO_E, //PE0 ~ PD7
   GPIO_F, //PF0 ~ PF7
   GPIO_G  //PG0 ~ PG4

}GPIOPort;


//GPIO 초기화 함수
void AcgGPIO_OutputSetting(GPIOPort GPIOx ,char GPIO_Pin);  //GPIO 출력 Setting
void AcgGPIO_InputSetting(GPIOPort GPIOx ,char GPIO_Pin);   //GPIO 입력 Setting



//GPIO 사용자 활용 함수 
void AcgGPIO_OutPort(GPIOPort GPIOx,char GPIO_Pin);    //PORTx에 GPIO_Pin(0x00~ 0xFF)을 출력
void AcgGPIO_OutPin(GPIOPort GPIOx,int pin, int data); //PORTx의 pin(0~7) 값을 출력 
char AcgGPIO_InPort(GPIOPort GPIOx);                   //PORTx에 입력으로 들어오는 핀값을 반환
int  AcgGPIO_InPin(GPIOPort GPIOx,int pin);            //PORTx의 pin(0~7) 값으로 들어오는 핀값을 반환 




#endif GPIO_H
