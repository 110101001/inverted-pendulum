#include "Motor.h"
void Motor_Init(){
	GPIO_InitTypeDef  GPIO_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);//��ʹ������IO PORTCʱ�� 
		
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7;	 // �˿�����
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT; 		 //�������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
  GPIO_Init(GPIOA, &GPIO_InitStructure);					 //�����趨������ʼ��GPIO 
  GPIO_ResetBits(GPIOA,GPIO_Pin_6|GPIO_Pin_7);	
  TIM4_PWM_Init();
}
void Motor_Set_Current(float C1){ //��Ӧ���1,����999�������ɸ�
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
