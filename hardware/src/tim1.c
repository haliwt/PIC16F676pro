#include "../inc/tim1.h"





/**
  Section: Global Variables Definitions
*/
//volatile uint16_t timer1ReloadVal;
//void (*TMR1_InterruptHandler)(void);

/******************************************************************************************************
*
*Functin Name: void TIMER1_Init(void)
*Funciton : timer1 is 1ms 
*           Timer0 overflow = 256 * prescaler * (__XTAL_FREQ / 4)= 256 * 4 * 1us = 1024us = 1.024ms
*           TMR1H:TMR1L = [65536-(__XTAL-FREQ/4)/prescaler * Timer0 overflow(s)]
*				 =(256 - (4MHz/4us)/4 * 0.001s) = (256 - 250)=6
*           Tim is need timer ,explame 1000us -unit us
*           Freq = system clock frequency is = 4MHz 
*           prescale = 1,2,4,8,prscale=1
*           TMR1H:TMR1L = 65536-[(Tim*Freq)/(4*precals)] -1=65536-((1000 * 4)/(4*1))-1=64535
            prscale = 8 
*           TMR1H:TMR1L = 65536-[(Tim*Freq)/(4*precals)] -1=65536-((1000 * 4)/(4*8))-1=65535-125 =65410
*
******************************************************************************************************/

void TMR1_Initialize(void)
{
    //Set the Timer to the options selected in the GUI

    //TMR1H : TMR1L = 65410; 
    TMR1H = 0xff;

    //TMR1L 48; 
    TMR1L = 0x82;

    // Clearing IF flag before enabling the interrupt.
    PIR1bits.TMR1IF = 0;

    // Load the TMR value to reload variable
    //timer1ReloadVal=(uint16_t)((TMR1H << 8) | TMR1L);

    // Enabling TMR1 interrupt.
    PIE1bits.TMR1IE = 1;

    // Set Default Interrupt Handler
   

    // T1CKPS 1:8; nT1SYNC synchronize; internal TMR1CS FOSC/4; TMR1ON enabled; 
    T1CON = 0b00110100; //0x04;
}

void TMR1_StartTimer(void)
{
    // Start the Timer by writing to TMRxON bit
    T1CONbits.TMR1ON = 1;
}

//void TMR1_StopTimer(void)
//{
    // Stop the Timer by writing to TMRxON bit
    //T1CONbits.TMR1ON = 0;
//}
#if 0
uint16_t TMR1_ReadTimer(void)
{
    uint16_t readVal;
    uint8_t readValHigh;
    uint8_t readValLow;
    
	
    readValLow = TMR1L;
    readValHigh = TMR1H;
    
    readVal = ((uint16_t)readValHigh << 8) | readValLow;

    return readVal;
}
#endif 

//void TMR1_WriteTimer(uint16_t timerVal)
//{
    
        // Write to the Timer1 register
       // TMR1H = (uint8_t)(timerVal >> 8);
       // TMR1L = (uint8_t)timerVal;
    
//}

//void TMR1_Reload(void)
//{
//    TMR1_WriteTimer(timer1ReloadVal);
//}





void TMR1_ISR(void)
{

    // Clear the TMR1 interrupt flag
    PIR1bits.TMR1IF = 0;
    //TMR1_WriteTimer(65410);
     //TMR1H : TMR1L = 65410; 
    TMR1H = 0xff;

    //TMR1L 48; 
    TMR1L = 0x82;

    // ticker function call;
    // ticker is 1 -> Callback function gets called everytime this ISR executes
    TMR1_CallBack();
}

void TMR1_CallBack(void)
{
    static uint16_t jt;
     static uint8_t zt,wt,it,n;
	 jt++;
  
    if(jt>499){ //500ms
      jt=0;
      wt++;
      it++;
      if(wt==1){
        gDoCharging =0;
      }
      else{
        wt=0;
         gDoCharging =1;
      }
      if(it==2){ //1s
          it=0;
          zt++;
          if(zt==1){
             gTimer++;
             blink_LedFrequency=0;
            
         }
        else {
            blink_LedFrequency=1;
            zt=0;
        }
          
      
      }

    }

}

//void TMR1_SetInterruptHandler(void (* InterruptHandler)(void)){
   // TMR1_InterruptHandler = InterruptHandler;
//}

//void TMR1_DefaultInterruptHandler(void){
    // add your TMR1 interrupt custom code
    // or set custom function using TMR1_SetInterruptHandler()
//}




