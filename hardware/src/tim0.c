#include "../../hardware/inc/tim0.h"
#include "../../main.h"

volatile uint8_t timer0ReloadVal;
void (*TMR0_InterruptHandler)(void);
/**********************************************************************
*
*Functin Name: void TIMER0_Init(void)
*Funciton : timer0 is 10ms ,Timer0 overflow is need timer times 
*           Timer0 overflow = 256 * prescaler * (__XTAL_FREQ / 4)-1
					= 256 * 4 * 0.01s -1 = 1024us = 1.024ms
*           TMR0 = [256-(__XTAL-FREQ/4)/prescaler * Timer0 overflow(s)]
*				 =(256 - (4MHz/4us)/4 * 0.001s) = (256 - 250)=6-1=5
*           Tim is need timer ,explame 1000us -unit us
*           Freq = system clock frequency is = 4MHz 
*           prescale = 2,4,8,16,32,64,128,256 
*           TMR0 = 256-[(Tim*Freq)/(4*precals)]=256-((10000 * 4)/(4*64))-1=99
*
************************************************************************/
void TMR0_Initialize(void)
{
    //OPTION_REGbits.nRAPU =0;
	OPTION_REGbits.PSA =0;
    OPTION_REGbits.T0CS = 0; //Timer0 is timer
    OPTION_REGbits.PS0 = 1;
	OPTION_REGbits.PS1 = 0;
	OPTION_REGbits.PS2 = 1;
    TMR0 = 99;
    
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
    TMR0 = 99;

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
/****************************************************************
 * 
 * Function Name:void TMR0_APP
 * 
 * _Fun(void)
 * Function : 10ms interrupt onece 
 * 
****************************************************************/
void TMR0_APP_Fun(void)
{
   static uint16_t it,zt,jt;
   
   it++;
   if(it>99){ //1s
   
      it=0;
      zt++;
      if(zt==1){
          blink_LedFrequency=0;
      }
      else {

		  blink_LedFrequency=1;
		  zt=0;
          
      }
     
   }
}




