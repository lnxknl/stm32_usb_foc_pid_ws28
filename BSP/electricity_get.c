


#include "electricity_get.h"



uint32_t ADC_VALUE[2] ={0,0};// = 0;
uint32_t LAST_ADC_VALUE[2] ={0,0};// = 0;
//void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc)  //在中断回调函数中读取
//{
//    ADC_VALUE = HAL_ADC_GetValue(&hadc1);  //这样可以不浪费资源，当然放在主函数中读取也行

//}


//将电压转换为电流,单位ma
float calculate_current_I(uint32_t voltage){
	//return (((float)(voltage/4096.0)*5.0) / 0.05) / 50.0;  完整表达式
	return ((float)(voltage/2048.0) * 1000);  
}


//获取电流值
float get_adc_u_value(){
	float adc =  (ADC_VALUE[0] + LAST_ADC_VALUE[0]) /2.0;
	LAST_ADC_VALUE[0]= ADC_VALUE[0];
	return calculate_current_I(adc);
}
//获取电流值
float get_adc_v_value(){
	float adc =  (ADC_VALUE[1] + LAST_ADC_VALUE[1]) /2.0;
	LAST_ADC_VALUE[1]= ADC_VALUE[1];
	return calculate_current_I(adc);
}

//开始adc采样
void start_adc(){
	HAL_ADC_Start_DMA(&hadc1,(uint32_t*)ADC_VALUE,2);
}
	 