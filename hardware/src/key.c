#include "../../hardware/inc/key.h"
#include "../../main.h"

key_types key;
CMD_T cmd_t;
void KEY_Init(void)
{
	//ANSELbits.ANS6= 0; //digital  I/O
	KEY1_RC2_SetDigitalMode() ;
    //TRISCbits.TRISC2 = 1; //as input GPIO
   KEY1_RC2_SetDigitalInput() ;
}

uint8_t KEY_Scan(void)
{
  uint8_t  reval = 0;
 // KEY1_RC2_SetDigitalMode() ;
 // KEY1_RC2_SetDigitalInput() ;
	key.read = _KEY_ALL_OFF; //0x1F 
   if(KEY1_RC2_GetValue() == 0)
	{
		
        key.read &= ~0x01; // 0x1f & 0xfe =  0x1E
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
				if(++key.on_time> 1000) //??  0.5us
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
				if(++key.on_time>10000)//long key be down
				{
					
					key.value = key.value|0x80; //key.value = 0x01 | 0x80  =0x81  
					key.on_time = 0;
					key.state   = finish;
                    // POWER_LED_OFF();
                   
				}
			}
			else if(key.read == _KEY_ALL_OFF)  // loose hand 
				{
					if(++key.off_time>30) //don't holding key dithering
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
				if(++key.off_time>100)
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
   static uint8_t powkey=0, currKey=0xff;

    switch(keyvalue){
        
        case 0:
			cmd_t.gCmd_KeyState++;
            return ;
        break;

    	case 0x01: // run up or down
    	 if( cmd_t.gCmd_Power ==PowerOn ){
       
          if(currKey != cmd_t.gCmd_KeyState){
             currKey = cmd_t.gCmd_KeyState;
           	  cmd_t.gCmd_KeyNum ++;

			if(cmd_t.bottomPos ==1){

				cmd_t.gCmd_KeyNum =1;
				cmd_t.bottomPos=0;
			}
			if(cmd_t.topPos ==1){
				
				cmd_t.gCmd_KeyNum = 3;
				cmd_t.topPos=0;
			    
			}
			if(cmd_t.handPos ==1){
				if(Clamp_Hand()==1){
				 cmd_t.gCmd_KeyNum = 3;
				}
				else{
				  cmd_t.handPos=0;
				}
			}
            if(cmd_t.gCmd_KeyNum  ==1){
           		cmd_t.gCmd = MotorUp; //state is ?
				BLINK_LED1_RC5_SetLow() ;
				BLINK_LED2_RC4_SetHigh() ;
           	}
           	else if(cmd_t.gCmd_KeyNum ==2){

                cmd_t.gCmd = MotorStop;
				

           	}
           	else if(cmd_t.gCmd_KeyNum==3){

                cmd_t.gCmd = MotorDown;
                cmd_t.gCmd_KeyNum=0;
				BLINK_LED1_RC5_SetHigh();
				BLINK_LED2_RC4_SetLow(); 
           	}
         }
        }
        break;

    	case 0x81: //long times ke be presed power On
    	   powkey = powkey ^ 0x01;
    	   if(powkey ==1){
            POWER_LED_ON();
            cmd_t.gCmd_Power =PowerOn;
            }
            else{
            	POWER_LED_OFF();
	            cmd_t.gCmd_Power =PowerOff;
            }

    	break;

    	default:
            Motor_Stop();
    	    BLINK_LED_OFF();
    		cmd_t.gCmd_KeyState=0;
    	break;

    }

}

void RunCommand(void)
{
    if(cmd_t.gCmd_Power == PowerOn ){

        switch(cmd_t.gCmd){

           case MotorUp :
		   	 
            	if(Clamp_Hand()){
	              Motor_Stop();
	    		  BLINK_LED_OFF();
				  cmd_t.gCmd_KeyState++;
	    		  cmd_t.gCmd_KeyNum=0;//continuce Up run
	    		  cmd_t.handPos=1;
	    		  cmd_t.gCmd=MotorStop;
	    		  
            	}
               else if(Top_Position()){
                      Motor_Stop();
	    		      BLINK_LED_OFF();
					 cmd_t.gCmd_KeyState++;
					cmd_t.topPos=1;
					cmd_t.gCmd=MotorStop;
	    	   }
			   else{
					cmd_t.gCmd_KeyState++;
	    			Motor_CCW_Run();
	    		//	BLINK_LED_Fun();
	    	 }
			break;

            case MotorDown:
				
            	if(Clamp_Hand()){
	              Motor_Stop();
	    		  BLINK_LED_OFF();
				  cmd_t.gCmd_KeyState++;
	    		  cmd_t.gCmd_KeyNum=2;//continuce Down run
	    		  cmd_t.handPos=1;
	    		  cmd_t.gCmd=MotorStop;
	    		  
            	}
            	else if(Bottom_Position()){
                    Motor_Stop();
	    		    BLINK_LED_OFF();
					cmd_t.gCmd_KeyState++;
					cmd_t.bottomPos=1;
					cmd_t.gCmd=MotorStop;
	    		}
	    		else{
					cmd_t.gCmd_KeyState++;
	    			Motor_CW_Run();
	    			//BLINK_LED_Fun();
	    		}


            break;

            case MotorStop:
			    cmd_t.gCmd_KeyState++;
                cmd_t.gCmd_RunState = MotorStop;
             	Motor_Stop();
	    		BLINK_LED_OFF();
			break;

			default:


			break;
		}
}

    else if(cmd_t.gCmd_Power ==PowerOff){

    	        Motor_Stop();
	    		POWER_LED_OFF();
	    		BLINK_LED_OFF();	
    }


}


