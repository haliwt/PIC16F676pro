#ifndef __SENSOR_H_
#define __SENSOR_H_
#include "../../main.h"



#define TOP_POS_RA2_SetDigitalInput()    			TRISAbits.TRISA2 = 1
#define TOP_POS_RA2_SetDigitalOutput()   		TRISAbits.TRISA2 = 0

#define TOP_POS_RA2_SetAnalogMode()      	    ANSELbits.ANS2 = 1
#define TOP_POS_RA2_SetDigitalMode()     		ANSELbits.ANS2 = 0


#define TOP_POS_RA2_GetValue()  		 PORTAbits.RA2

#define BOTTOM_POS_RA1_GetValue()   	 PORTAbits.RA1
#define DOCHARGE_RA0_GetValue()          PORTAbits.RA0


#define CLAMPHAND_RA5_SetDigitalInput()    			TRISAbits.TRISA5 = 1
#define CLAMPHAND_RA5_SetDigitalOutput()   			TRISAbits.TRISA5 = 0

#define CLAMPHAND_RA5_GetValue()         			PORTAbits.RA5





void SENSOR_Init(void);

unsigned char Top_Position(void);
unsigned char  Bottom_Position(void);
void Do_Charge(void);
unsigned char  Clamp_Hand(void);




#endif 
