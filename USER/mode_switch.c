#include "mode_switch.h"

void MS_Init(void){
	GPIO_InitTypeDef  GPIO_InitStructure;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_4|GPIO_Pin_3;	 // 端口配置
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN; 		 
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
  GPIO_Init(GPIOD, &GPIO_InitStructure);					 //根据设定参数初始化GPIO 
}

u8 Get_state(){
	return D4*4+D1*2+D0*1;
}