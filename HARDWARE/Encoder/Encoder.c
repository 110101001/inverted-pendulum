#include "Encoder.h"
//这个文件中建立一个系统时钟
//encoder.INPUT_B---PB4(TIM3_CH1)
//encoder.INPUT_A---PB5(TIM3_CH2)
float w;
float timer_count=0;

void TIM5_Configuration(void)
{
	  NVIC_InitTypeDef NVIC_InitStructure;
    TIM_TimeBaseInitTypeDef tim;
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5,ENABLE);
    tim.TIM_Period = 0xFFFFFFFF;
    tim.TIM_Prescaler = 84-1;	 //1M 的时钟  
    tim.TIM_ClockDivision = TIM_CKD_DIV1;	
    tim.TIM_CounterMode = TIM_CounterMode_Up;  
    TIM_ARRPreloadConfig(TIM5, ENABLE);	
    TIM_TimeBaseInit(TIM5, &tim);
	
	TIM_ITConfig
	(  //使能或者失能指定的TIM中断
		TIM5, //TIM5
		TIM_IT_Update ,
		ENABLE  //使能
		);
	
		NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQn;  //TIM5中断
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //先占优先级0级
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //从优先级3级
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
		NVIC_Init(&NVIC_InitStructure);  

    TIM_Cmd(TIM5,ENABLE);	
}

void Quad_Encoder_Configuration(void)
{
  GPIO_InitTypeDef gpio;

  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

	gpio.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
  gpio.GPIO_Speed = GPIO_Speed_100MHz;
	gpio.GPIO_Mode = GPIO_Mode_AF;
	gpio.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOA,&gpio);
	
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource1,GPIO_AF_TIM2);
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource0,GPIO_AF_TIM2);
	
  TIM_EncoderInterfaceConfig(TIM2, TIM_EncoderMode_TI12, TIM_ICPolarity_Falling, TIM_ICPolarity_Falling);
 
  TIM_Cmd(TIM2,ENABLE);	 
}

void Encoder_Start1(void)
{
    TIM2->CNT = 0x7FFF;
}

static char Encoder_Dir1 = 0;
  
int32_t GetQuadEncoderDiff1(void)
{
    int32_t cnt = 0;    
    cnt = TIM2->CNT-0x7fff;
    TIM2->CNT = 0x7fff;    
    if(Encoder_Dir1 == 1)
	{
		return cnt;	
	}
	else
	{
		return -cnt;            
	}
}


void TIM5_IRQHandler(void){
	if (TIM_GetITStatus(TIM5, TIM_IT_Update) != RESET){
		timer_count++;
	}
	TIM_ClearITPendingBit(TIM5, TIM_IT_Update  );
}

void TIM2_IRQHandler(void){
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET){
	}
	TIM_ClearITPendingBit(TIM2, TIM_IT_Update  );
}
//获取系统时间
long int Get_time(){
	return TIM5->CNT;
}
//获取电机速度
void Get_speed(){
	static long int time;
	w=ARC_PER_PLS*GetQuadEncoderDiff1()/(SEC_PER_CLK*(Get_time()-time));
	//w2=ARC_PER_PLS*GetQuadEncoderDiff2()/(SEC_PER_CLK*(Get_time()-time));
	time = Get_time();
}
