#ifndef  __SHOOT_FRICTION_TASK_H
#define  __SHOOT_FRICTION_TASK_H
/* ����ͷ�ļ� ---------------------------------------------------------------*/
#include "myinclude.h"
#include "user_lib.h"

/* ��ģ�����ⲿ�ṩ�ĺ궨�� -------------------------------------------------*/
#define SHOOT_FRIC_PWM_ADD_VALUE    5.0f
//CW:
#define GUN_PERIOD  10
#define Mocha_PERIOD  10
#define BLOCK_TIME 4000
#define REVERSE_TIME 2000
#define DELAY_TIME  100

#define Limit_switch_Control 0    

#define Mocha_Stop         0
#define Mocha_danfa_mode   1
#define Mocha_Duofa_mode   2
#define Mocha_Lianfa_mode  3

#define bopan_Stop          0
#define bopan_danfa_mode    1
#define bopan_Duofa_mode    2
#define bopan_Lianfa_mode   3
#define bopan_shangdan_mode 4
#define bopan_guodu_mode    5
#define bopan_fanzhuan_mode 10

/* ��ģ�����ⲿ�ṩ�Ľṹ��/ö�ٶ��� ----------------------------------------*/
typedef struct
{
		ramp_function_source_t fric1_ramp;  //б�º����к��ô���
		ramp_function_source_t fric2_ramp;
	
} shoot_control_t;	

//CW:
typedef struct 
{
	uint8_t remote_mode;     
	uint8_t limit_flag;            
  uint8_t limit_level;      
	uint8_t last_limit_level; 
	uint16_t cnt;              
	uint16_t last_cnt;       
	uint16_t danfa_cnt;       
	float val;
  uint16_t heat_forecast;
 }Shoot_status_t;

 typedef struct Heat_Gun_t
{
	int16_t  shted_bullet;
	int16_t limt_bullet;
	int16_t last_limt_bullet;
	uint16_t limt_heat;
	uint16_t rel_heat;
	uint16_t last_rel_heat;
	float    remain_power;
	uint8_t  limt_spd;
	uint8_t  roboLevel;
	uint8_t  sht_flg;
	uint8_t  stop_flg;
	uint8_t  heat_down_flg;
}Heat_Gun_t;

volatile typedef struct 
{
	volatile uint16_t rel_heat;
	volatile float remain_power;
}Power_Heat;
/* ��ģ�����ⲿ�ṩ�ı������� -----------------------------------------------*/
extern uint8_t Magazine_flag;    //���ֿ��ر�־λ
/* ��ģ�����ⲿ�ṩ���Զ����������ͱ������� ---------------------------------*/

/* ��ģ�����ⲿ�ṩ�Ľӿں���ԭ������ ---------------------------------------*/




#endif



