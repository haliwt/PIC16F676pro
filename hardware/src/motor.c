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

void Motor_CW_Run(void)
{
	MotorStart_CW_Step();
	MOTOR_CW_RC0_SetHigh();	
	MOTOR_CCW_RC1_SetLow();
	
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
     if(cmd_t.gmotor_thefirst_run_flag==0 ){//CW: run_go_up
		cmd_t.gmotor_thefirst_run_flag++;
       MOTOR_CCW_RC1_SetLow();
	   MOTOR_CW_RC0_SetHigh();	
        __delay_ms(30); //	WT.EDIT 2025.03.28
       MOTOR_CCW_RC1_SetLow();
	   __delay_ms(15);//	WT.EDIT 2025.03.28
       MOTOR_CW_RC0_SetHigh();	
	   __delay_ms(100);//	WT.EDIT 2025.03.28
	   MOTOR_CCW_RC1_SetLow();
	   __delay_ms(10);//	WT.EDIT 2025.03.28
	   MOTOR_CW_RC0_SetHigh();	
	   __delay_ms(300);//
      }
}

 void MotorStart_CCW_Step(void)
{
     if(cmd_t.gmotor_thefirst_run_flag==0 ){//CCW:go_down
		cmd_t.gmotor_thefirst_run_flag++;
        
      	MOTOR_CW_RC0_SetLow();	
	
	   MOTOR_CCW_RC1_SetHigh();
	   __delay_ms(50);
	    MOTOR_CCW_RC1_SetLow();
	   __delay_ms(15);
       MOTOR_CCW_RC1_SetHigh();
       __delay_ms(50); //WT.EDIT 2022.09.24
       MOTOR_CCW_RC1_SetHigh();
        
    }



}



