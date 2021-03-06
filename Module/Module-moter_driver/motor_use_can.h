#ifndef __MOTOR_USE_CAN_H
#define __MOTOR_USE_CAN_H
/* 包含头文件 ---------------------------------------------------------------*/
#include "myinclude.h"

/* 本模块向外部提供的宏定义 -------------------------------------------------*/


/* 本模块向外部提供的结构体/枚举定义 ----------------------------------------*/
typedef enum
{
	CHASSIS_3508MOTOR,
	TRIGGER_2006MOTOR,
	YAW_3508MOTOR,
	PITCH_6020MOTOR,
	
	NUM_OF_MOTOR      //电机的数量
}motor_ID;//电机数据接收结构体对应存储的数组编号

typedef enum
{
	CAN_CHASSIS_3508MOTOR_ID = 0x201,
	CAN_TRIGGER_2006MOTOR_ID = 0x203,
	CAN_YAW_3508MOTOR_ID = 0x205,
	CAN_PITCH_6020MOTOR_ID = 0x206,
	CAN_SEND_REMOTEDATE_ID = 0x110,
	CAN_SEND_REFEREEDATE_ID = 0x120,
	
}CAN_Message_ID;//CAN通信时电机电调对应ID号

typedef struct{
	int16_t	 			speed_rpm;			//转子转速
	int16_t  			real_current; 	//实际转矩电流
	int16_t  			given_current;	//给定转矩电流
	uint8_t  			temperature;		//电机温度
	uint16_t 			angle;					//转子机械角度abs angle range:[0,8191]
	uint16_t 			last_angle;			//上一次转子机械角度
	uint16_t			offset_angle;		//电机上电转子初始机械角度
	int32_t				round_cnt;			//电机转子转动圈数
	int32_t				total_angle;		//电机总转动圈数
	uint8_t				msg_cnt;				//CAN接收数据次数（用于获取电机转子初始角度）
}motor_measure_t;
/* 本模块向外部提供的变量声明 -----------------------------------------------*/

/* 本模块向外部提供的自定义数据类型变量声明 ---------------------------------*/
extern motor_measure_t  motor_get[NUM_OF_MOTOR];

/* 本模块向外部提供的接口函数原型声明 ---------------------------------------*/
HAL_StatusTypeDef Gimbal_Motor6020(CAN_HandleTypeDef * hcan,int16_t yaw,int16_t	pitch);
HAL_StatusTypeDef Gimbal_Motor6020_Disable(CAN_HandleTypeDef * hcan);
HAL_StatusTypeDef Gimbal_Motor6623_Calibration(CAN_HandleTypeDef * hcan);
HAL_StatusTypeDef Chassis_Motor3508( CAN_HandleTypeDef * hcan,int16_t iq1, int16_t iq2, int16_t iq3, int16_t iq4);
HAL_StatusTypeDef Chassis_Motor3508_Disable( CAN_HandleTypeDef * hcan);
HAL_StatusTypeDef Trigger_Motor2006(CAN_HandleTypeDef * hcan,int16_t value);
HAL_StatusTypeDef CAN_Send_RemoteDate( CAN_HandleTypeDef * hcan,int16_t key_v, int16_t rc_ch0, int16_t rc_ch1, uint8_t rc_s1, uint8_t rc_s2);
HAL_StatusTypeDef CAN_Send_RefereeData( CAN_HandleTypeDef * hcan, uint16_t data0, uint16_t data1 , uint16_t data2 ,uint16_t data3);

#endif
