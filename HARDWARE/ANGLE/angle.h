#ifndef __ANGLE_H__
#define __ANGLE_H__
#include "sys.h"
#include "adc.h"

#define ANGLE_CONST 0.08789
#define ANGLE get_angle()
#define BIAS 2.3

void angle_calibration(void);
float get_angle(void);

#endif
