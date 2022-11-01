#include "../inc/tim1.h"



static void TMR1_CallBack(void);

/**
  Section: Global Variables Definitions
*/
//volatile uint16_t timer1ReloadVal;
//void (*TMR1_InterruptHandler)(void);

/******************************************************************************************************
*
*Functin Name: void TIMER1_Init(void)
*Funciton : TIMER0 and TIMER1 is 1ms 
*           prescaler = 4 
*           Timer0 overflow = 256 * prescaler * (__XTAL_FREQ / 4)= 256 * 4 * 1us = 1024us = 1.024ms
*           TIMER0 0f initial value  =(256 - (4MHz/4us)/4 * 0.001s) = (256 - 250)= 6
*
*           TMR1H:TMR1L = [65536-[(__XTAL-FREQ/4)/prescaler] * Timer0 overflow(s)]
*			Tim is need timer ,explame 1000us -unit us
*           Freq = system clock frequency is = 4MHz 
*           prescale = 1,2,4,8,prscale=1
*           TMR1H:TMR1L = 65536-[(Tim*Freq)/(4*precals)] =65536-((1000 * 4)/(4*1))-1=64535
            prscale = 8 
*           TMR1H:TMR1L = 65536-[(Tim*Freq)/(4*precals)] =65536-((1000 * 4)/(4*8))=65535-125 =65410
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
    T1CON = 0b00110101; //0x04;
}



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

static void TMR1_CallBack(void)
{
     static uint16_t jt,cnt0,cnt1;
     static uint8_t zt,wt,it,n;
	 jt++;
     cnt0++;
    if(cnt0>99){//100ms ,WT.EDIT 2022.10.31
        cnt0=0;
        cmd_t.gTimer_100ms++;
     }
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
	      cmd_t.gTimer_5_minutes++;
          if(zt==1){ 
             
             blink_LedFrequency=0;
            
         }
        else {
            blink_LedFrequency=1;
            zt=0;
        }

		
          
      
      }

    }

}



