#include "../../hardware/inc/tim0.h"
#include "../../main.h"

volatile uint8_t timer0ReloadVal;
void (*TMR0_InterruptHandler)(void);
/***************************************************************
*
*Functin Name: void TIMER0_Init(void)
*Funciton : timer0 is 1ms 
*           Timer0 overflow = 256 * prescaler * (__XTAL_FREQ / 4)= 256 * 4 * 1us = 1024us = 1.024ms
*           TMR0 = [256-(__XTAL-FREQ/4)/prescaler * Timer0 overflow(s)]
				 =(256 - 1000000/4 * 0.001s) = (256 - 250)=6
*
*
***************************************************************/
void TMR0_Initialize(void)
{
   OPTION_REGbits.PSA =0;
    OPTION_REGbits.T0CS = 0; //Timer0 is timer
    OPTION_REGbits.PS0 = 1;
	OPTION_REGbits.PS1 = 0;
	OPTION_REGbits.PS2 = 0;
    TMR0 = 6;
    
    //interrupt 
    INTCONbits.T0IE = 1; //timer0 interrupt
    INTCONbits.T0IF =0;

    // Set Default Interrupt Handler
//    TMR0_SetInterruptHandler(TMR0_DefaultInterruptHandler);
}

uint8_t TMR0_ReadTimer(void)
{
    uint8_t readVal;

    readVal = TMR0;

    return readVal;
}

void TMR0_WriteTimer(uint8_t timerVal)
{
    // Write to the Timer0 register
    TMR0 = timerVal;
}

void TMR0_Reload(void)
{
    // Write to the Timer0 register
    TMR0 = timer0ReloadVal;
}

void TMR0_ISR(void)
{

    // Clear the TMR0 interrupt flag
    INTCONbits.TMR0IF = 0;

    //TMR0 = timer0ReloadVal;
    TMR0 = 6;

    // ticker function call;
    // ticker is 1 -> Callback function gets called every time this ISR executes
    TMR0_CallBack();

    // add your TMR0 interrupt custom code
}

void TMR0_CallBack(void)
{
    // Add your custom callback code here
    TMR0_InterruptHandler = TMR0_APP_Fun;
    if(TMR0_InterruptHandler)
    {
        TMR0_InterruptHandler();
    }
}

//void TMR0_SetInterruptHandler(void (* InterruptHandler)(void)){
  //  TMR0_InterruptHandler = InterruptHandler;
//}

void TMR0_DefaultInterruptHandler(void){
    // add your TMR0 interrupt custom code
    // or set custom function using TMR0_SetInterruptHandler()
}

void TMR0_APP_Fun(void)
{
   static uint16_t i,j;
   
   i++;
   if(i>499){ //500ms
   
      i=0;
      j++;
      blink_t.blink_LedFrequency++;
      if(j < 3){
           blink_t.blink_LedFrequency=1;
       }
       if(j > 2 && j <= 5){
           j=0;
       
           blink_t.blink_LedFrequency=0;

       }


}
}




