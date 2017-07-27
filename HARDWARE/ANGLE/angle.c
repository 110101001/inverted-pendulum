#include "angle.h"

float read_180;

void angle_calibration(void){
	 read_180=Get_Adc_Average(5,5);
}
float get_angle(void){
	float angle;
	angle=Get_Adc_Average(5,3);
	angle=(angle-read_180)*ANGLE_CONST+180;
	if(angle>360) angle-=360;
	if(angle<0) angle+=360;
	//angle=(((angle-read_0)*ANGLE_CONST)<-180)?(angle-read_0)*ANGLE_CONST+360:(angle-read_0)*ANGLE_CONST;
	return angle;
}
