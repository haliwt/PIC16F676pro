#include "../../hardware/inc/motor.h"

MOTOR_T motor_t;


void Motor_Init(void)
{
	TRISCbits.TRISC0 = 0;
	TRISCbits.TRISC1 =0;  //as output GPIO 

	ANSELbits.ANS4 = 0;
	ANSELbits.ANS5 = 0;
	
    MOTOR_CW_RC0_SetLow() ; //brake
    MOTOR_CCW_RC1_SetLow(); //brake

}

void Motor_CCW_Run(void)
{
	MOTOR_CW_RC0_SetHigh();	
	//__delay_ms(100);
	//motor_t.motorSet = 1;
    //if(motor_t.motorTimers < 1 )
	
    MOTOR_CCW_RC1_SetLow();
	//__delay_ms(100);
}

void Motor_CW_Run(void)
{
	MOTOR_CW_RC0_SetLow();	
	//__delay_ms(100);
	MOTOR_CCW_RC1_SetHigh();
	//__delay_ms(100);
}


void Motor_Stop(void)
{
    MOTOR_CW_RC0_SetLow(); //brake
    MOTOR_CCW_RC1_SetLow(); //brake
}


