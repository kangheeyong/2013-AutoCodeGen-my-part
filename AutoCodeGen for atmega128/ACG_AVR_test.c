// S/W Environment : AVR Studio + WINAVR Compiler
// Target : M128
// Crystal: 16Mhz
//
// Made by chowk.
// UART Communication test


#include "AutoCodeGen.h"
#include "ACG_TEST.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>


int main (void)
{

	 keyData = MENU; //사용자가 입력 받을 키 값

    //Usart0 Setting
	AcgUSART0_Setting(BAUDRATE_19200,WORDLENGTH_8,STOPBIT_1,PARITY_NONE);


	//printf 사용 가능하게 한다.
	fdevopen(put_char,0);   

	printMenu();
	

    AcgGPIOOut_A.All = GPIO_Pin_00;
	AcgGPIOOut_B.Bit.GPIO_00 = 1;



	while(1)
	{
		
	
	      keyData = AcgUSART0_rxc();


		  if(keyData == MENU)
		  {
		      printMenu();
		  }

	      else if(keyData == GPIO)
		  {

		      GPIO_Test();
			  keyData = '0';	

		  }
	   
		  else if(keyData == EXTI)
		  {
		  	 EXTI_Test();
		     keyData = '0';	

		  }

		  else if(keyData == TIMER)
		  {
		  	 TIMER_Test();
		     keyData = '0';	

		  }

		  else if(keyData == PWM)
		  {
		  	 PWM_Test();
		     keyData = '0';	

		  }

		  else if(keyData == ADC)
		  {
			 ADC_Test();
		     keyData = '0';	

		  }
   

	}

	return 0;
}

