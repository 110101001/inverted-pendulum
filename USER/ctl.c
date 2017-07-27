#include "ctl.h"

extern float w;

pid_struct pid_v={0.1,0,0,{0,0},0,0,0,0,1000};
pid_struct pid_angle={0.008,0,600000,{0,0},0,0,0,0,10};//0.0009 500
pid_struct pid_w={-17,0.0000035,21000,{0,0},0,0,0,0,1000};// 0.000003,19500,
//Æð°Ú
void swing_up(){
	
	
	//	static long int time;
	//float a;
	int a=305;
	int i;
	float angle;
//	u32 time;
//	time=Get_time();
//		while(angle[0]<150||angle[0]>210){
//			a=ENERGY_CONST*(0.5*J*pow((angle[0]-angle[1])/(Get_time()-time),2)+M*(cos(angle[0])-1));
//			pid_v.ref+=a*(Get_time()-time);
//			pid_v.fdb=w;
//			Pid_calc(&pid_v);
//			ANO_DT_Send_Status(ENERGY_CONST*(0.5*J*pow((angle[0]-angle[1])/(Get_time()-time),2)+M*(cos(angle[0])-1)),w,angle[0], 0, 0,0);
//			time=Get_time();
//			angle[1]=angle[0];
//			angle[0]=ANGLE;
//			Get_speed();
//			delay_ms(5);
//		}
	
		//Motor_Set_Current(pid_v.output);
		
//		angle[2]=angle[1];
//		angle[1]=angle[0];
//		if((angle[1]>angle[2]&&angle[1]>angle[0])||(angle[1]<angle[0]&&angle[1]<angle[2])) a=-a;
	
//	
	Motor_Set_Current(a);
	delay_ms(1000);
	Motor_Set_Current(-a);
	delay_ms(300);
	while(angle<140||angle>220) angle=ANGLE;
	
	
//	while(angle[0]<140||angle[0]>220){
//		speed=(angle[0]-angle[1])/(Get_time()-time);
//		if(abs(speed)>1) pid_v.ref=0;
//		else if(speed>0) pid_v.ref=-1;
//		else pid_v.ref=1;
//		Get_speed();
//		pid_v.fdb=w;
//		Pid_calc(&pid_v);
//		Motor_Set_Current(pid_v.output);
//	}
}

void swing(void){
	int a=600;
	int i=0;
	float angle;
	for(i=0;i<20;i++){//		Get_speed();
		
//		a=ENERGY_CONST*(0.5*J*pow(w,2)+M*(cos(ANGLE)-1));
//		pid_v.ref+=a*(Get_time()-time);
//		pid_v.fdb=w;
//		Pid_calc(&pid_v);
//		Motor_Set_Current(pid_v.output);
		
//		angle[2]=angle[1];
//		angle[1]=angle[0];
		angle=ANGLE;
//		if((angle[1]>angle[2]&&angle[1]>angle[0])||(angle[1]<angle[0]&&angle[1]<angle[2])) a=-a;
		Motor_Set_Current(a);
		delay_ms(400);
		a=-a;
	}
	Motor_Set_Current(0);
}
//Ðý×ª
void rotate(){
//		Get_speed();
//		pid_v.ref=sin(OMEGA*Get_time());
//		pid_v.fdb=w;
//		Pid_calc(&pid_v);
	int i=0;
	for(i=0;i<6000;i++){
		Motor_Set_Current(600.0*sin(OMEGA*Get_time()));
		delay_ms(1);
	}
	Motor_Set_Current(0);
}

void arm_rotate(){
	static int angle=0;
	float roll=ANGLE;
	pid_angle.ref=500;
	if(roll<120||roll>240){
				Motor_Set_Current(0);
			}
	if(roll>120&&roll<240)
	{
	angle+=GetQuadEncoderDiff1();
		
	pid_angle.ref=0;
	pid_angle.fdb=angle;
	Pid_calc(&pid_angle);
	
	if(angle<600) pid_w.ref=5;
		else pid_w.ref=pid_angle.output; 
	pid_w.fdb=roll-180;
	Pid_calc(&pid_w);
	
	Motor_Set_Current(pid_w.output);
	ANO_DT_Send_Status(pid_w.fdb,pid_w.ref, angle, pid_w.kp*(pid_w.ref-pid_w.fdb), 0,0);
	}
}
//ÎÈ¶¨
void stable()
{
	static int angle=0;
	float roll=ANGLE;
	if(roll<140||roll>220){
				Motor_Set_Current(0);
			}
	if(roll>140&&roll<220)
	{
	angle+=GetQuadEncoderDiff1();
	
	pid_angle.ref=0;
	pid_angle.fdb=angle;
	Pid_calc(&pid_angle);
	
	pid_w.ref=pid_angle.output;
	pid_w.fdb=roll-180;
	Pid_calc(&pid_w);
	
	Motor_Set_Current(pid_w.output);
	ANO_DT_Send_Status(pid_w.fdb,pid_w.ref, angle, pid_w.kp*(pid_w.ref-pid_w.fdb), pid_w.output,0);
	}
}
