#ifndef CTL_H
#define CTL_H

#include "sys.h"
#include "Encoder.h"
#include "motor.h"
#include "pid.h"
#include "math.h"
#include "angle.h"
#include "usart.h"
#include "delay.h"

#define OMEGA 0.00001//���н��ٶ�
//#define SPEED 1//�ڸ˵���ת�ٶ�
#define ENERGY_CONST 2//������������
#define J 0.0003//�ڸ�ת������
#define M 0.0588//mgl

void swing_up(void);
void swing(void);
void rotate(void);
void arm_rotate(void);
void stable(void);

#endif
