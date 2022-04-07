#include "../../hardware/inc/motor.h"


void Motor_Init(void)
{
	TRISCbits.TRISC0 = 0;
	TRISCbits.TRISC1 =0;  //as output GPIO 
    MOTOR_CW_SetLow() ; //brake
    MOTOR_CCW_SetLow(); //brake

}

void Motor_CCW_Run(void)
{
	MOTOR_CW_SetHigh();	
	MOTOR_CCW_SetLow();
}

void Motor_CW_Run(void)
{
	MOTOR_CW_SetLow();	
	MOTOR_CCW_SetHigh();
}


void Motor_Stop(void)
{

	MOTOR_CW_SetLow(); //brake
    MOTOR_CCW_SetLow(); //brake
}


