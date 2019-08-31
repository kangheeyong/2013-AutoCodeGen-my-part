#ifndef ACG_SYSCLK_H_
#define ACG_SYSCLK_H_

#include "ACG_datatype.h"

 
typedef enum
{
    SYSCLK_16MHz = ((uint32_t)0x00000000),
    SYSCLK_24MHz = ((uint32_t)0x00040000),
    SYSCLK_32MHz = ((uint32_t)0x00080000),
    SYSCLK_40MHz = ((uint32_t)0x000C0000),
    SYSCLK_48MHz = ((uint32_t)0x00100000),
    SYSCLK_56MHz = ((uint32_t)0x00140000),
    SYSCLK_64MHz = ((uint32_t)0x00180000),
    SYSCLK_72MHz = ((uint32_t)0x001C0000)  
}SysClk;

//시스템 클락을 설정하는 함수
void AcgSystemClock_Setting(SysClk clk);

#endif