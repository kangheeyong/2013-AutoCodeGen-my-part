
#include <stdio.h>

#define MENU  'z'
#define GPIO  '1'
#define EXTI  '2'
#define TIMER '3'
#define PWM   '4'
#define ADC   '5'
#define HIGH_VALUE   1
#define LOW_VALUE    0

extern volatile unsigned char keyData;  // ����ڰ� �Է� ���� key �� 
extern volatile unsigned char EXTI_flag[8];  // EXTI Pin�� ����
extern volatile unsigned int timerNum;  // Timer���� �̿�Ǵ� ���� 
extern volatile unsigned int timerFlag;

extern volatile char rcvCompleteFlag0;  
extern volatile char rx0_Data;


char AcgUSART0_rxc_NoWaiting(); // USART ���� �Լ� (���� �ð� ������ ���� �޴� ���� ��ٸ���)

int put_char(char c, FILE *stream); //printf ��� �����ϰ� ���ִ� �Լ�


//Display �Լ�
void printMenu();
void clearDisplay();
void printGPIO();
void printEXTI();
void printTIMER();
void printPWM();
void printADC();
void printStateOfEXTI(int i);  // EXTI�� ����(HIGH or LOW)�� ���


//Test �Լ�
void GPIO_Test();
void EXTI_Test();
void TIMER_Test();
void PWM_Test();
void ADC_Test();



//Timer ���� �Լ�
void timerFunction();




