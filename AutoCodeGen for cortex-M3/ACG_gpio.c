#include "stm32f10x.h"
#include "ACG_gpio.h"


void AcgGPIO_OutputSetting(GpioPort GPIOx ,UINT16 GPIO_Pin) //GPIO 출력etting
{
    GPIO_InitTypeDef GPIO_InitStructure;

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;    
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  
    
    if(GPIOx == GPIO_A )      //PORTA  PA0 ~ PA15
    {
      RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); 
      GPIO_Init(GPIOA, &GPIO_InitStructure);
    }
    else if(GPIOx == GPIO_B ) //PORTB  PB0 ~ PB15
    {
      RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); 
      GPIO_Init(GPIOB, &GPIO_InitStructure);
    }
    else if(GPIOx == GPIO_C ) //PORTC  PC0 ~ PC15
    {
      RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE); 
      GPIO_Init(GPIOC, &GPIO_InitStructure);
    }
    else if(GPIOx == GPIO_D ) //PORTD  PD0 ~ PD15
    {
      RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE); 
      GPIO_Init(GPIOD, &GPIO_InitStructure);
    }
    else if(GPIOx == GPIO_E ) //PORTE  PE0 ~ PE15
    {
      RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE); 
      GPIO_Init(GPIOE, &GPIO_InitStructure);
    }
    else if(GPIOx == GPIO_F ) //PORTF  PF0 ~ PF15
    {
      RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOF, ENABLE); 
      GPIO_Init(GPIOF, &GPIO_InitStructure);
    }
    else if(GPIOx == GPIO_G ) //PORTG  PG0 ~ PG15
    {
      RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOG, ENABLE); 
      GPIO_Init(GPIOG, &GPIO_InitStructure);
    }
}

void AcgGPIO_InputSetting(GpioPort GPIOx ,UINT16 GPIO_Pin) //GPIO 입력etting
{
    GPIO_InitTypeDef GPIO_InitStructure;

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin;   
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;  
    
    if(GPIOx == GPIO_A )      //PORTA  PA0 ~ PA15
    {
      RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); 
      GPIO_Init(GPIOA, &GPIO_InitStructure);
    }
    else if(GPIOx == GPIO_B ) //PORTB  PB0 ~ PB15
    {
      RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); 
      GPIO_Init(GPIOB, &GPIO_InitStructure);
    }
    else if(GPIOx == GPIO_C ) //PORTC  PC0 ~ PC15
    {
      RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE); 
      GPIO_Init(GPIOC, &GPIO_InitStructure);
    }
    else if(GPIOx == GPIO_D ) //PORTD  PD0 ~ PD15
    {
      RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE); 
      GPIO_Init(GPIOD, &GPIO_InitStructure);
    }
    else if(GPIOx == GPIO_E ) //PORTE  PE0 ~ PE15
    {
      RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE); 
      GPIO_Init(GPIOE, &GPIO_InitStructure);
    }
    else if(GPIOx == GPIO_F ) //PORTF  PF0 ~ PF15
    {
      RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOF, ENABLE); 
      GPIO_Init(GPIOF, &GPIO_InitStructure);
    }
    else if(GPIOx == GPIO_G ) //PORTG  PG0 ~ PG15
    {
      RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOG, ENABLE); 
      GPIO_Init(GPIOG, &GPIO_InitStructure);
    }
}


void AcgGPIO_OutPort(GpioPort GPIOx, UINT16 GPIO_Pin) //PORTx에 GPIO_Pin(0x0000~ 0xFFFF)을 출력
{
    if(GPIOx == GPIO_A )        //PORTA  PA0 ~ PA15
    {
      GPIOA->ODR = GPIO_Pin;
    }
    else if(GPIOx == GPIO_B )   //PORTB  PB0 ~ PB15
    {
      GPIOB->ODR = GPIO_Pin;
    }
    else if(GPIOx == GPIO_C )   //PORTC  PC0 ~ PC15
    {
      GPIOC->ODR = GPIO_Pin;
    }
    else if(GPIOx == GPIO_D )   //PORTD  PD0 ~ PD15
    {
      GPIOD->ODR = GPIO_Pin;
    }
    else if(GPIOx == GPIO_E )   //PORTE  PE0 ~ PE15
    {
      GPIOE->ODR = GPIO_Pin;
    }
    else if(GPIOx == GPIO_F )   //PORTF  PF0 ~ PF15
    {
      GPIOF->ODR = GPIO_Pin;
    }
    else if(GPIOx == GPIO_G )   //PORTG  PG0 ~ PG15
    {
      GPIOG->ODR = GPIO_Pin;
    } 
}
void AcgGPIO_OutPin(GpioPort GPIOx,uint16_t pin, uint8_t data) //PORTx의 pin(0~15) 값을 출력
{
    char GPIO_Pin;

    if(data == 0)
    {
	  GPIO_Pin =  (uint16_t) ~(1<<pin);
    }

    else
    {
	  GPIO_Pin =  (uint16_t) (1<<pin);
    }

    if(data == 0)
    {
          if(GPIOx == GPIO_A )        //PORTA  PA0 ~ PA15
          {
            GPIOA->ODR &= GPIO_Pin;
          }
          else if(GPIOx == GPIO_B )   //PORTB  PB0 ~ PB15
          {
            GPIOB->ODR &= GPIO_Pin;
          }
          else if(GPIOx == GPIO_C )   //PORTC  PC0 ~ PC15
          {
            GPIOC->ODR &= GPIO_Pin;
          }
          else if(GPIOx == GPIO_D )   //PORTD  PD0 ~ PD15
          {
            GPIOD->ODR &= GPIO_Pin;
          }
          else if(GPIOx == GPIO_E )   //PORTE  PE0 ~ PE15
          {
            GPIOE->ODR &= GPIO_Pin;
          }
          else if(GPIOx == GPIO_F )   //PORTF  PF0 ~ PF15
          {
            GPIOF->ODR &= GPIO_Pin;
          }
          else if(GPIOx == GPIO_G )   //PORTG  PG0 ~ PG15
          {
            GPIOG->ODR &= GPIO_Pin;
          } 
    }
    else
    {
          if(GPIOx == GPIO_A )        //PORTA  PA0 ~ PA15
          {
            GPIOA->ODR |= GPIO_Pin;
          }
          else if(GPIOx == GPIO_B )   //PORTB  PB0 ~ PB15
          {
            GPIOB->ODR |= GPIO_Pin;
          }
          else if(GPIOx == GPIO_C )   //PORTC  PC0 ~ PC15
          {
            GPIOC->ODR |= GPIO_Pin;
          }
          else if(GPIOx == GPIO_D )   //PORTD  PD0 ~ PD15
          {
            GPIOD->ODR |= GPIO_Pin;
          }
          else if(GPIOx == GPIO_E )   //PORTE  PE0 ~ PE15
          {
            GPIOE->ODR |= GPIO_Pin;
          }
          else if(GPIOx == GPIO_F )   //PORTF  PF0 ~ PF15
          {
            GPIOF->ODR |= GPIO_Pin;
          }
          else if(GPIOx == GPIO_G )   //PORTG  PG0 ~ PG15
          {
            GPIOG->ODR |= GPIO_Pin;
          } 
    }
  
}
uint16_t AcgGPIO_InPort(GpioPort GPIOx) //PORTx에 입력으로 들어오는 핀값을 반환
{
    if(GPIOx == GPIO_A )         //PORTA  PA0 ~ PA15
    {
      return GPIOA->IDR;
    }
    else if(GPIOx == GPIO_B )    //PORTB  PB0 ~ PB15
    {
      return GPIOB->IDR;
    }
    else if(GPIOx == GPIO_C )    //PORTC  PC0 ~ PC15
    {
      return GPIOC->IDR;
    }
    else if(GPIOx == GPIO_D )    //PORTD  PD0 ~ PD15
    {
      return GPIOD->IDR;
    }
    else if(GPIOx == GPIO_E )    //PORTE  PE0 ~ PE15
    {
      return GPIOE->IDR;
    }
    else if(GPIOx == GPIO_F )    //PORTF  PF0 ~ PF15
    {
      return GPIOF->IDR;
    }
    else if(GPIOx == GPIO_G )    //PORTG  PG0 ~ PG15
    {
      return GPIOG->IDR;
    }
    return 0;
}

uint8_t AcgGPIO_InPin(GpioPort GPIOx,uint16_t pin) //PORTx의 pin(0~15) 값으로 들어오는 핀값을 반환 
{
  if(GPIOx == GPIO_A)            //PORTA  PA0 ~ PA15
	{
	    return (GPIOA->IDR & (1<<pin));
	}

	else if(GPIOx == GPIO_B) //PORTB  PB0 ~ PB15
	{
	    return (GPIOB->IDR & (1<<pin));
	}

	else if(GPIOx == GPIO_C) //PORTC  PC0 ~ PC15
	{
	    return (GPIOC->IDR & (1<<pin));
	}

	else if(GPIOx == GPIO_D) //PORTD  PD0 ~ PD15
	{
	    return (GPIOD->IDR & (1<<pin));
	}

	else if(GPIOx == GPIO_E) //PORTE  PE0 ~ PE15
	{
	    return (GPIOE->IDR & (1<<pin));
	}

	else if(GPIOx == GPIO_F) //PORTF  PF0 ~ PF15
	{
	    return (GPIOF->IDR & (1<<pin));
	}

	else if(GPIOx == GPIO_G)//PORTG  PG0 ~ PG15
	{
	    return (GPIOG->IDR & (1<<pin));
	}
        return 0;
}