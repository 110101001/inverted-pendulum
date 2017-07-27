#ifndef _PWM_H_
#define _PWM_H_
#include "sys.h"

#define PERIOD 1000
#define PSC 71

#define PWM_CH1_DUTY_CYCLE TIM4->CCR3//实际上不是CH1而是CH3

#define PWM_CH1 PBout(8)

void TIM4_PWM_Init(void);

#endif
