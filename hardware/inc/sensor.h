#ifndef __SENSOR_H_
#define __SENSOR_H_
#include "../../main.h"

#define BOTTOM_POS_RA2_GetValue()  		 PORTAbits.RA2

#define TOP_POS_RA1_GetValue()   	     PORTAbits.RA1

#define DOCHARGE_RA0_GetValue()          PORTAbits.RA0

#define CLAMPHAND_RA5_GetValue()        PORTAbits.RA5





void SENSOR_Init(void);


void Do_Charge(void);
unsigned char  Clamp_Hand(void);




#endif 
