#include "ACG_EXTI.h"



// 외부 인터럽트 settinrg ( 몇번 interrupt , trigger 방식)
void AcgEXTI_Setting(EXTIChannel ch, TriggerType Trigger)
{
    unsigned char exit_temp = 0x01;
	SREG &= (~0x80); // global Interrupt disable 
    
    exit_temp<<=ch;
    
    EIMSK |= exit_temp;  //External interrupt Mask register

    if(ch > 3)  //EICAB 상위 4bit
    {     
        ch -= 4;
        exit_temp = (unsigned char)Trigger;
        exit_temp<<= 2*ch;

        //Interrupt Trigger mode setting
        EICRB |= exit_temp;  
    }
    else        //EICRA 하위 4bit
    {
		exit_temp = (unsigned char)Trigger;
		exit_temp<<= 2*ch;

		//Interrupt Trigger mode setting
		EICRA |= exit_temp;  
    } 

    SREG |= 0x80; //global Interrupt enable
}



//External Interrupt vector

ISR(INT0_vect)
{
	EXTI_00_interrupt();
}

ISR(INT1_vect)
{
	EXTI_01_interrupt();
}

ISR(INT2_vect)
{
	EXTI_02_interrupt();
}

ISR(INT3_vect)
{
	EXTI_03_interrupt();
}

ISR(INT4_vect)
{
	EXTI_04_interrupt();
}

ISR(INT5_vect)
{
	EXTI_05_interrupt();
}

ISR(INT6_vect)
{
	EXTI_06_interrupt();
}

ISR(INT7_vect)
{
	EXTI_07_interrupt();
}
