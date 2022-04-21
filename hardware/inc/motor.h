#ifndef __MOTOR_H_
#define __MOTOR_H_
#include "../../main.h"






#define MOTOR_CW_RC0_SetHigh()		do { PORTCbits.RC0 = 1;} while(0)
#define MOTOR_CW_RC0_SetLow()       do { PORTCbits.RC0 = 0;} while(0)





#define MOTOR_CCW_RC1_SetHigh()     do { PORTCbits.RC1 = 1 ;} while(0)
#define MOTOR_CCW_RC1_SetLow()		do { PORTCbits.RC1 = 0 ;} while(0)





void Motor_Init(void);
void Motor_CCW_Run(void);
void Motor_CW_Run(void);
void Motor_Stop(void);



#endif 
