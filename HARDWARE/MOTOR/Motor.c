#include "Motor.h"
void Motor_Init(){
	GPIO_InitTypeDef  GPIO_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);//先使能外设IO PORTC时钟 
		
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7;	 // 端口配置
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT; 		 //推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
  GPIO_Init(GPIOA, &GPIO_InitStructure);					 //根据设定参数初始化GPIO 
  GPIO_ResetBits(GPIOA,GPIO_Pin_6|GPIO_Pin_7);	
  TIM4_PWM_Init();
}
void Motor_Set_Current(float C1){ //对应电机1,上限999，可正可负
	int Current1=(int)C1;
	if(Current1>999) Current1=999;
	if(Current1<-999) Current1=-999;
	
	if(Current1==0){
		AIN1=0;
		AIN2=0;
	}
	else if(Current1>0){
		AIN1=1;
		AIN2=0;
		PWM_CH1_DUTY_CYCLE=Current1;
	}
	else if(Current1<0){
		AIN1=0;
		AIN2=1;
		PWM_CH1_DUTY_CYCLE=-Current1;
	}
}
