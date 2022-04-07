#ifndef __SENSOR_H_
#define __SENSOR_H_
#include "../../main.h"

#define TOP_POS()  		(PORTAbits.RA2)
#define BOTTOM_POS()   	(PORTAbits.RA1)
#define DOCHARGE()      (PORTAbits.RA0)
#define CLAMPHAND()     (PORTAbits.RA5)


void SENSOR_Init(void);

unsigned char Top_Position(void);
unsigned char  Bottom_Position(void);
unsigned char  Do_Charge(void);
unsigned char  Clamp_Hand(void);



#endif 
