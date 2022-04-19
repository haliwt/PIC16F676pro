#ifndef __TIM1_H_
#define __TIM1_H_
#include "../../main.h"

#define TMR1_INTERRUPT_TICKER_FACTOR    1

void TMR1_Initialize(void);

/**
  @Summary
    This function starts the TMR1.

  @Description
    This function starts the TMR1 operation.
    This function must be called after the initialization of TMR1.

  @Preconditions
    Initialize  the TMR1 before calling this function.

  @Param
    None

  @Returns
    None

  @Example
    <code>
    // Initialize TMR1 module

    // Start TMR1
    TMR1_StartTimer();

    // Do something else...
    </code>
*/
void TMR1_StartTimer(void);

/**
  @Summary
    This function stops the TMR1.

  @Description
    This function stops the TMR1 operation.
    This function must be called after the start of TMR1.

  @Preconditions
    Initialize  the TMR1 before calling this function.

  @Param
    None

  @Returns
    None

  @Example
    <code>
    // Initialize TMR1 module

    // Start TMR1
    TMR1_StartTimer();

    // Do something else...

    // Stop TMR1;
    TMR1_StopTimer();
    </code>
*/
void TMR1_StopTimer(void);

/**
  @Summary
    Reads the TMR1 register.

  @Description
    This function reads the TMR1 register value and return it.

  @Preconditions
    Initialize  the TMR1 before calling this function.

  @Param
    None

  @Returns
    This function returns the current value of TMR1 register.

  @Example
    <code>
    // Initialize TMR1 module

    // Start TMR1
    TMR1_StartTimer();

    // Read the current value of TMR1
    if(0 == TMR1_ReadTimer())
    {
        // Do something else...

        // Reload the TMR value
        TMR1_Reload();
    }
    </code>
*/



void TMR1_WriteTimer(unsigned short timerVal);




void TMR1_ISR(void);

void TMR1_CallBack(void);


 void TMR1_SetInterruptHandler(void (* InterruptHandler)(void));


extern void (*TMR1_InterruptHandler)(void);


void TMR1_DefaultInterruptHandler(void);


void TMR1_APP_Fun(void);


#endif 
