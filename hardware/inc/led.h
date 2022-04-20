#ifndef __LED_H_
#define __LED_H_
#include "../../main.h"

#define BLINK_LED1_RC5_SetHigh()            do { PORTCbits.RC5 = 1; } while(0)
#define BLINK_LED1_RC5_SetLow()             do { PORTCbits.RC5 = 0; } while(0)



#define BLINK_LED2_RC4_SetHigh()            do { PORTCbits.RC4 = 1; } while(0)
#define BLINK_LED2_RC4_SetLow()             do { PORTCbits.RC4 = 0; } while(0)




#define POWER_LED_ON()              do { PORTCbits.RC3 = 1; } while(0)
#define POWER_LED_OFF()             do { PORTCbits.RC3 = 0; } while(0)




#define uchar           unsigned char 
#define uint            unsigned int 
#define ulong            unsigned long 






uchar blink_LedFrequency;

void  BLINK_POWER_LED_Init(void);
void  BLINK_LED_Fun(void);
void BLINK_LED_OFF(void);
void BLINK_LED_ON(void);




#endif 
