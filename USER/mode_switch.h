#ifndef MODE_H
#define MODE_H

#include "sys.h"

#define D0 (GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_0))//1
#define D1 (GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_1))//2
#define D4 (GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_4))//3
#define D3 (GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_3))//8

#define ROTATE (D0==1&&D1==0&&D2==0&&D3==0)
#define SWING_UP (D0==0&&D1==1&&D2==0&&D3==0)
#define STABLE (D0==0&&D1==0&&D2==1&&D3==0)

void MS_Init(void);
void TIM3_IRQHandler(void);

#endif
