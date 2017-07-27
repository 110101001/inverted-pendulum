#ifndef __Encoder_H__
#define __Encoder_H__
#include "sys.h"

#define SEC_PER_CLK 0.000001
#define ARC_PER_PLS 360/390.0

void TIM5_Configuion(void);
void Quad_Encoder_Configuration(void);
void Encoder_Start1(void);
int32_t GetQuadEncoderDiff1(void);  
void TIM4_IRQHandler(void);
void TIM2_IRQHandler(void);
long int Get_time(void);
void Get_speed(void);
#endif
