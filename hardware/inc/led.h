#ifndef __LED_H_
#define __LED_H_
#include "../../main.h"



#define BLINK_LED1     PORTCbits.RC5
#define BLINK_LED2     PORTCbits.RC4
#define POWER_LED      PORTCbits.RC3

#define uint8_t             unsigned char 
#define int8_t              unsigned int 
#define uint16_t            unsigned short 
#define uint32_t            unsigned long 

typedef struct _BLINK_LED{

   uint8_t blink_LedFrequency;
    


}BLINK;

extern BLINK blink_t;



void  BLINK_POWER_LED_Init(void);
void  BLINK_LED_Fun(void);
void POWER_LED_ON(void);
void POWER_LED_OFF(void);



#endif 
