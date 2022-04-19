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
	MOTOR_CCW_RC1_SetLow();
	
}

void Motor_CW_Run(void)
{
	MOTOR_CW_RC0_SetLow();	
	
	MOTOR_CCW_RC1_SetHigh();
	
}


void Motor_Stop(void)
{
    MOTOR_CW_RC0_SetLow(); //brake
    MOTOR_CCW_RC1_SetLow(); //brake
}


