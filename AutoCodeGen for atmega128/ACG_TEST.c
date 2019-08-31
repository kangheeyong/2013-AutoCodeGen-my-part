
#include "ACG_TEST.h"
#include "AutoCodeGen.h"
#include <avr/delay.h>

volatile unsigned char keyData;  // 사용자가 입력 받을 key 값 
volatile unsigned char EXTI_flag[8] = {HIGH_VALUE,HIGH_VALUE,HIGH_VALUE,HIGH_VALUE,HIGH_VALUE,HIGH_VALUE,HIGH_VALUE,HIGH_VALUE};  // EXTI Pin의 상태
volatile unsigned int timerNum;  // Timer에서 이용되는 변수 
volatile unsigned int timerFlag;
volatile unsigned char Interrupt_Flag[8] = {0,0,0,0,0,0,0,0};
volatile unsigned char timerNumFlag = 0;





//	EXTI interrupt handler

void EXTI_00_interrupt(void)
{
	Interrupt_Flag[0] = 1;
	

}

void EXTI_01_interrupt(void)
{
	Interrupt_Flag[1] = 1;

}

void EXTI_02_interrupt(void)
{
	Interrupt_Flag[2] = 1;

}

void EXTI_03_interrupt(void)
{
	Interrupt_Flag[3] = 1;

}

void EXTI_04_interrupt(void)
{
	Interrupt_Flag[4] = 1;

}

void EXTI_05_interrupt(void)
{
	Interrupt_Flag[5] = 1;

}

void EXTI_06_interrupt(void)
{
	Interrupt_Flag[6] = 1;

}

void EXTI_07_interrupt(void)
{
	Interrupt_Flag[7] = 1;

}




//	TIMER interrupt handler

void TIMER_03_interrupt(void)
{
	timerFlag = 1;
}




//	printf 사용 가능 함수
int put_char(char c, FILE *stream)
{
	AcgUSART0_txc(c);
	return 0;
      
}



//  GPIO Test Function

void GPIO_Test()
{
    clearDisplay();
	printGPIO();



	 // 모든 Pin을 출력으로 설정 
	AcgGPIO_OutputSetting(GPIO_A,0xFF); 
	AcgGPIO_OutputSetting(GPIO_B,0xFF); 
	AcgGPIO_OutputSetting(GPIO_C,0xFF); 
	AcgGPIO_OutputSetting(GPIO_D,0xFF); 
	AcgGPIO_OutputSetting(GPIO_E,0xFF);
	AcgGPIO_OutputSetting(GPIO_F,0xFF); 
	AcgGPIO_OutputSetting(GPIO_G,0x03); // PORTG : PG0과 PG1을 출력으로 설정




	while(1)
	{

	    keyData = AcgUSART0_rxc();




		if(keyData == '1')      
		{
		    clearDisplay();
			printGPIO();

			// All Pin Set
			AcgGPIO_OutPort(GPIO_A,0xFF);
			AcgGPIO_OutPort(GPIO_B,0xFF);
			AcgGPIO_OutPort(GPIO_C,0xFF);
			AcgGPIO_OutPort(GPIO_D,0xFF);
			AcgGPIO_OutPort(GPIO_E,0xFF);
			AcgGPIO_OutPort(GPIO_F,0xFF);
			AcgGPIO_OutPort(GPIO_G,0x03);
			printf("\n\rAll GPIO Pin is Set !! \n\r");

			keyData = '0';
		
	  
		}

		else if(keyData == '2') 
		{

		    clearDisplay();
			printGPIO();

			// All Pin Clear
			AcgGPIO_OutPort(GPIO_A,0x00);
			AcgGPIO_OutPort(GPIO_B,0x00);
			AcgGPIO_OutPort(GPIO_C,0x00);
			AcgGPIO_OutPort(GPIO_D,0x00);
			AcgGPIO_OutPort(GPIO_E,0x00);
			AcgGPIO_OutPort(GPIO_F,0x00);
			AcgGPIO_OutPort(GPIO_G,0x00);
			printf("\n\rAll GPIO Pin is Clear !! \n\r");
			
			keyData = '0';	

		}

		else if(keyData == 'z') // Go to menu
		{
			// All Pin Clear
			AcgGPIO_OutPort(GPIO_A,0x00);
			AcgGPIO_OutPort(GPIO_B,0x00);
			AcgGPIO_OutPort(GPIO_C,0x00);
			AcgGPIO_OutPort(GPIO_D,0x00);
			AcgGPIO_OutPort(GPIO_E,0x00);
			AcgGPIO_OutPort(GPIO_F,0x00);
			AcgGPIO_OutPort(GPIO_G,0x00);	


		    clearDisplay();
			printMenu();
			keyData = '0';	
			break;
		}

	}

	// All Pin Clear
	AcgGPIO_OutPort(GPIO_A,0x00);
	AcgGPIO_OutPort(GPIO_B,0x00);
	AcgGPIO_OutPort(GPIO_C,0x00);
	AcgGPIO_OutPort(GPIO_D,0x00);
	AcgGPIO_OutPort(GPIO_E,0x00);
	AcgGPIO_OutPort(GPIO_F,0x00);
	AcgGPIO_OutPort(GPIO_G,0x00);	

	AcgGPIO_InputSetting(GPIO_A,0xFF); 
	AcgGPIO_InputSetting(GPIO_B,0xFF); 
	AcgGPIO_InputSetting(GPIO_C,0xFF); 
	AcgGPIO_InputSetting(GPIO_D,0xFF); 
	AcgGPIO_InputSetting(GPIO_E,0xFF);
	AcgGPIO_InputSetting(GPIO_F,0xFF); 
	AcgGPIO_InputSetting(GPIO_G,0xFF);

 

	  
}


//  EXTI Test Function

void EXTI_Test()
{
    int i = 0;
	keyData = '0';

	AcgGPIO_OutputSetting(GPIO_D,0x0F); 
	AcgGPIO_OutputSetting(GPIO_E,0xF0);

	// 모든 EXTI 값을 HIGH로 바꾼다.
	AcgGPIO_OutPin(GPIO_D,0,1);
	AcgGPIO_OutPin(GPIO_D,1,1);
	AcgGPIO_OutPin(GPIO_D,2,1);
	AcgGPIO_OutPin(GPIO_D,3,1);
	AcgGPIO_OutPin(GPIO_E,4,1);
	AcgGPIO_OutPin(GPIO_E,5,1);
	AcgGPIO_OutPin(GPIO_E,6,1);
	AcgGPIO_OutPin(GPIO_E,7,1);


	// 모든 EXTI를 Falling Edge로 설정
	AcgEXTI_Setting(EXTI_00, FALLING);
	AcgEXTI_Setting(EXTI_01, FALLING);
	AcgEXTI_Setting(EXTI_02, FALLING);
	AcgEXTI_Setting(EXTI_03, FALLING);
	AcgEXTI_Setting(EXTI_04, FALLING);
	AcgEXTI_Setting(EXTI_05, FALLING);
	AcgEXTI_Setting(EXTI_06, FALLING);
	AcgEXTI_Setting(EXTI_07, FALLING);



	for(i=0; i<8; i++)
		Interrupt_Flag[i] = 0;




	clearDisplay();
	printEXTI();






	while(1)
	{
	
		

    	keyData = AcgUSART0_rxc_NoWaiting();

		

		if(keyData == '1')
		{

		    EXTI_flag[0] = (~EXTI_flag[0]) &0x01;  // toggle로 상태 변화 
			AcgGPIO_OutPin(GPIO_D,0,EXTI_flag[0]);

			clearDisplay();
			printEXTI();
			keyData = '0';

		}

		if(keyData =='2')
		{

			EXTI_flag[1] = (~EXTI_flag[1]) &0x01;  // toggle로 상태 변화 
			AcgGPIO_OutPin(GPIO_D,1,EXTI_flag[1]);

			clearDisplay();
			printEXTI();
			keyData = '0';

		}

		if(keyData =='3')
		{

			EXTI_flag[2] = (~EXTI_flag[2]) &0x01;  // toggle로 상태 변화 
			AcgGPIO_OutPin(GPIO_D,2,EXTI_flag[2]);

			clearDisplay();
			printEXTI();
			keyData = '0';

		}

		if(keyData =='4')
		{
	
			EXTI_flag[3] = (~EXTI_flag[3]) &0x01;  // toggle로 상태 변화 
			AcgGPIO_OutPin(GPIO_D,3,EXTI_flag[3]);

			clearDisplay();
			printEXTI();
			keyData = '0';

		}

		if(keyData =='5')
		{
	
			EXTI_flag[4] = (~EXTI_flag[4]) &0x01;  // toggle로 상태 변화 
			AcgGPIO_OutPin(GPIO_E,4,EXTI_flag[4]);

			clearDisplay();
			printEXTI();
			keyData = '0';

		}




		if(keyData =='6')
		{
		
			EXTI_flag[5] = (~EXTI_flag[5]) &0x01;  // toggle로 상태 변화 
			AcgGPIO_OutPin(GPIO_E,5,EXTI_flag[5]);

			clearDisplay();
			printEXTI();
			keyData = '0';

		}

		if(keyData =='7')
		{

			EXTI_flag[6] = (~EXTI_flag[6]) & 0x01;  // toggle로 상태 변화 
			AcgGPIO_OutPin(GPIO_E,6,EXTI_flag[6]);

			clearDisplay();
			printEXTI();
			keyData = '0';

		}

		if(keyData =='8')
		{

			EXTI_flag[7] = (~EXTI_flag[7]) & 0x01;  // toggle로 상태 변화 
			AcgGPIO_OutPin(GPIO_E,7,EXTI_flag[7]);

			clearDisplay();
			printEXTI();
			keyData = '0';

		}


	
		if(keyData == 'z')
		{

			clearDisplay();
			printMenu();
			keyData = '0';	

			EIMSK = 0;    //EXTI를 끈다. 
			break;

		}




		for(i=0; i<8; i++)
		{
			if(Interrupt_Flag[i] == 1) //interrupt가 걸렸으면
			{
				clearDisplay();
				printEXTI();

			    printf("\n\rEXTI_0%d interrupt!\n\r",i);
				Interrupt_Flag[i] = 0;
			}
		}
		

	}




}

// Timer Test Function


void TIMER_Test()
{
	timerNum  = 0;
	timerFlag = 0;
	timerNumFlag  = 0;


	clearDisplay();
	printTIMER();


	// 모든 Pin을 출력으로 설정 
	AcgGPIO_OutputSetting(GPIO_A,0xFF); // PORTA : PA0 ~PA7을 출력으로 설정
	
	


	while(1)
	{


		keyData = AcgUSART0_rxc_NoWaiting();


		if(keyData == '1')
		{
			timerNum  = 0;
			timerFlag = 0;

			AcgTIMER3_Setting(500000); // 0.5sec로 설정

			timerNumFlag = 1;
			keyData = '0';

		}

		else if(keyData == '2')
		{
			timerNum  = 0;
			timerFlag = 0;

			AcgTIMER3_Setting(1000000); // 1.0sec로 설정

			timerNumFlag = 2;
			keyData = '0';

		}

		else if(keyData == '3')
		{
			timerNum  = 0;
			timerFlag = 0;

			AcgTIMER3_Setting(2000000); // 2.0sec로 설정

			timerNumFlag = 3;
			keyData = '0';

		}

		else if(keyData == 'z')
		{
			clearDisplay();
			printMenu();
			keyData = '0';	



			AcgGPIO_OutPort(GPIO_A,0x00); 		 //PORTA의 LED off
			AcgGPIO_InputSetting(GPIO_A,0xFF);
			break;
		}


		timerFunction();
			

	

		
		
		
	}


}


void timerFunction()
{
	if(timerFlag)
	{
		if(timerNum%2 == 0)
			AcgGPIO_OutPort(GPIO_A,0xFF);

		else if(timerNum%2 == 1)
			AcgGPIO_OutPort(GPIO_A,0x00);
		
		timerNum++;
		clearDisplay();
		printTIMER();
		printf("%d\n\r" , timerNum);
		timerFlag = 0;

		if(timerNumFlag == 1)
			printf("\n\r0.5sec period\n\r");

		else if(timerNumFlag == 2)
			printf("\n\r1.0sec period\n\r");

		else if(timerNumFlag == 3)
			printf("\n\r2.0sec period\n\r");
	}	

}



// PWM Test Function

void PWM_Test()
{
	clearDisplay();
	printPWM();


	AcgPWM1_Setting(TIMER_01 | TIMER_02 | TIMER_03, 1000); // 주기를 1ms로 설정



	while(1)
	{
		keyData = AcgUSART0_rxc();


		if(keyData == '1')
		{
			AcgPWM1(TIMER_01 | TIMER_02 | TIMER_03, 100);  //duty rate 100%

			clearDisplay();
			printPWM();

			printf("100%% duty rate \n\r");

			keyData == '0';

		}

		else if(keyData == '2')
		{
			AcgPWM1(TIMER_01 | TIMER_02 | TIMER_03, 75);  //duty rate 75%

			clearDisplay();
			printPWM();

			printf("75%% duty rate \n\r");

			keyData == '0';

		}

		else if(keyData == '3')
		{
			AcgPWM1(TIMER_01 | TIMER_02 | TIMER_03, 50);  //duty rate 50%

			clearDisplay();
			printPWM();

			printf("50%% duty rate \n\r");

			keyData == '0';
		}

		else if(keyData == '4')
		{
			AcgPWM1(TIMER_01 | TIMER_02 | TIMER_03, 25);  //duty rate 25%

			clearDisplay();
			printPWM();

			printf("25%% duty rate \n\r");

			keyData == '0';
		}

		else if(keyData == 'z')
		{
			clearDisplay();
			printMenu();



			keyData == '0';

			break;

		}

	}


	

}


//  ADC Test Function 

void ADC_Test()
{
	clearDisplay();
	printADC();

	int ADC_Value = 0;

	AcgADC_Setting();

	while(1)
	{
		keyData = AcgUSART0_rxc_NoWaiting();


		ADC_Value = AcgADC(ADC_00);
		
		clearDisplay();
		printADC();
		printf("ADC Value : %d\n\r",ADC_Value);

		_delay_ms(1000);

		if(keyData == 'z')
		{
			clearDisplay();
			printMenu();

			ADCSRA = 0; //ADC Setting Reset
			keyData == '0';

			break;
		}
	}

}





///////////////////////////////////////////////////////////

///////	 	USART 수신 (일정 시간까지만 기다린다)   ///////

///////////////////////////////////////////////////////////

char AcgUSART0_rxc_NoWaiting()
{
	int i = 0;

	// Wait for data to be received
    while(!rcvCompleteFlag0)
	{
	   i++;

	   if(i>=3)
	   {
			return '0';
	   }

	}
    

	rcvCompleteFlag0 = 0;

    return rx0_Data;



}





/////////////////////////////////////
////////					  ///////
////////   print function     ///////
////////					  /////// 
/////////////////////////////////////





// 화면을 Clear 한다. 
void clearDisplay()
{
	puts("\x1B[2J");
}



void printMenu()
{
	printf("AutoCodeGen AVR Test\n\r\n\r");
	printf("1.GPIO Test\n\r");
	printf("2.External Interrupt Test\n\r");
	printf("3.Timer Test\n\r");
	printf("4.PWM Test\n\r");
	printf("5.ADC Test");
}

void printGPIO()
{
	printf("GPIO Test\n\r");
	printf("1. All GPIO Pin Set \n\r");
	printf("2. All GPIO Pin Clear\n\r");
	printf("z. Go to Menu\n\r");
}

void printEXTI()
{
	printf("Exti Test (Falling Edge)\n\r\n\r");
	printf("Input signal to interrupt pin \n\r");

	printf("1. EXTI_00 : ");
	printStateOfEXTI(0);

	printf("2. EXTI_01 : ");
	printStateOfEXTI(1);

	printf("3. EXTI_02 : ");
	printStateOfEXTI(2);

	printf("4. EXTI_03 : ");
	printStateOfEXTI(3);

	printf("5. EXTI_04 : ");
	printStateOfEXTI(4);

	printf("6. EXTI_05 : ");
	printStateOfEXTI(5);

	printf("7. EXTI_06 : ");
	printStateOfEXTI(6);

	printf("8. EXTI_07 : ");
	printStateOfEXTI(7);

	printf("z. Go to Menu\n\r");

}

// EXTI의 상태(HIGH or LOW)를 출력
void printStateOfEXTI(int i)
{
	// EXTI가 HIGH이면
    if(EXTI_flag[i])  
		printf("HIGH \n\r");

	// EXTI가 LOW이면 
	else             
		printf("LOW \n\r"); 

}

void printTIMER()
{
	printf("TIMER Test\n\r\n\r");
	printf("Select period  \n\r");

	printf("1. 0.5sec period LED toggle \n\r");
	printf("2. 1.0sec period LED toggle \n\r");
	printf("3. 2.0sec perrod LED toggle \n\r");
	printf("z. Go to Menu\n\r\n\r");


}

void printPWM()
{
	printf("PWM Test\n\r\n\r");
	printf("Period : 0.5sec (PB5, PB6)\n\r");
	printf("Select duty rate\n\r");

	printf("1. 100%% duty rate\n\r");
	printf("2. 75%% duty rate\n\r");
	printf("3. 50%% duty rate\n\r");
	printf("4. 25%% duty rate\n\r");
	printf("z. Go to Menu\n\r\n\r");

}

void printADC()
{
	printf("ADC Test\n\r\n\r");
	printf("print ADC value\n\r");
	printf("z. Go to Menu\n\r\n\r");

}



