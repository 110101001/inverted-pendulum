#include "pid.h"
#include "usart.h"

#define BYTE0(dwTemp)       ( *( (char *)(&dwTemp)		) )
#define BYTE1(dwTemp)       ( *( (char *)(&dwTemp) + 1) )
#define BYTE2(dwTemp)       ( *( (char *)(&dwTemp) + 2) )
#define BYTE3(dwTemp)       ( *( (char *)(&dwTemp) + 3) )

extern pid_struct pid_w;
extern pid_struct pid_angle;

u8 data_to_send[256];

float absf(float x){return (x>0)?x:-x;}
float ValLimit(float x,float Limit)
{
if (x>Limit)x=Limit;
	else if(x<-Limit)x=-Limit;
	return x;
}
void Pid_calc(pid_struct *pid){
//	pid->output=pid->kp*((pid->ref-pid->fdb)+pid->kd*(pid->err[0]-pid->err[1])/(SEC_PER_CLK*(Get_time()-time))+pid->ki*pid->in);
	pid->output+=(pid->ref-pid->fdb)*pid->kp*(1+pid->ki*(Get_time()-pid->time)+pid->kd/(Get_time()-pid->time))-pid->err[0]*pid->kp*(1+2*pid->kd/(Get_time()-pid->time))+pid->err[1]*pid->kp*pid->kd/(Get_time()-pid->time);
	pid->time=Get_time();
	pid->err[1]=pid->err[0];
	pid->err[0]=pid->ref-pid->fdb;
	pid->output=ValLimit(pid->output,pid->limit);
}

void ANO_DT_Send_Senser(s16 a_x,s16 a_y,s16 a_z,s16 g_x,s16 g_y,s16 g_z,s16 m_x,s16 m_y,s16 m_z)
{
	u8 _cnt=0;
	vs16 _temp;
		u8 sum = 0;
	u8 i;
	data_to_send[_cnt++]=0xAA;
	data_to_send[_cnt++]=0xAA;
	data_to_send[_cnt++]=0x02;
	data_to_send[_cnt++]=0;
	
	_temp = a_x;
	data_to_send[_cnt++]=BYTE1(_temp);
	data_to_send[_cnt++]=BYTE0(_temp);
	_temp = a_y;
	data_to_send[_cnt++]=BYTE1(_temp);
	data_to_send[_cnt++]=BYTE0(_temp);
	_temp = a_z;	
	data_to_send[_cnt++]=BYTE1(_temp);
	data_to_send[_cnt++]=BYTE0(_temp);
	
	_temp = g_x;	
	data_to_send[_cnt++]=BYTE1(_temp);
	data_to_send[_cnt++]=BYTE0(_temp);
	_temp = g_y;	
	data_to_send[_cnt++]=BYTE1(_temp);
	data_to_send[_cnt++]=BYTE0(_temp);
	_temp = g_z;	
	data_to_send[_cnt++]=BYTE1(_temp);
	data_to_send[_cnt++]=BYTE0(_temp);
	
	_temp = m_x;	
	data_to_send[_cnt++]=BYTE1(_temp);
	data_to_send[_cnt++]=BYTE0(_temp);
	_temp = m_y;	
	data_to_send[_cnt++]=BYTE1(_temp);
	data_to_send[_cnt++]=BYTE0(_temp);
	_temp = m_z;	
	data_to_send[_cnt++]=BYTE1(_temp);
	data_to_send[_cnt++]=BYTE0(_temp);
/////////////////////////////////////////
	_temp = 0;	
	data_to_send[_cnt++]=BYTE1(_temp);
	data_to_send[_cnt++]=BYTE0(_temp);	
	
	data_to_send[3] = _cnt-4;
	

	for(i=0;i<_cnt;i++)
		sum += data_to_send[i];
	data_to_send[_cnt++] = sum;
	
	for(i=0;i<_cnt;i++) {
		USART_SendData(USART1,*(data_to_send+i));
		while((USART1->SR&0X40)==0);
	}
}
void ANO_DT_Send_Status(float angle_rol, float angle_pit, float angle_yaw, s32 alt, u8 fly_model, u8 armed)
{
	u8 _cnt=0;
	vs16 _temp;
	vs32 _temp2 = alt;
	u8 sum = 0;
	u8 i;
	data_to_send[_cnt++]=0xAA;
	data_to_send[_cnt++]=0xAA;
	data_to_send[_cnt++]=0x01;
	data_to_send[_cnt++]=0;
	
	_temp = (int)(angle_rol*100);
	data_to_send[_cnt++]=BYTE1(_temp);
	data_to_send[_cnt++]=BYTE0(_temp);
	_temp = (int)(angle_pit*100);
	data_to_send[_cnt++]=BYTE1(_temp);
	data_to_send[_cnt++]=BYTE0(_temp);
	_temp = (int)(angle_yaw*100);
	data_to_send[_cnt++]=BYTE1(_temp);
	data_to_send[_cnt++]=BYTE0(_temp);
	
	data_to_send[_cnt++]=BYTE3(_temp2);
	data_to_send[_cnt++]=BYTE2(_temp2);
	data_to_send[_cnt++]=BYTE1(_temp2);
	data_to_send[_cnt++]=BYTE0(_temp2);
	
	data_to_send[_cnt++] = fly_model;
	
	data_to_send[_cnt++] = armed;
	
	data_to_send[3] = _cnt-4;
	

	for(i=0;i<_cnt;i++)
		sum += data_to_send[i];
	data_to_send[_cnt++]=sum;
	
	for(i=0;i<_cnt;i++) {
		USART_SendData(USART1,*(data_to_send+i));
		while((USART1->SR&0X40)==0);
	}
}

void Usart1_DataPrepare(u8 data)
{
	static u8 RxBuffer[50];
	static u8 _data_len = 0,_data_cnt = 0;
	static u8 state = 0;
	
	if(state==0&&data==0xAA)						//判断帧头
	{
		state=1;
		RxBuffer[0]=data;
	}
	else if(state==1&&data==0xAF)			//帧头
	{
		state=2;
		RxBuffer[1]=data;
	}
	else if(state==2&&data<0XF1)			//帧类型
	{
		state=3;
		RxBuffer[2]=data;
	}
	else if(state==3&&data<50)				//帧长
	{
		state = 4;
		RxBuffer[3]=data;
		_data_len = data;
		_data_cnt = 0;
	}
	else if(state==4&&_data_len>0)		//数据帧
	{
		_data_len--;
		RxBuffer[4+_data_cnt++]=data;
		if(_data_len==0)
			state = 5;
	}
	else if(state==5)								//校验帧
	{
		state = 0;
		RxBuffer[4+_data_cnt]=data;
		Data_Receive_Anl(RxBuffer,_data_cnt+5);
		
	}
	else
		state = 0;

}

void Data_Receive_Anl(u8 *data_buf,u8 num)
{
	u8 sum = 0;
	u8 i;
	for(i=0;i<(num-1);i++)														//求和校验
		sum += *(data_buf+i);
	if(!(sum==*(data_buf+num-1)))		return;						//校验不成功则return
	if(!(*(data_buf)==0xAA && *(data_buf+1)==0xAF))		return;	//帧头校验不成功则return

//		if(*(data_buf+2)==0X02)
//	{
//		if(*(data_buf+4)==0X01)
//		{
//			send_pid1 = 1;
//		}
//		if(*(data_buf+4)==0XA1)	
//		{
//			Para_ResetToFactorySetup();
//		}
//	}
		if(*(data_buf+2)==0X10)								//PID1
    {
					
        pid_angle.kp  = 0.001*( (vs16)(*(data_buf+4)<<8)|*(data_buf+5) );
        pid_angle.ki  = 0.001*( (vs16)(*(data_buf+6)<<8)|*(data_buf+7) );
        pid_angle.kd  = 0.001*( (vs16)(*(data_buf+8)<<8)|*(data_buf+9) );
        pid_w.kp = 0.001*( (vs16)(*(data_buf+10)<<8)|*(data_buf+11) );
        pid_w.ki = 0.001*( (vs16)(*(data_buf+12)<<8)|*(data_buf+13) );
        pid_w.kd = 0.001*( (vs16)(*(data_buf+14)<<8)|*(data_buf+15) );
//        Chassis_arg.kp 	= 0.001*( (vs16)(*(data_buf+16)<<8)|*(data_buf+17) );
//        Chassis_arg.ki 	= 0.001*( (vs16)(*(data_buf+18)<<8)|*(data_buf+19) );
//        Chassis_arg.kd 	= 0.001*( (vs16)(*(data_buf+20)<<8)|*(data_buf+21) );
    }

}
