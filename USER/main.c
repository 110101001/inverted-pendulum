#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "malloc.h" 
#include "Motor.h"
#include "Encoder.h"
#include "angle.h"
#include "ctl.h"
#include "mode_switch.h"


//SD卡 实验 -库函数版本
//STM32F4工程模板-库函数版本
//淘宝店铺：http://mcudev.taobao.com


int main(void)
{ 
	u8 state;	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置系统中断优先级分组2
	delay_init(168);  //初始化延时函数
	uart_init(115200);		//初始化串口波特率为115200
	Motor_Init();
	TIM5_Configuration();
	
	Quad_Encoder_Configuration();
	Encoder_Start1();
	Adc_Init();
	angle_calibration();
	MS_Init();
	
	while(1){ 
		if(D3==0){
			Motor_Set_Current(0);
			while(D3==0);
			state=Get_state();
		}
		switch(state){
		  case 1:
				delay_ms(2000);
				swing();
				break;
			case 2:
				delay_ms(2000);
				rotate();
				break;
			case 3:
				GetQuadEncoderDiff1();
				stable();
				break;
			case 4:
				delay_ms(2000);
				swing_up();
				Motor_Set_Current(0);
				state=3;
				break;
			case 5:
				stable();
				break;
			case 6:
				arm_rotate();
				break;
	  }
	} 
	return 0;
}





