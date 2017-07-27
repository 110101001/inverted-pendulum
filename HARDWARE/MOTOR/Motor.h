#ifndef MOTOR_H
#define MOTOR_H

#include "sys.h"
#include "pwm.h"

#define AIN1 PAout(6)
#define AIN2 PAout(7)

void Motor_Init(void);
void Motor_Set_Current(float C1);

#endif
