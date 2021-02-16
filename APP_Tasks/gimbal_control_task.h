#ifndef __GIMBAL_CONTROL_TASK_H
#define __GIMBAL_CONTROL_TASK_H

/* ����ͷ�ļ� ---------------------------------------------------------------*/
#include "myinclude.h"
/* ��ģ�����ⲿ�ṩ�ĺ궨�� -------------------------------------------------*/

/* ��ģ�����ⲿ�ṩ�Ľṹ��/ö�ٶ��� ----------------------------------------*/
typedef struct
{                     //RC�Ľṹ�����Ķ���ģ�  ---ң�������ݽṹ����Remote_control.h�ж��������Remote_control.c��ͨ��ģ���
	uint8_t gimbal_mode;
	uint8_t gimbal_flag;
	uint8_t remote_mode;
	uint8_t minipc_mode;
	uint8_t minipc_color;   //�Ӿ���Ҫ����ɫ��Ϣ
	uint8_t bopan_mode;
	uint8_t bopan_lastmode;
	uint8_t bopan_flag;     //���̷�ת��־λ
}Gimbal_Status_t;    

typedef struct{
		int32_t expect;      //����PID����ֵ
		uint8_t	step;
		uint8_t mode;
		int32_t expect_pc;  //�Ӿ��趨ֵ
    	int16_t err;
} Pos_Set;
/* ��ģ�����ⲿ�ṩ�ı������� -----------------------------------------------*/
extern Gimbal_Status_t Gimbal_status;
extern Pos_Set  yaw_set;
extern Pos_Set  yaw_tly_set;
extern Pos_Set  pit_set;
/* ��ģ�����ⲿ�ṩ���Զ����������ͱ������� ---------------------------------*/

/* ��ģ�����ⲿ�ṩ�Ľӿں���ԭ������ ---------------------------------------*/







#endif

