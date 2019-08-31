#include "stm32f10x.h"
#include "ACG_i2c.h"



void AcgI2C1_setting(BitRate bitRate)
{
    I2C_InitTypeDef I2C_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;

    
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE); 
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    
    //GPIO 환경설정
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7; 
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
 
    //I2C 환경 설정
    I2C_InitStructure.I2C_ClockSpeed =  bitRate;                                                 
    I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;               
    I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;              
    I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;                 
    I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
    I2C_InitStructure.I2C_OwnAddress1 = 0x00;

    I2C_Init(I2C1, &I2C_InitStructure);
   
    I2C_Cmd(I2C1, ENABLE);
}
void AcgI2C2_setting(BitRate bitRate)
{
    I2C_InitTypeDef I2C_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;

    
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C2, ENABLE); 
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    //GPIO 환경설정
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11; 
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    
    //I2C 환경 설정
    I2C_InitStructure.I2C_ClockSpeed = bitRate;                                                 
    I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;               
    I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;              
    I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;                 
    I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
    I2C_InitStructure.I2C_OwnAddress1 = 0x00;

    I2C_Init(I2C2, &I2C_InitStructure);
   
    
    I2C_Cmd(I2C2, ENABLE);
}
