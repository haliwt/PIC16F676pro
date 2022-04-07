#ifndef __LED_H_
#define __LED_H_
#include "../../main.h"


#define BLINK_LED1     PORTCbits.RC5
#define BLINK_LED2     PORTCbits.RC4
#define POWER_LED      PORTCbits.RC3

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
void POWER_LED_ON(void);
void POWER_LED_OFF(void);



#endif 
