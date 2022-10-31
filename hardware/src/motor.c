#include "../../hardware/inc/motor.h"



 void MotorStart_CW_Step(void);
void MotorStart_CCW_Step(void);
void Motor_Init(void)
{
	TRISCbits.TRISC0 = 0;
	TRISCbits.TRISC1 =0;  //as output GPIO 

	ANSELbits.ANS4 = 0;
	ANSELbits.ANS5 = 0;
	
    MOTOR_CW_RC0_SetLow() ; //brake
    MOTOR_CCW_RC1_SetLow(); //brake

}

void Motor_CW_Run(void)//Run Up Motor 
{
	MotorStart_CW_Step();
 //   MOTOR_CCW_RC1_SetLow();//WT.EDIT 2022.10.31	
	MOTOR_CW_RC0_SetHigh();
    __delay_ms(5);//WT.EDIT 2022.10.31	
//	MOTOR_CCW_RC1_SetLow();//WT.EDIT 2022.10.31	
	
}

void Motor_CCW_Run(void)
{
	MotorStart_CCW_Step();
    MOTOR_CW_RC0_SetLow();	
	
	MOTOR_CCW_RC1_SetHigh();
}



void Motor_Stop(void)
{
    MOTOR_CW_RC0_SetLow(); //brake
    MOTOR_CCW_RC1_SetLow(); //brake
}
void MotorStart_CW_Step(void)//Up 
{

     if(cmd_t.gmotor_upStep==0 ){//CW
		cmd_t.gmotor_upStep++;
        MOTOR_CCW_RC1_SetLow();
        
       MOTOR_CW_RC0_SetHigh();	
	   __delay_ms(50);
	   MOTOR_CW_RC0_SetLow();
	   __delay_ms(50);
       MOTOR_CW_RC0_SetHigh();	
	   __delay_ms(50);
	}
}
#if 0
 void MotorStart_CW_Step(void)//Up 
{
     //unsigned char m =2;//WT.EDIT VERSION V023 
     unsigned char m =2;//WT.EDIT 2022.10.10
     if(cmd_t.gmotor_upStep==0 ){//CW
		cmd_t.gmotor_upStep++;
        MOTOR_CCW_RC1_SetLow();
        
       MOTOR_CW_RC0_SetHigh();	
	   __delay_ms(25);
	   MOTOR_CW_RC0_SetLow();
	   __delay_ms(25);
       MOTOR_CW_RC0_SetHigh();	
	   __delay_ms(25);
	   MOTOR_CW_RC0_SetLow();
		 __delay_ms(25);
	   MOTOR_CW_RC0_SetHigh();	//WT.EDIT 2022.10.11
	 
       while(m--){ //WT.EDIT 2022.09.30,run two times
       if(TOP_POS_RA1_GetValue()==0 ){ //RA2 
            Motor_Stop();
            m = 0;
            return ;
       }
       else if(cmd_t.gCmd==TempStop){ //
       	  Motor_Stop();
            m = 0;
            return ;
       }
       else if(TOP_POS_RA1_GetValue()==1)
          __delay_ms(200);//WT.EDIT 2002.10.10 __delay_ms(300); //WT.EDIT 2022.09.24
     
       }
    }
}
#endif 
/***************************************************************************
	*
	*Function Name :void MotorStart_CCW_Step(void)
	*Function :motor run down 
	*Input Ref:NO
	*Return Ref:NO
	*
***************************************************************************/
void MotorStart_CCW_Step(void)
{
     if(cmd_t.gmotor_upStep==0 ){//CW
		cmd_t.gmotor_upStep++;
        
      	MOTOR_CW_RC0_SetLow();	
	
	   MOTOR_CCW_RC1_SetHigh();
	   __delay_ms(50);
	    MOTOR_CCW_RC1_SetLow();
	   __delay_ms(50);
       MOTOR_CCW_RC1_SetHigh();
       //__delay_ms(50); //WT.EDIT 2022.09.24
        
    }

}



