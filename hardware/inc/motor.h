#ifndef __MOTOR_H_
#define __MOTOR_H_
#include "../../main.h"



#define MOTOR_CW_RC0_SetDigitalInput()    do { TRISCbits.TRISC0 = 1; } while(0)
#define MOTOR_CW_RC0_SetDigitalOutput()   do { TRISCbits.TRISC0 = 0; } while(0)

#define MOTOR_CW_RC0_SetAnalogMode()      do { ANSELbits.ANS4 = 1; } while(0)
#define MOTOR_CW_RC0_SetDigitalMode()     do { ANSELbits.ANS4 = 0; } while(0)


#define MOTOR_CW_RC0_SetHigh()		do { PORTCbits.RC0 = 1;} while(0)
#define MOTOR_CW_RC0_SetLow()       do { PORTCbits.RC0 = 0;} while(0)

#define MOTOR_CCW_RC1_SetDigitalInput()    do { TRISCbits.TRISC1 = 1; } while(0)
#define MOTOR_CCW_RC1_SetDigitalOutput()   do { TRISCbits.TRISC1 = 0; } while(0)

#define MOTOR_CCW_RC1_SetAnalogMode()      do { ANSELbits.ANS5 = 1; } while(0)
#define MOTOR_CCW_RC1_SetDigitalMode()     do { ANSELbits.ANS5 = 0; } while(0)

#define MOTOR_CCW_RC1_SetHigh()     do { PORTCbits.RC1 = 1 ;} while(0)
#define MOTOR_CCW_RC1_SetLow()		do { PORTCbits.RC1 = 0 ;} while(0)





void Motor_Init(void);
void Motor_CCW_Run(void);
void Motor_CW_Run(void);

void Motor_Stop(void);
void MotorRunCommand(void);

void Motor_TempStop(void);
#endif 
