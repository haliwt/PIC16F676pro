#include "../../hardware/inc/key.h"
#include "../../main.h"

#define   uint unsigned int
//key_types key;
//CMD_T cmd_t;



void KEY_Init(void)
{
	              //??????? 
    ANSELbits.ANS6=0;
    TRISCbits.TRISC2=1;
   
    
}

#if MODE_KEY
uint8_t KEY_Scan(void)
{
  uint8_t  reval = 0;
  key.read = _KEY_ALL_OFF; //0x1F 
   if(KEY1_RC2_GetValue() ==0 )
	{
		//key.read  &= ~0x01; // 0x1f & 0xfe =  0x1E
       key.read = key.read & 0xfe;
	}
	
	
	switch(key.state )
	{
		case start:
		{
			if(key.read != _KEY_ALL_OFF)
			{
				key.buffer   = key.read; //??:key.buffer = 0x1E  POWER KEY 
				key.state    = first;
				key.on_time  = 0;
				key.off_time = 0;
             //   POWER_LED_ON();
                
			}
			break;
		}
		case first:
		{
			if(key.read == key.buffer) // adjust key be down 
			{
				if(++key.on_time> 50) //1000  0.5us
				{
					key.value = key.buffer^_KEY_ALL_OFF; // key.value = 0x1E ^ 0x1f = 0x01, com = 0x0E ^ 0x1f = 0x11
					key.on_time = 0;
                   
					key.state   = second;
                   
                    
				}
			}
			else
			{
				key.state   = start;
			}
			break;
		}
		case second:
		{
			if(key.read == key.buffer) //again adjust key if be pressed down 
			{
				if(++key.on_time>5000)//6000 10000 long key be down
				{
					
					key.value = key.value|0x80; //key.value = 0x01 | 0x80  =0x81  
					key.on_time = 0;
					key.state   = finish;
                    // POWER_LED_OFF();
                   
				}
			}
			else if(key.read == _KEY_ALL_OFF)  // loose hand 
				{
					if(++key.off_time>0)//2 //30 don't holding key dithering
					{
						key.value = key.buffer^_KEY_ALL_OFF; // key.value = 0x1E ^ 0x1f = 0x01
						
						key.state   = finish; // loose hand
					}
				}
		   
			break;
		}
		case finish:
		{
			
			reval = key.value; // is short time  TIMER_KEY = 0x01  2. long times TIMER_KEY = 0X81
			key.state   = end;
         
			break;
		}
		case end:
		{
			if(key.read == _KEY_ALL_OFF)
			{
				if(++key.off_time>2)//5 //50 //100
				{
					key.state   = start;
                  
				}
			}
			break;
		}
		default:
		{
			key.state   = start;
         
			break;
		}
	}
	return  reval;


}
#else 
#define SHORT_PRESS_THRESHOLD 30  // 短按的时间阈值
#define LONG_PRESS_THRESHOLD 4000   // 长按的时间阈值
#define DEBOUNCE_THRESHOLD 10      // 去抖动的时间阈值

uint8_t KEY_Scan(void)
{
 
    static uint16_t k1 = 0; // 记录 KEY1 按下的时间
    static uint8_t cnt = 0; // 记录按键释放的时间
    static uint8_t long_press_triggered = 0; // 标记是否已经触发长按事件
    uint8_t value = 0;

	if (KEY1_RC2_GetValue() == 0){
	       cnt = 0; // 清除释放计数器
		   k1++;	// 增加 KEY1 的按下计数
	
		   // 如果 KEY1 按下时间超过长按阈值且未触发长按事件，则触发长按
		   if (k1 >= LONG_PRESS_THRESHOLD && !long_press_triggered) {
			   long_press_triggered = 1; // 标记长按已触发
			    cmd_t.gCmd_Power =PowerOn;
		        cmd_t.gCmd = 0xf0;//MotorStop;
		        gTimer=0;
				POWER_LED_ON();
			   
			   return 0x81; 			 // 返回长按事件
		   }

       
    }

	  // 检测按键释放状态（按键抬起）
    if (KEY1_RC2_GetValue() == 1){
       // cnt++; // 增加释放计数器

        // 如果按键释放时间不足 DEBOUNCE_THRESHOLD，认为按键未完全释放
       // if (cnt < DEBOUNCE_THRESHOLD){
         ///   return 0;
       // }

        // 按键已完全释放，处理短按事件
        cnt = 0;

        // 处理 KEY1 的短按
        if (k1 > SHORT_PRESS_THRESHOLD && long_press_triggered ==0) {
			 // 重置按键计数器和长按标记
        k1 = 0;
  
        long_press_triggered = 0;
		value = 0x01; // 短按 KEY1

        return value;
            
        }
		else{
		    k1 = 0;
		 
			long_press_triggered = 0;

		    return 0;


		}

       

       
    }
    return 0;
  
}







#endif 


/**************************************************
 * 
 * Function Name: void CheckMode(unsigned char keyvalue)
 * Function : check which is command ? what is doing?
 * 
 * 
 * 
**************************************************/
void CheckMode(unsigned char keyvalue)
{
   static uint8_t currKey=0xff;

    switch(keyvalue){
        
         case 0x01: // run up or down
          if( cmd_t.gCmd_Power ==PowerOn){
       
		       if(BOTTOM_POS_RA2_GetValue()==0){//if(cmd_t.bottomPos ==1){

					cmd_t.gCmd = MotorUp; //wt.edif 2025.03.27
					cmd_t.gmotor_thefirst_run_flag=0;
				}
		        else if(TOP_POS_RA1_GetValue()==0 || cmd_t.clamphandPos == null_top_pos){ //RA2 ///else //if(cmd_t.gCmd_KeyNum  ==1){
		               
	                    cmd_t.gCmd = MotorDown;
						cmd_t.gmotor_thefirst_run_flag=0;
	            }
			    else if(cmd_t.gCmd == MotorUp){//second be pressed key 
	           	    cmd_t.gCmd = TempStop; //state is ?
	           	    Motor_Stop();//Motor_Stop();
					cmd_t.gmotor_thefirst_run_flag=0;
           	   }
           	   else if(cmd_t.gCmd == MotorDown){ //second be pressed key 

                 cmd_t.gCmd = TempStop;
				 Motor_Stop();//Motor_Stop();
				 cmd_t.gmotor_thefirst_run_flag=0;

			   }
           	   else if(cmd_t.gCmd == TempStop){

			      if(cmd_t.clamphandPos== null_up_state){

					  cmd_t.gCmd = MotorUp;
					  cmd_t.gmotor_thefirst_run_flag=0;

				  }
				  else if(cmd_t.clamphandPos== null_down_state){

					  cmd_t.gCmd = MotorDown;
					  cmd_t.gmotor_thefirst_run_flag=0;
                  }
                  else if(cmd_t.direction_flag == MotorDown){
                     
				      cmd_t.gCmd = MotorUp;
					  cmd_t.gmotor_thefirst_run_flag=0;

				   }
				   else if(cmd_t.direction_flag == MotorUp){

				      cmd_t.gCmd = MotorDown;
					  cmd_t.gmotor_thefirst_run_flag=0;   
				   }
           	   	}
			    else{

			       cmd_t.gCmd = MotorUp;
				   cmd_t.gmotor_thefirst_run_flag=0;
			       
				}
			  
		
          	}
         
        
        break;

    	case 0x81: //long times ke be presed power On
    	 
    	   if(cmd_t.gCmd_Power ==PowerOff){
            	cmd_t.gCmd_Power =PowerOn;
		        cmd_t.gCmd = 0xf0;//MotorStop;
		        gTimer=0;
				POWER_LED_ON();
            }
            else{
               	cmd_t.gCmd_Power =PowerOff;
			    Motor_Stop();
               	cmd_t.gmotor_thefirst_run_flag=0;
	    		POWER_LED_OFF();
                BLINK_LED_OFF();
			}

    	break;

    	default:
			  
  
    	break;

    }

}
/****************************************************************
*
*Function Name:void RunCommand(void)
*Function : main process run 
*Input Ref: NO
*Return Ref: NO
*
****************************************************************/
void RunCommand(void)
{
    if(cmd_t.gCmd_Power == PowerOn ){

        switch(cmd_t.gCmd){
            case TempStop:
             
				if(cmd_t.clamphandPos==up){
	    	       cmd_t.clamphandPos= null_up_state;
	    	        Motor_CW_Run();  //Move Up 
	    	        __delay_ms(300);
					Motor_Stop();//Motor_Stop();
					
	    	       
	    	    }
				else if(cmd_t.clamphandPos ==down){ //motor run Up //WT.EDIT 2022.05.17
					cmd_t.clamphandPos =null_down_state ;
					Motor_CCW_Run(); //motor run down
					__delay_ms(150);
					Motor_Stop();//Motor_Stop();
					
					
				}
				else{//next direct motor un up.WT.EDIT.2025.03.28
				
			     	Motor_Stop();//Motor_Stop();
	    	    	BLINK_LED_OFF();
				    POWER_LED_ON();
			    }
             
                
            break;
		  
              case MotorUp : //CW -UP cmd_t.mtorDir =0;
				if(Clamp_Hand()){
                 
                   cmd_t.clamphandPos=down;//go astern 
                    
                    cmd_t.gCmd=TempStop;
					Motor_Stop();//WT.EDIT 2025.03.20
			    }
				else if(TOP_POS_RA1_GetValue()==0){ //RA2 
                   
					cmd_t.gCmd=TempStop;
					Motor_Stop(); //WT.EDIT 2025.03.20
					cmd_t.clamphandPos= null_top_pos;
					BLINK_LED_OFF();
					
	    	   }
			   else{
				
	    			dochargingFlag=0;
					BLINK_LED_Fun();
				    Motor_CW_Run(); //go up run
	    			
					cmd_t.direction_flag = MotorUp;
					cmd_t.clamphandPos= null_state;
					
	    	 }
			break;

            case MotorDown: //CW- DOWN move cmd_t.mtorDir =1;
			   
				
				if(Clamp_Hand()){	
	              cmd_t.clamphandPos=up; //go astern 
	    		  cmd_t.gCmd=TempStop;
				  Motor_Stop(); //WT.EDIT 2025.03.20
	    		  
            	}
            	else if(BOTTOM_POS_RA2_GetValue()==0){
                  
					cmd_t.gCmd=TempStop;
					Motor_Stop(); //WT.EDIT 2025.03.20
					cmd_t.clamphandPos= null_bottom_pos;
	    		}
	    		else{
				
	    		
					dochargingFlag=0;
			        BLINK_LED_Fun();
			        Motor_CCW_Run(); //go down run .
			        cmd_t.direction_flag = MotorDown;
					cmd_t.clamphandPos= null_state;
					
                   
				}

            break;

   			default://WT.EDIT 2022.10.10 
			   
			break;
		}
	}
	


}



