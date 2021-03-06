/*******************************************************************************
                      版权所有 (C), 2020-,NCUROBOT
 *******************************************************************************
  文 件 名   : motor_use_tim.c
  版 本 号   : V1.0
  作    者   : NCURM
  生成日期   : 2018年7月
  最近修改   : 2020.11.28
  功能描述   : 电机库模块中使用TIM进行控制的电机【PWM初始化、比较值设定】
  函数列表   : 1) TIM_Compare_Value_Set()				   【内部调用】
							 2) Shoot_Firction_Motor()				   【外部调用：使用处】
							 3) Shoot_Firction_Motor_Stop()	     【外部调用：使用处】
							 4) Snail_PWM_Init()								 【外部调用：bsp.c】 改为了Shoot_Firction_Motor_PWM_Init(void)  
*******************************************************************************/
/* 包含头文件 ----------------------------------------------------------------*/
#include "motor_use_tim.h"

/* 内部宏定义 ----------------------------------------------------------------*/
#define PWM_htim  htim5
/* 内部自定义数据类型的变量 --------------------------------------------------*/

/* 内部变量 ------------------------------------------------------------------*/

/* 内部函数原型声明 ----------------------------------------------------------*/
void TIM_Compare_Value_Set(uint32_t value1,uint32_t value2);

/* 函数主体部分 --------------------------------------------------------------*/
/*
TIM4：通道1-通道4对应 -> PD12/PD13/PD14/PD15
TIM5：通道1-通道4对应 -> PH10/PH11/PH12/PI0
目前只使用TIM5通道1与通道2，其余均完成测试但未使用到。
*/
/**
  * @brief				TIM捕获/比较寄存器的预装载值设定
  * @param[out]		
  * @param[in]		value1：通道CC1的值。value2：通道CC2的值									
  * @retval				
*/
void TIM_Compare_Value_Set(uint32_t value1,uint32_t value2)
{
	  PWM_htim.Instance->CCR1=value1;
	  PWM_htim.Instance->CCR2=value2;
}

/**
  * @brief				摩擦轮电机驱动函数（通过设定比较值进而进行设定转速）
  * @param[out]		
  * @param[in]		两轮转速:wheel1；wheel2
  * @retval				
*/
void Shoot_Firction_Motor(uint32_t wheel1,uint32_t wheel2)  //有一个疑问 为什么声明出形参和此处不一致
{
  TIM_Compare_Value_Set(wheel1,wheel2);
}

/**
  * @brief				摩擦轮电机停止函数（不常用，一般通过将比较值设定为最低电机即可停转）
  * @param[out]		
  * @param[in]		
  * @retval				none
*/
void Shoot_Firction_Motor_Stop(void)
{
	
	PWM_htim.Instance->CR1 &= ~(0x01);  //关闭定时器
		
}

/**
  * @brief				摩擦轮电机初始化函数
  * @param[out]		
  * @param[in]		
  * @retval				none
*/
void Shoot_Firction_Motor_PWM_Init(void)          //在程序一开始就初始化？
{
	__HAL_TIM_ENABLE(&PWM_htim);									//开启定时器
	HAL_TIM_PWM_Start(&PWM_htim,TIM_CHANNEL_1);   //PH10,右侧摩擦轮(TIM5)
	HAL_TIM_PWM_Start(&PWM_htim,TIM_CHANNEL_2);   //PH11,左侧摩擦轮(TIM5)
	Shoot_Firction_Motor (HIGH_SPEED,HIGH_SPEED);
	HAL_Delay(2000);
	Shoot_Firction_Motor (LOW_SPEED,LOW_SPEED);
	HAL_Delay(1000);   
	}     /*CW:初始化函数主要是为了设置最大行程*/
	//CW：HIHG_SPEED 200 LOW_SPEED 100  ARR = 2000 PSC = 839  84M/8400 = 10000
	//该模块主要完成了snail电机的初始化过程，也即调整最大行程