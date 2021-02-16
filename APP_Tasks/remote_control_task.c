/*******************************************************************************
                      版权所有 (C), 2020-,NCUROBOT
 *******************************************************************************
  文 件 名   : remote_control_task.c
  版 本 号   : V1.0
  作    者   : 高云海
  生成日期   : 2020.12.1
  最近修改   : 
  功能描述   : 遥控器数据进一步处理任务，包括判断是键鼠操作还是遥控器操作等。      
							 （当USART1接收完一组数据时在空闲中断进行解码，并发送任务通知,然后
							 该任务方可运行，否则该任务处于阻塞状态，阻塞时间为4294967295ms即
							 约等于47天17小时。）
  函数列表   : 1) Remote_Data_Task()      【FreeRTOS函数：操作系统任务调度运行】  
*******************************************************************************/
/* 包含头文件 ----------------------------------------------------------------*/
#include "remote_control_task.h"
#include "offline_check.h"
//CW:
#include "remote_control.h"
#include "motor_use_can.h"
#include "gimbal_control_task.h"     //引入云台状态结构体Gimbal_status
#include "shoot_task.h"             //引入拨盘等状态标志位 例如bopan_stop
#include "main.h"                   //引入键鼠宏定义 例如F_Press

/* 内部宏定义 ----------------------------------------------------------------*/

/* 内部自定义数据类型的变量 --------------------------------------------------*/
uint8_t test;
/* 内部变量 ------------------------------------------------------------------*/

/* 内部函数原型声明 ----------------------------------------------------------*/

/* 函数主体部分 --------------------------------------------------------------*/
/**
  * @brief				遥控器任务    
  * @param[in]		
	* @param[out]		
  * @retval				none
*/
void Remote_Data_Task(void const * argument)
{
	  uint32_t NotifyValue;

		portTickType xLastWakeTime;
		xLastWakeTime = xTaskGetTickCount();
	
	for(;;)
	{
		NotifyValue = ulTaskNotifyTake(pdTRUE,portMAX_DELAY);  //未有任务通知则进入堵塞状态去等待任务通知
		
    if(NotifyValue == 1)
		{
			Refresh_Task_OffLine_Time(RemoteDataTask_TOE);

			//接收遥控器数据     解码函数  空闲中断USART1 遥控器要进行哪些任务？
			/*1.通过CAN发送遥控器数据     2.发送给minipc     3.根据s1设置状态位、云台模式、底盘模式*/
			
			//1.上下云台通信（给下云台发送裁判系统信息） 为什么只要ch0和ch1
			CAN_Send_RemoteDate( &hcan2,rc_ctrl.key.v,rc_ctrl.rc.ch0,rc_ctrl.rc.ch1,rc_ctrl.rc.s1,rc_ctrl.rc.s2);
			
			switch(rc_ctrl.rc.s1)  //左拨钮
			{
					case 1: //上
					{
						Gimbal_status.remote_mode = 0;      //拨到s1是什么状态？  
						MouseKeyControlProcess();           
					}break; 
					case 2: //下
					{
						Gimbal_status.remote_mode = 0;
				    RemoteControlProcess();
					}break; 
					case 3: //中
					{
						Gimbal_status.remote_mode = 1;
					}break;  
					default :break;
			}
			
			
		}
		
		osDelayUntil(&xLastWakeTime, REMOTE_PERIOD);
	}
}



/***************************************************************************************
**
	*	@brief	RemoteControlProcess()
	*	@param
	*	@supplement	与遥控器进行对接，对遥控器的数据进行处理，实现对底盘、云台、发射机构的控制
	*	@retval	
****************************************************************************************/
void RemoteControlProcess()  
{
		switch(rc_ctrl.rc.s2)
		{
		
//				case 1: //上
//				{
//						gimbal_status.gimbal_mode = 2;  
//					yaw_set.expect =yaw_set.expect + (RC_Ctl.rc.ch2 - 0x400) / 10;
//  		  	pit_set.expect = pit_set.expect + (0x400 - RC_Ctl.rc.ch3) / 20;	
//				}break; 
//				case 2: //下
//				{
//						gimbal_status.gimbal_mode = 2;  
//					yaw_set.expect=0;
//				}break; 
//				case 3: //中
//				{ 
//						gimbal_status.gimbal_mode = 2;  
//					yaw_set.expect=1000;	 
//				}break; 
//				default :break;
//			}
				
			
			
		
			case 3: //中
			{
				 Gimbal_status.gimbal_mode = 2;            //编码器模式 
//				 Set_AX6(2,819,0x3ff);       //逆时针角度   240° 关
				Gimbal_status.bopan_mode = bopan_Stop;
			}break; 
			case 2: //下
			{
						Gimbal_status.gimbal_mode = 3;            //小陀螺模式  3
	//			 Set_AX6(2,819,0x3ff);       //逆时针角度   240° 关
				Gimbal_status.bopan_mode = bopan_Stop;
			   
			}break; 
			case 1: //上
			{
						Gimbal_status.gimbal_mode = 1;            //跟随模式  

//				 Set_AX6(2,512,0x3ff);       //逆时针角度   150°
         Gimbal_status.bopan_mode =bopan_Stop ;
				
//				gimbal_status.gimbal_mode = 4;    //视觉模式
//				gimbal_status.minipc_mode = 1;    //自瞄模式
			}break; 
			
			
			
			
			
			
			default :break;
		}					
        
    if((Gimbal_status.gimbal_mode == 1) || (Gimbal_status.gimbal_mode == 3))            //陀螺仪模式
		{
			  yaw_tly_set.expect = yaw_tly_set.expect + (rc_ctrl.rc.ch2 - 0x400) / 10;	
				pit_set.expect = pit_set.expect + (0x400 - rc_ctrl.rc.ch3) / 20;	              //pit_set.expect_remote不受模式影响		
			
		}else if(Gimbal_status.gimbal_mode == 2 )       // 编码器模式  
		{
				yaw_set.expect = yaw_set.expect + (rc_ctrl.rc.ch2 - 0x400) / 10;
		  	pit_set.expect = pit_set.expect + (0x400 - rc_ctrl.rc.ch3) / 20;	 
		}
//    Mocha_flag=1;
		
		if(pit_set.expect<-583) pit_set.expect=-583;
		else if(pit_set.expect>443)  pit_set.expect=443;


//				  if(RC_Ctl.rc.s2 == 1)            //上
//		{    
//			 gimbal_status.bopan_mode= bopan_danfa_mode;
//		}
//		else if(RC_Ctl.rc.s2== 2)       //下
//		{
//        gimbal_status.bopan_mode = bopan_Lianfa_mode;
//		}else                             //中
//		{
//        gimbal_status.bopan_mode = bopan_Stop;    
//		}		
}

/***************************************************************************************
**
	*	@brief	MouseKeyControlProcess()
	*	@param
	*	@supplement	对键鼠的数据进行处理
	*	@retval	
****************************************************************************************/
void MouseKeyControlProcess()
{
	  static uint16_t delay=0;
	
 	
		if(F_Press){   //F键跟随
			test=1;
			Gimbal_status.gimbal_mode = 1;  
		}
		if(CTRL_Press && F_Press){    //取消跟随模式后切换成分离
			test=2;
			Gimbal_status.gimbal_mode = 2;  
		}
		
		
		if(R_Press){    //R键开弹仓
			Magazine_flag = 1;        //单场开关标志位
		}
		if(CTRL_Press&&R_Press){
			Magazine_flag = 0;
		}

		
		if(Left_Press){   //左键发射一发
			if(delay>2 && Left_Press){   //按键消抖
				Gimbal_status.bopan_mode = bopan_danfa_mode;
				delay=0;
			}
			delay++;
		}
		
		if(Right_Press){    //右键连发
			Gimbal_status.bopan_mode=bopan_Lianfa_mode;
		}
		
		if(C_Press){    //小陀螺模式
			Gimbal_status.gimbal_mode=3;                                                                        
		}
		if(C_Press&&CTRL_Press){   //取消小陀螺后切换成跟随模式
			Gimbal_status.gimbal_mode=1;
		}
		
		if(X_Press){   //X键 45度模式
			
			Gimbal_status.gimbal_mode = 6;  
		}
		if(CTRL_Press && X_Press){    //取消45度模式后切换成跟随
			
			Gimbal_status.gimbal_mode = 1; 
		}
//		
			
			
		
		
    
	
	if((Gimbal_status.gimbal_mode == 1) || (Gimbal_status.gimbal_mode == 3)|| (Gimbal_status.gimbal_mode == 6))            //陀螺仪模式
		{
			  yaw_tly_set.expect = yaw_tly_set.expect + rc_ctrl.mouse.x*1.2f;	
				pit_set.expect = pit_set.expect - rc_ctrl.mouse.y *1.2f;	              //pit_set.expect_remote不受模式影响		
			
		}else if(Gimbal_status.gimbal_mode == 2 )       // 编码器模式  
		{
				yaw_set.expect = yaw_set.expect + rc_ctrl.mouse.x*1.0f;
		  	pit_set.expect = pit_set.expect - rc_ctrl.mouse.y *1.0f;	  
		}
		if(pit_set.expect<-583) pit_set.expect=-583;
		else if(pit_set.expect>443)  pit_set.expect=443;       
		
}
