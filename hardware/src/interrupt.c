#include "../../hardware/inc/interrupt.h"
#include "../../main.h"

void __interrupt() INTERRUPT_InterruptManager (void)
{
    // interrupt handler
   	if(PIE1bits.TMR1IE == 1 && PIR1bits.TMR1IF == 1)
    {
            TMR1_ISR();
    } 
    else
    {
            //Unhandled Interrupt
    }
}      
  
