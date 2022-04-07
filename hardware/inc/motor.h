#ifndef __MOTOR_H_
#define __MOTOR_H_
#include "../../main.h"


#define MOTOR_CW_SetHigh()		(PORTCbits.RC0 = 1)
#define MOTOR_CW_SetLow()       (PORTCbits.RC0 =0 )

#define MOTOR_CCW_SetHigh()     (PORTCbits.RC1=1)
#define MOTOR_CCW_SetLow()		(PORTCbits.RC1=0)


void Motor_Init(void);
void Motor_CCW_Run(void);
void Motor_CW_Run(void);

void Motor_Stop(void);



#endif 
