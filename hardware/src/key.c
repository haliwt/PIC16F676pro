#include "../../hardware/inc/key.h"
#include "../../main.h"

#define   uint unsigned int
//key_types key;
//CMD_T cmd_t;

static uint8_t powkey=0;

void KEY_Init(void)
{
	              //??????? 
    ANSELbits.ANS6=0;
    TRISCbits.TRISC2=1;
   
    
}


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
				if(++key.on_time>6000)// 10000 long key be down
				{
					
					key.value = key.value|0x80; //key.value = 0x01 | 0x80  =0x81  
					key.on_time = 0;
					key.state   = finish;
                    // POWER_LED_OFF();
                   
				}
			}
			else if(key.read == _KEY_ALL_OFF)  // loose hand 
				{
					if(++key.off_time>2) //30 don't holding key dithering
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
				if(++key.off_time>5)//50 //100
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
          if( cmd_t.gCmd_Power ==PowerOn  && cmd_t.gDoKey==0){
       
			if(currKey != cmd_t.gCmd_KeyState){
				currKey = cmd_t.gCmd_KeyState;
				cmd_t.gmotor_upStep=0;
				 	cmd_t.gCmd_KeyNum ++;

				if(cmd_t.bottomPos ==1){

					cmd_t.gCmd_KeyNum =1;
					cmd_t.bottomPos=0;
				}
				if(cmd_t.topPos ==1){
					cmd_t.gCmd_KeyNum = 3;
					cmd_t.topPos=0;
				    
				}
		    
			
            if(cmd_t.gCmd_KeyNum  ==1){
                if(TOP_POS_RA1_GetValue()==0){ //RA2 
                      cmd_t.gCmd = MotorDown;
                }
           		else cmd_t.gCmd = MotorUp; //state is ?
				cmd_t.gmotor_upStep=0;
           	}
           	else if(cmd_t.gCmd_KeyNum ==2 || cmd_t.gCmd_KeyNum ==4){

                cmd_t.gCmd = TempStop;
				Motor_Stop();//WT.EDIT 2022.10.10
				if(cmd_t.gCmd_KeyNum==4)cmd_t.gCmd_KeyNum=0;
				
			}
           	else if(cmd_t.gCmd_KeyNum==3){

                cmd_t.gCmd = MotorDown;
				
           	}
			}
		}
         
        
        break;

    	case 0x81: //long times ke be presed power On
    	   powkey ++;
    	   if(powkey ==1){
            	cmd_t.gCmd_Power =PowerOn;
		        cmd_t.gCmd = 0;//MotorStop;
		        gTimer=0;
            }
            else{
               powkey =0;
               cmd_t.gCmd_Power =PowerOff;
			  
			}

    	break;

    	default:
			  
  
    	break;

    }

}

void RunCommand(void)
{
    if(cmd_t.gCmd_Power == PowerOn ){

        switch(cmd_t.gCmd){
            case TempStop:
             
				if(cmd_t.handPos==1){
	    	       cmd_t.handPos=0;
	    	        Motor_CW_Run();  //Move Up
	    	        __delay_ms(300);
	    	       
	    	    }
				else if(cmd_t.handPos ==2){ //motor run Up //WT.EDIT 2022.05.17
					cmd_t.handPos =0;
					Motor_CCW_Run(); //motor run down
					__delay_ms(150);
					
				}
				cmd_t.gmotor_upStep=0;	
				cmd_t.gCmd_KeyState ++;
                Motor_Stop();//Motor_Stop();
	    	    BLINK_LED_OFF();
             
                
            break;
		  
              case MotorUp : //CW -UP cmd_t.mtorDir =0;
				 if(Clamp_Hand()){
                    cmd_t.gCmd_KeyState++;
                    cmd_t.gCmd_KeyNum=0;//continuce Up run
                    cmd_t.handPos=2;
                    cmd_t.gCmd=TempStop;
	    		  
            	}
               else if(TOP_POS_RA1_GetValue()==0){ //RA2 
                   
					cmd_t.gCmd_KeyState++;
					cmd_t.topPos=1;
					cmd_t.gCmd_KeyNum = 2;
					cmd_t.gCmd=TempStop;
	    	   }
			   else{
					cmd_t.gCmd_KeyState++;
	    			cmd_t.gCmd_KeyNum = 1;
					dochargingFlag=0;
				    Motor_CW_Run();
	    			 BLINK_LED_Fun();
					
	    	 }
			break;

            case MotorDown: //CW- DOWN move cmd_t.mtorDir =1;
			   
				
				if(Clamp_Hand()){	
	           
				  cmd_t.gCmd_KeyState++;
	    		  cmd_t.gCmd_KeyNum=2;//continuce Down run
	    		  cmd_t.handPos=1;
	    		  cmd_t.gCmd=TempStop;
	    		  
            	}
            	else if(BOTTOM_POS_RA2_GetValue()==0){
                  
					cmd_t.gCmd_KeyState++;
					cmd_t.bottomPos=1;
					cmd_t.gCmd_KeyNum = 0;
					cmd_t.gCmd=TempStop;
	    		}
	    		else{
					cmd_t.gCmd_KeyState++;
	    			cmd_t.gCmd_KeyNum = 3;
					dochargingFlag=0;
			        BLINK_LED_Fun();
			        Motor_CCW_Run();
					
                   
				}
	    	


            break;

   			default://WT.EDIT 2022.10.10 
			   if(cmd_t.gmotor_upStep !=0 && cmd_t.gCmd != 0 && cmd_t.gCmd !=TempStop && cmd_t.gCmd !=0xf0){
                   if(cmd_t.handPos !=1 &&  cmd_t.handPos!=2 && cmd_t.bottomPos!=1 && cmd_t.topPos!=1){
                        if(cmd_t.gCmd_KeyNum == 3)cmd_t.gCmd=MotorDown;//WT.EDIT 2022.09.24 
                        if(cmd_t.gCmd_KeyNum ==1)cmd_t.gCmd=MotorUp ;   //WT.EDIT  2022.09.24
                   }
			   	}
			break;
		}
	}
	else if(cmd_t.gCmd_Power ==PowerOff){
               
    	        Motor_Stop();
               	cmd_t.gmotor_upStep=0;
	    		POWER_LED_OFF();
                BLINK_LED_OFF();
				cmd_t.gCmd_KeyState++;
				cmd_t.gCmd=0xf0;
                gTimer = 0;
				powkey=0;
    }


}



