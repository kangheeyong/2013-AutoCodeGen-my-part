#include "ACG_ADC.h"


//ADC �ʱ�ȭ �Լ�
void AcgADC_Setting()
{
    // ADEN : ADC Enable  
	// ADPS2 : ADPS1 : ADPS0  
	//   1   :   1   :   1  , 16MHz  prescaler 1/128 
    ADCSRA = (1 << ADEN) | (1 <<ADPS2 ) | (1 << ADPS1) | (1 << ADPS0); 
    _delay_ms(5); 
}

//ADC ��ȯ ���� ��ȯ�ϴ� �Լ� 
int AcgADC(ADCChannel ch)
{
    //select channel : ADC0 ~ ADC7
    ADMUX = ch;


    ADCSRA = 0xC7; //ADEN = 1, ADSC = 1   ADSC : ADC Start Conversion 
  
	
	//waiting for ADC conversion
    while((ADCSRA & (1 << ADIF)) == 0);  // ADIF : ADC Interrupt Flag

    ADCSRA |=   (1 << ADIF) ;  // ADIF clear


    _delay_ms(5);


	
    return (int)ADCL + ((int)ADCH<<8);  //ADC ��ȯ �� ��ȯ
}

