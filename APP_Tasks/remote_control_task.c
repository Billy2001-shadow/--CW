/*******************************************************************************
                      ��Ȩ���� (C), 2020-,NCUROBOT
 *******************************************************************************
  �� �� ��   : remote_control_task.c
  �� �� ��   : V1.0
  ��    ��   : ���ƺ�
  ��������   : 2020.12.1
  ����޸�   : 
  ��������   : ң�������ݽ�һ���������񣬰����ж��Ǽ����������ң���������ȡ�      
							 ����USART1������һ������ʱ�ڿ����жϽ��н��룬����������֪ͨ,Ȼ��
							 �����񷽿����У����������������״̬������ʱ��Ϊ4294967295ms��
							 Լ����47��17Сʱ����
  �����б�   : 1) Remote_Data_Task()      ��FreeRTOS����������ϵͳ����������С�  
*******************************************************************************/
/* ����ͷ�ļ� ----------------------------------------------------------------*/
#include "remote_control_task.h"
#include "offline_check.h"
//CW:
#include "remote_control.h"
#include "motor_use_can.h"
#include "gimbal_control_task.h"     //������̨״̬�ṹ��Gimbal_status
#include "shoot_task.h"             //���벦�̵�״̬��־λ ����bopan_stop
#include "main.h"                   //�������궨�� ����F_Press

/* �ڲ��궨�� ----------------------------------------------------------------*/

/* �ڲ��Զ����������͵ı��� --------------------------------------------------*/
uint8_t test;
/* �ڲ����� ------------------------------------------------------------------*/

/* �ڲ�����ԭ������ ----------------------------------------------------------*/

/* �������岿�� --------------------------------------------------------------*/
/**
  * @brief				ң��������    
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
		NotifyValue = ulTaskNotifyTake(pdTRUE,portMAX_DELAY);  //δ������֪ͨ��������״̬ȥ�ȴ�����֪ͨ
		
    if(NotifyValue == 1)
		{
			Refresh_Task_OffLine_Time(RemoteDataTask_TOE);

			//����ң��������     ���뺯��  �����ж�USART1 ң����Ҫ������Щ����
			/*1.ͨ��CAN����ң��������     2.���͸�minipc     3.����s1����״̬λ����̨ģʽ������ģʽ*/
			
			//1.������̨ͨ�ţ�������̨���Ͳ���ϵͳ��Ϣ�� ΪʲôֻҪch0��ch1
			CAN_Send_RemoteDate( &hcan2,rc_ctrl.key.v,rc_ctrl.rc.ch0,rc_ctrl.rc.ch1,rc_ctrl.rc.s1,rc_ctrl.rc.s2);
			
			switch(rc_ctrl.rc.s1)  //��ť
			{
					case 1: //��
					{
						Gimbal_status.remote_mode = 0;      //����s1��ʲô״̬��  
						MouseKeyControlProcess();           
					}break; 
					case 2: //��
					{
						Gimbal_status.remote_mode = 0;
				    RemoteControlProcess();
					}break; 
					case 3: //��
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
	*	@supplement	��ң�������жԽӣ���ң���������ݽ��д���ʵ�ֶԵ��̡���̨����������Ŀ���
	*	@retval	
****************************************************************************************/
void RemoteControlProcess()  
{
		switch(rc_ctrl.rc.s2)
		{
		
//				case 1: //��
//				{
//						gimbal_status.gimbal_mode = 2;  
//					yaw_set.expect =yaw_set.expect + (RC_Ctl.rc.ch2 - 0x400) / 10;
//  		  	pit_set.expect = pit_set.expect + (0x400 - RC_Ctl.rc.ch3) / 20;	
//				}break; 
//				case 2: //��
//				{
//						gimbal_status.gimbal_mode = 2;  
//					yaw_set.expect=0;
//				}break; 
//				case 3: //��
//				{ 
//						gimbal_status.gimbal_mode = 2;  
//					yaw_set.expect=1000;	 
//				}break; 
//				default :break;
//			}
				
			
			
		
			case 3: //��
			{
				 Gimbal_status.gimbal_mode = 2;            //������ģʽ 
//				 Set_AX6(2,819,0x3ff);       //��ʱ��Ƕ�   240�� ��
				Gimbal_status.bopan_mode = bopan_Stop;
			}break; 
			case 2: //��
			{
						Gimbal_status.gimbal_mode = 3;            //С����ģʽ  3
	//			 Set_AX6(2,819,0x3ff);       //��ʱ��Ƕ�   240�� ��
				Gimbal_status.bopan_mode = bopan_Stop;
			   
			}break; 
			case 1: //��
			{
						Gimbal_status.gimbal_mode = 1;            //����ģʽ  

//				 Set_AX6(2,512,0x3ff);       //��ʱ��Ƕ�   150��
         Gimbal_status.bopan_mode =bopan_Stop ;
				
//				gimbal_status.gimbal_mode = 4;    //�Ӿ�ģʽ
//				gimbal_status.minipc_mode = 1;    //����ģʽ
			}break; 
			
			
			
			
			
			
			default :break;
		}					
        
    if((Gimbal_status.gimbal_mode == 1) || (Gimbal_status.gimbal_mode == 3))            //������ģʽ
		{
			  yaw_tly_set.expect = yaw_tly_set.expect + (rc_ctrl.rc.ch2 - 0x400) / 10;	
				pit_set.expect = pit_set.expect + (0x400 - rc_ctrl.rc.ch3) / 20;	              //pit_set.expect_remote����ģʽӰ��		
			
		}else if(Gimbal_status.gimbal_mode == 2 )       // ������ģʽ  
		{
				yaw_set.expect = yaw_set.expect + (rc_ctrl.rc.ch2 - 0x400) / 10;
		  	pit_set.expect = pit_set.expect + (0x400 - rc_ctrl.rc.ch3) / 20;	 
		}
//    Mocha_flag=1;
		
		if(pit_set.expect<-583) pit_set.expect=-583;
		else if(pit_set.expect>443)  pit_set.expect=443;


//				  if(RC_Ctl.rc.s2 == 1)            //��
//		{    
//			 gimbal_status.bopan_mode= bopan_danfa_mode;
//		}
//		else if(RC_Ctl.rc.s2== 2)       //��
//		{
//        gimbal_status.bopan_mode = bopan_Lianfa_mode;
//		}else                             //��
//		{
//        gimbal_status.bopan_mode = bopan_Stop;    
//		}		
}

/***************************************************************************************
**
	*	@brief	MouseKeyControlProcess()
	*	@param
	*	@supplement	�Լ�������ݽ��д���
	*	@retval	
****************************************************************************************/
void MouseKeyControlProcess()
{
	  static uint16_t delay=0;
	
 	
		if(F_Press){   //F������
			test=1;
			Gimbal_status.gimbal_mode = 1;  
		}
		if(CTRL_Press && F_Press){    //ȡ������ģʽ���л��ɷ���
			test=2;
			Gimbal_status.gimbal_mode = 2;  
		}
		
		
		if(R_Press){    //R��������
			Magazine_flag = 1;        //�������ر�־λ
		}
		if(CTRL_Press&&R_Press){
			Magazine_flag = 0;
		}

		
		if(Left_Press){   //�������һ��
			if(delay>2 && Left_Press){   //��������
				Gimbal_status.bopan_mode = bopan_danfa_mode;
				delay=0;
			}
			delay++;
		}
		
		if(Right_Press){    //�Ҽ�����
			Gimbal_status.bopan_mode=bopan_Lianfa_mode;
		}
		
		if(C_Press){    //С����ģʽ
			Gimbal_status.gimbal_mode=3;                                                                        
		}
		if(C_Press&&CTRL_Press){   //ȡ��С���ݺ��л��ɸ���ģʽ
			Gimbal_status.gimbal_mode=1;
		}
		
		if(X_Press){   //X�� 45��ģʽ
			
			Gimbal_status.gimbal_mode = 6;  
		}
		if(CTRL_Press && X_Press){    //ȡ��45��ģʽ���л��ɸ���
			
			Gimbal_status.gimbal_mode = 1; 
		}
//		
			
			
		
		
    
	
	if((Gimbal_status.gimbal_mode == 1) || (Gimbal_status.gimbal_mode == 3)|| (Gimbal_status.gimbal_mode == 6))            //������ģʽ
		{
			  yaw_tly_set.expect = yaw_tly_set.expect + rc_ctrl.mouse.x*1.2f;	
				pit_set.expect = pit_set.expect - rc_ctrl.mouse.y *1.2f;	              //pit_set.expect_remote����ģʽӰ��		
			
		}else if(Gimbal_status.gimbal_mode == 2 )       // ������ģʽ  
		{
				yaw_set.expect = yaw_set.expect + rc_ctrl.mouse.x*1.0f;
		  	pit_set.expect = pit_set.expect - rc_ctrl.mouse.y *1.0f;	  
		}
		if(pit_set.expect<-583) pit_set.expect=-583;
		else if(pit_set.expect>443)  pit_set.expect=443;       
		
}
