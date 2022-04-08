#ifndef __LED_H_
#define __LED_H_
#include "../../main.h"





#define BLINK_LED1     PORTCbits.RC5
#define BLINK_LED2     PORTCbits.RC4
#define POWER_LED      PORTCbits.RC3

#define BLINK_LED1_RC5_SetDigitalInput()    do { TRISCbits.TRISC5 = 1; } while(0)
#define BLINK_LED1_RC5_SetDigitalOutput()   do { TRISCbits.TRISC5 = 0; } while(0)

#define BLINK_LED1_RC5_SetHigh()            do { PORTCbits.RC5 = 1; } while(0)
#define BLINK_LED1_RC5_SetLow()             do { PORTCbits.RC5 = 0; } while(0)

#define BLINK_LED2_RC4_SetDigitalInput()    do { TRISCbits.TRISC4 = 1; } while(0)
#define BLINK_LED2_RC4_SetDigitalOutput()   do { TRISCbits.TRISC4 = 0; } while(0)

#define BLINK_LED2_RC4_SetHigh()            do { PORTCbits.RC4 = 1; } while(0)
#define BLINK_LED2_RC4_SetLow()             do { PORTCbits.RC4 = 0; } while(0)


#define POWER_LED_RC3_SetDigitalInput()    do { TRISCbits.TRISC3 = 1; } while(0)
#define POWER_LED_RC3_SetDigitalOutput()   do { TRISCbits.TRISC3 = 0; } while(0)

#define POWER_LED_RC3_SetHigh()            do { PORTCbits.RC3 = 1; } while(0)
#define POWER_LED_RC3_SetLow()             do { PORTCbits.RC3 = 0; } while(0)
#define POWER_LED_RC3_SetAnalogMode()      do { ANSELbits.ANS7 = 1; } while(0)
#define POWER_LED_RC3_SetDigitalMode()     do { ANSELAbits.ANS7 = 0; } while(0)


#define uchar           unsigned char 
#define uint            unsigned int 
#define ulong            unsigned long 
//typedef unsigned long   uint32_t;



typedef struct _BLINK_LED{

    uchar  blink_LedFrequency;
    


}BLINK;

extern BLINK blink_t;



void  BLINK_POWER_LED_Init(void);
void  BLINK_LED_Fun(void);
void BLINK_LED_OFF(void);

void POWER_LED_ON(void);
void POWER_LED_OFF(void);



#endif 
