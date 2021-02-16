#ifndef __GIMBAL_CONTROL_TASK_H
#define __GIMBAL_CONTROL_TASK_H

/* 包含头文件 ---------------------------------------------------------------*/
#include "myinclude.h"
/* 本模块向外部提供的宏定义 -------------------------------------------------*/

/* 本模块向外部提供的结构体/枚举定义 ----------------------------------------*/
typedef struct
{                     //RC的结构体在哪定义的？  ---遥控器数据结构体在Remote_control.h中定义的属于Remote_control.c在通信模块层
	uint8_t gimbal_mode;
	uint8_t gimbal_flag;
	uint8_t remote_mode;
	uint8_t minipc_mode;
	uint8_t minipc_color;   //视觉需要的颜色信息
	uint8_t bopan_mode;
	uint8_t bopan_lastmode;
	uint8_t bopan_flag;     //拨盘反转标志位
}Gimbal_Status_t;    

typedef struct{
		int32_t expect;      //最终PID运算值
		uint8_t	step;
		uint8_t mode;
		int32_t expect_pc;  //视觉设定值
    	int16_t err;
} Pos_Set;
/* 本模块向外部提供的变量声明 -----------------------------------------------*/
extern Gimbal_Status_t Gimbal_status;
extern Pos_Set  yaw_set;
extern Pos_Set  yaw_tly_set;
extern Pos_Set  pit_set;
/* 本模块向外部提供的自定义数据类型变量声明 ---------------------------------*/

/* 本模块向外部提供的接口函数原型声明 ---------------------------------------*/







#endif

