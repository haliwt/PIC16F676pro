#ifndef __SENSOR_H_
#define __SENSOR_H_
#include "../../main.h"



#define TOP_POS_RA2_SetDigitalInput()    			do { TRISAbits.TRISA2 = 1; } while(0)
#define TOP_POS_RA2_SetDigitalOutput()   			do { TRISAbits.TRISA2 = 0; } while(0)

#define TOP_POS_RA2_SetAnalogMode()      			do { ANSELbits.ANS2 = 1; } while(0)
#define TOP_POS_RA2_SetDigitalMode()     			do { ANSELbits.ANS2 = 0; } while(0)


#define TOP_POS_RA2_GetValue()  		 PORTAbits.RA2

#define BOTTOM_POS_RA1_GetValue()   	 PORTAbits.RA1
#define DOCHARGE_RA0_GetValue()          PORTAbits.RA0


#define CLAMPHAND_RA5_SetDigitalInput()    			do { TRISAbits.TRISA5 = 1; } while(0)
#define CLAMPHAND_RA5_SetDigitalOutput()   			do { TRISAbits.TRISA5 = 0; } while(0)

#define CLAMPHAND_RA5_GetValue()         			PORTAbits.RA5





void SENSOR_Init(void);

unsigned char Top_Position(void);
unsigned char  Bottom_Position(void);
unsigned char  Do_Charge(void);
unsigned char  Clamp_Hand(void);



#endif 
