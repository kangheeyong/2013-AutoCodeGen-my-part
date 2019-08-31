/*
 * ACG_TMS320F28335_GPIO.c
 *
 *  Created on: 2013. 7. 5.
 *      Author: ssm
 */
#include "ACG_GPIO.h"
#include "DSP28x_Project.h"


void AcgGPIO_OutputSetting(GPIOPort GPIOx ,unsigned long GPIO_Pin)
{

	AcgGPIO_CtrlRgSetting(GPIOx,GPIO_Pin,OUTPUT);

}

void AcgGPIO_InputSetting(GPIOPort GPIOx ,unsigned long GPIO_Pin)
{
	AcgGPIO_CtrlRgSetting(GPIOx,GPIO_Pin,INPUT);
}

void AcgGPIO_CtrlRgSetting(GPIOPort GPIOx,unsigned long GPIO_Pin,GPIODir dir)
{

	unsigned long n = 1;


	 AcgGPIO_DirSetting(GPIOx,GPIO_Pin,dir);   //GPIO 입출력 방향 설정

	    	while(n)
	    	{
	    		//1자리씩 masking하여 검사
	    		//GPIOx를 Output으로 사용할 때
	             if(GPIO_Pin & n)
	             {
	            	  EALLOW;
	            	  AcgGPIO_MuxSetting(GPIOx,n);              //GPXMUX Setting
	            	  EDIS;

	             }

	             n = n << 1; //n을 1bit씩 증가
	    	}

}


void AcgGPIO_DirSetting(GPIOPort GPIOx,unsigned long GPIO_Pin,GPIODir dir)
{
	if(GPIOx == GPIO_A)
	{
		EALLOW;
		GpioDataRegs.GPACLEAR.all = GPIO_Pin;

		//GPIOx를 출력으로 사용
		 if(dir == OUTPUT)
		 	 GpioCtrlRegs.GPADIR.all |=  GPIO_Pin;

		 //GPIOx를 입력으로 사용
		 else if(dir == INPUT)
			 GpioCtrlRegs.GPADIR.all &=  (~GPIO_Pin);

		 EDIS;

	}

	else if(GPIOx == GPIO_B)
	{
		EALLOW;
		GpioDataRegs.GPBCLEAR.all = GPIO_Pin;

		//GPIOx를 출력으로 사용
		 if(dir == OUTPUT)
			 GpioCtrlRegs.GPBDIR.all |=  GPIO_Pin;

		 //GPIOx를 입력으로 사용
		 else if(dir == INPUT)
			 GpioCtrlRegs.GPBDIR.all &=  (~GPIO_Pin);

		 EDIS;
	}

	else if(GPIOx == GPIO_C)
	{
		EALLOW;
		GpioDataRegs.GPCCLEAR.all = GPIO_Pin;

		//GPIOx를 출력으로 사용
		 if(dir == OUTPUT)
			 GpioCtrlRegs.GPCDIR.all |=  GPIO_Pin;

		 //GPIOx를 입력으로 사용
		 else if(dir == INPUT)
			 GpioCtrlRegs.GPCDIR.all &=  (~GPIO_Pin);

		 EDIS;
	}


}


void AcgGPIO_MuxSetting(GPIOPort GPIOx,unsigned long n)
{
	unsigned long one = 1;

	if(n < (one<<16))  //0~15 하위비트 일 경우
	{
		if(GPIOx == GPIO_A)
		{
			//GPAMUX1  GPIOx 00  -> GPIO로 사용
			GpioCtrlRegs.GPAMUX1.all &=  0xFFFFFFFF &  (0 << (n-1)*2 );
			GpioCtrlRegs.GPAMUX1.all &=  0xFFFFFFFF &  (0 << (n-1)*2+1 );
		}

		else if(GPIOx == GPIO_B)
		{
			 //GPAMUX1  GPIOx 00  -> GPIO로 사용
			GpioCtrlRegs.GPBMUX1.all &=  0xFFFFFFFF &  (0 << (n-1)*2 );
			GpioCtrlRegs.GPBMUX1.all &=  0xFFFFFFFF &  (0 << (n-1)*2+1 );

		}

		else if(GPIOx == GPIO_C)
		{
			 //GPAMUX1  GPIOx 00  -> GPIO로 사용
			 GpioCtrlRegs.GPCMUX1.all &=  0xFFFFFFFF &  (0 << (n-1)*2 );
			 GpioCtrlRegs.GPCMUX1.all &=  0xFFFFFFFF &  (0 << (n-1)*2+1 );
		}
	}

	else
	{
		n = (n >> 16);
		if(GPIOx == GPIO_A)
		{
			//GPAMUX1  GPIOx 00  -> GPIO로 사용
			 GpioCtrlRegs.GPAMUX2.all &=  0xFFFFFFFF &  (0 << (n-1)*2 );
			 GpioCtrlRegs.GPAMUX2.all &=  0xFFFFFFFF &  (0 << (n-1)*2+1 );
		}

		else if(GPIOx == GPIO_B)
		{
			 //GPAMUX1  GPIOx 00  -> GPIO로 사용
			 GpioCtrlRegs.GPBMUX2.all &=  0xFFFFFFFF &  (0 << (n-1)*2 );
			 GpioCtrlRegs.GPBMUX2.all &=  0xFFFFFFFF &  (0 << (n-1)*2+1 );

		}

		else if(GPIOx == GPIO_C)
		{
			 //GPAMUX1  GPIOx 00  -> GPIO로 사용
			 GpioCtrlRegs.GPCMUX2.all &=  0xFFFFFFFF &  (0 << (n-1)*2 );
			 GpioCtrlRegs.GPCMUX2.all &=  0xFFFFFFFF &  (0 << (n-1)*2+1 );
		}
	}

}



void AcgGPIO_OutPort(GPIOPort GPIOx,unsigned long GPIO_Pin) //PORTx에 GPIO_Pin(0x00000000 ~ 0xFFFFFFFF)를 출력
{
	EALLOW;
	if(GPIOx == GPIO_A)
	{
		GpioDataRegs.GPADAT.all = GPIO_Pin;
	}

	else if(GPIOx == GPIO_B)
	{
		GpioDataRegs.GPBDAT.all = GPIO_Pin;
	}

	else if(GPIOx == GPIO_C)
	{
		GpioDataRegs.GPCDAT.all = GPIO_Pin;
	}
	EDIS;
}


void AcgGPIO_OutPin(GPIOPort GPIOx, int pin, int data)    //PORTx의 pin(0~31) 값을 출력 (Portc일 경우  0 ~ 23)
{
	unsigned long GPIO_Pin;
	unsigned long one = 1;

	if(data == 0)
		GPIO_Pin = (unsigned long) ~(one << pin);

	else
		GPIO_Pin = (unsigned long) (one << pin);

	EALLOW;

	if(data == 0)
	{
		if(GPIOx == GPIO_A)
		{
			GpioDataRegs.GPADAT.all &= GPIO_Pin;
		}

		else if(GPIOx == GPIO_B)
		{
			GpioDataRegs.GPBDAT.all &= GPIO_Pin;
		}

		else if(GPIOx == GPIO_C)
		{
			GpioDataRegs.GPCDAT.all &= GPIO_Pin;
		}
	}

	else
	{
		if(GPIOx == GPIO_A)
		{
			GpioDataRegs.GPADAT.all |= GPIO_Pin;
		}

		else if(GPIOx == GPIO_B)
		{
			GpioDataRegs.GPBDAT.all |= GPIO_Pin;
		}

		else if(GPIOx == GPIO_C)
		{
			GpioDataRegs.GPCDAT.all |= GPIO_Pin;
		}

	}
	EDIS;

}

unsigned long AcgGPIO_InPort(GPIOPort GPIOx) // PORTx에 입력으로 들어오는 핀 값을 반환
{
	if(GPIOx == GPIO_A)
	{
		return GpioDataRegs.GPADAT.all;
	}

	else if(GPIOx == GPIO_B)
	{
		return GpioDataRegs.GPBDAT.all;
	}

	else if(GPIOx == GPIO_C)
	{
		return GpioDataRegs.GPCDAT.all;
	}

	else
		return 0;


}

int AcgGPIO_InPin(GPIOPort GPIOx,int GPIO_Pin)   //PORTx의 Pinx에 들어오는  핀 값을 반환
{

	unsigned long one = 1;


	if(GPIOx == GPIO_A)
	{
		if((GpioDataRegs.GPADAT.all & (unsigned long)(one << GPIO_Pin)))
			return 1;

		else
			return 0;
	}

	else if(GPIOx == GPIO_B)
	{
		if((GpioDataRegs.GPBDAT.all & (unsigned long)(one << GPIO_Pin)))
			return 1;

		else
			return 0;
	}

	else if(GPIOx == GPIO_C)
	{
		if((GpioDataRegs.GPCDAT.all & (unsigned long)(one << GPIO_Pin)))
			return 1;

		else
			return 0;
	}

	else
		return 0;

}



