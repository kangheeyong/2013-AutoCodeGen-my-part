
#include <stdio.h>

#define MENU  'z'
#define GPIO  '1'
#define EXTI  '2'
#define TIMER '3'
#define PWM   '4'
#define ADC   '5'
#define HIGH_VALUE   1
#define LOW_VALUE    0

extern volatile unsigned char keyData;  // 사용자가 입력 받을 key 값 
extern volatile unsigned char EXTI_flag[8];  // EXTI Pin의 상태
extern volatile unsigned int timerNum;  // Timer에서 이용되는 변수 
extern volatile unsigned int timerFlag;

extern volatile char rcvCompleteFlag0;  
extern volatile char rx0_Data;


char AcgUSART0_rxc_NoWaiting(); // USART 수신 함수 (일정 시간 까지만 수신 받는 값을 기다린다)

int put_char(char c, FILE *stream); //printf 사용 가능하게 해주는 함수


//Display 함수
void printMenu();
void clearDisplay();
void printGPIO();
void printEXTI();
void printTIMER();
void printPWM();
void printADC();
void printStateOfEXTI(int i);  // EXTI의 상태(HIGH or LOW)를 출력


//Test 함수
void GPIO_Test();
void EXTI_Test();
void TIMER_Test();
void PWM_Test();
void ADC_Test();



//Timer 동작 함수
void timerFunction();




