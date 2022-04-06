#ifndef __TIM0_H
#define __TIM0_H
#include "../../main.h"
#include "../inc/led.h"

#define _XTAL_FREQ    4000000UL
#define uint8_t unsigned char 



#define TMR0_INTERRUPT_TICKER_FACTOR    1


void TMR0_Initialize(void);


uint8_t TMR0_ReadTimer(void);


void TMR0_WriteTimer(uint8_t timerVal);


void TMR0_Reload(void);


void TMR0_CallBack(void);


void TMR0_DefaultInterruptHandler(void);

void TMR0_ISR(void);

void TMR0_APP_Fun(void);


#endif 
