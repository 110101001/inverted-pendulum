#ifndef PID_H
#define PID_H

#include "sys.h"
#include "Encoder.h"
#include "ctl.h"

typedef struct{
	float kp;
	float ki;
	float kd;
	float err[2];
	float ref;
	float fdb;
	float output;
	u32 time;
	int limit;//Êä³öÏÞ·ù
}pid_struct;


void Data_Receive_Anl(u8 *data_buf,u8 num);
void Pid_calc(pid_struct*);
void Usart1_DataPrepare(u8 data);
void ANO_DT_Send_Senser(s16 a_x,s16 a_y,s16 a_z,s16 g_x,s16 g_y,s16 g_z,s16 m_x,s16 m_y,s16 m_z);
void ANO_DT_Send_Status(float angle_rol, float angle_pit, float angle_yaw, s32 alt, u8 fly_model, u8 armed);
#endif
