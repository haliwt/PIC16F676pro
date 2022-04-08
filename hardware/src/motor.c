#include "../../hardware/inc/motor.h"


void Motor_Init(void)
{
	TRISCbits.TRISC0 = 0;
	TRISCbits.TRISC1 =0;  //as output GPIO 
    MOTOR_CW_RC0_SetLow() ; //brake
    MOTOR_CCW_RC1_SetLow(); //brake

}

void Motor_CCW_Run(void)
{
	MOTOR_CW_RC0_SetHigh();	
	__delay_ms(100);
	MOTOR_CCW_RC1_SetLow();
	__delay_ms(100);
}

void Motor_CW_Run(void)
{
	MOTOR_CW_RC0_SetLow();	
	__delay_ms(100);
	MOTOR_CCW_RC1_SetHigh();
	__delay_ms(100);
}


void Motor_Stop(void)
{
    MOTOR_CW_RC0_SetLow(); //brake
    MOTOR_CCW_RC1_SetLow(); //brake
}


