#include "ACG_GPIO.h"


void AcgGPIO_OutputSetting(GPIOPort GPIOx ,char GPIO_Pin)  //GPIO 출력 Setting
{
    if(GPIOx == GPIO_A)      //PORTA  PA0 ~ PA7
	{
	    DDRA |= GPIO_Pin;
	}

	else if(GPIOx == GPIO_B) //PORTB  PB0 ~ PB7
	{
	    DDRB |= GPIO_Pin;
	}

	else if(GPIOx == GPIO_C) //PORTC  PC0 ~ PC7
	{
	    DDRC |= GPIO_Pin;
	}

	else if(GPIOx == GPIO_D) //PORTD  PD0 ~ PD7
	{
	    DDRD |= GPIO_Pin;
	}

	else if(GPIOx == GPIO_E) //PORTE  PE0 ~ PE7
	{
	    DDRE |= GPIO_Pin;
	}

	else if(GPIOx == GPIO_F) //PORTF  PF0 ~ PF7
	{
	    DDRF |= GPIO_Pin;
	}

	else if(GPIOx == GPIO_G) //PORTG  PG0 ~ PG4
	{
	    DDRG |= GPIO_Pin;
	}

}



void AcgGPIO_InputSetting(GPIOPort GPIOx ,char GPIO_Pin)   //GPIO 입력 Setting
{
      
	if(GPIOx == GPIO_A)      //PORTA  PA0 ~ PA7
	{
	    DDRA &= (~GPIO_Pin);
	}

	else if(GPIOx == GPIO_B) //PORTB  PB0 ~ PB7
	{
	    DDRB &= (~GPIO_Pin);
	}

	else if(GPIOx == GPIO_C) //PORTC  PC0 ~ PC7
	{
	    DDRC &= (~GPIO_Pin);
	}

	else if(GPIOx == GPIO_D) //PORTD  PD0 ~ PD7
	{
	    DDRD &= (~GPIO_Pin);
	}

	else if(GPIOx == GPIO_E) //PORTE  PE0 ~ PE7
	{
	    DDRE &= (~GPIO_Pin);
	}

	else if(GPIOx == GPIO_F) //PORTF  PF0 ~ PF7
	{
	    DDRF &= (~GPIO_Pin);
	}

	else if(GPIOx == GPIO_G) //PORTG  PG0 ~ PG4
	{
	    DDRG &= (~GPIO_Pin);
	}

}



void AcgGPIO_OutPort(GPIOPort GPIOx,char GPIO_Pin) //PORTx에 GPIO_Pin을 출력
{
    
	if(GPIOx == GPIO_A)      //PORTA  PA0 ~ PA7
	{
	    PORTA = GPIO_Pin;
	}

	else if(GPIOx == GPIO_B) //PORTB  PB0 ~ PB7
	{
	    PORTB = GPIO_Pin;
	}

	else if(GPIOx == GPIO_C) //PORTC  PC0 ~ PC7
	{
	    PORTC = GPIO_Pin;
	}

	else if(GPIOx == GPIO_D) //PORTD  PD0 ~ PD7
	{
	    PORTD = GPIO_Pin;
	}

	else if(GPIOx == GPIO_E) //PORTE  PE0 ~ PE7
	{
	    PORTE = GPIO_Pin;
	}

	else if(GPIOx == GPIO_F) //PORTF  PF0 ~ PF7
	{
	    PORTF = GPIO_Pin;
	}

	else if(GPIOx == GPIO_G) //PORTG  PG0 ~ PG4
	{
	    PORTG = GPIO_Pin;
	}

}

void AcgGPIO_OutPin(GPIOPort GPIOx,int pin, int data) //PORTx의 pin(0~7) 값을 출력 
{
    char GPIO_Pin;

	if(data == 0)
	   GPIO_Pin =  (unsigned char) ~(1<<pin);

    else
	   GPIO_Pin =  (unsigned char) (1<<pin);


    if(data == 0)
	{
		if(GPIOx == GPIO_A)      //PORTA  PA0 ~ PA7
		{
		    PORTA &= GPIO_Pin;
		}

		else if(GPIOx == GPIO_B) //PORTB  PB0 ~ PB7
		{
		    PORTB &= GPIO_Pin;
		}

		else if(GPIOx == GPIO_C) //PORTC  PC0 ~ PC7
		{
		    PORTC &= GPIO_Pin;
		}

		else if(GPIOx == GPIO_D) //PORTD  PD0 ~ PD7
		{
		    PORTD &= GPIO_Pin;
		}

		else if(GPIOx == GPIO_E) //PORTE  PE0 ~ PE7
		{
		    PORTE &= GPIO_Pin;
		}

		else if(GPIOx == GPIO_F) //PORTF  PF0 ~ PF7
		{
		    PORTF &= GPIO_Pin;
		}

		else if(GPIOx == GPIO_G) //PORTG  PG0 ~ PG4
		{
		    PORTG &= GPIO_Pin;
		}
         

	}

	else 
	{

		if(GPIOx == GPIO_A)      //PORTA  PA0 ~ PA7
		{
		    PORTA |= GPIO_Pin;
		}

		else if(GPIOx == GPIO_B) //PORTB  PB0 ~ PB7
		{
		    PORTB |= GPIO_Pin;
		}

		else if(GPIOx == GPIO_C) //PORTC  PC0 ~ PC7
		{
		    PORTC |= GPIO_Pin;
		}

		else if(GPIOx == GPIO_D) //PORTD  PD0 ~ PD7
		{
		    PORTD |= GPIO_Pin;
		}

		else if(GPIOx == GPIO_E) //PORTE  PE0 ~ PE7
		{
		    PORTE |= GPIO_Pin;
		}

		else if(GPIOx == GPIO_F) //PORTF  PF0 ~ PF7
		{
		    PORTF |= GPIO_Pin;
		}

		else if(GPIOx == GPIO_G) //PORTG  PG0 ~ PG4
		{
		    PORTG |= GPIO_Pin;
		}


	}




}

char AcgGPIO_InPort(GPIOPort GPIOx) //PORTx에 입력으로 들어오는 핀값을 반환
{
    
	if(GPIOx == GPIO_A)      //PORTA  PA0 ~ PA7
	{
	    return PINA;
	}

	else if(GPIOx == GPIO_B) //PORTB  PB0 ~ PB7
	{
	    return PINB;
	}

	else if(GPIOx == GPIO_C) //PORTC  PC0 ~ PC7
	{
	    return PINC;
	}

	else if(GPIOx == GPIO_D) //PORTD  PD0 ~ PD7
	{
	    return PIND;
	}

	else if(GPIOx == GPIO_E) //PORTE  PE0 ~ PE7
	{
	    return PINE;
	}

	else if(GPIOx == GPIO_F) //PORTF  PF0 ~ PF7
	{
	    return PINF;
	}

	else if(GPIOx == GPIO_G) //PORTG  PG0 ~ PG4
	{
	    return PING;
	}
}



int  AcgGPIO_InPin(GPIOPort GPIOx,int pin)            //PORTx의 pin(0~7) 값으로 들어오는 핀값을 반환 
{

    if(GPIOx == GPIO_A)      //PORTA  PA0 ~ PA7
	{
	    return (PINA & (1<<pin));
	}

	else if(GPIOx == GPIO_B) //PORTB  PB0 ~ PB7
	{
	    return (PINB & (1<<pin));
	}

	else if(GPIOx == GPIO_C) //PORTC  PC0 ~ PC7
	{
	    return (PINC & (1<<pin));
	}

	else if(GPIOx == GPIO_D) //PORTD  PD0 ~ PD7
	{
	    return (PIND & (1<<pin));
	}

	else if(GPIOx == GPIO_E) //PORTE  PE0 ~ PE7
	{
	    return (PINE & (1<<pin));
	}

	else if(GPIOx == GPIO_F) //PORTF  PF0 ~ PF7
	{
	    return (PINF & (1<<pin));
	}

	else if(GPIOx == GPIO_G) //PORTG  PG0 ~ PG4
	{
	    return (PING & (1<<pin));
	}

}
