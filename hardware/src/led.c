#include "../../hardware/inc/led.h"
#include "../../main.h"
BLINK blink_t;



void  BLINK_POWER_LED_Init(void)
{
    TRISC = 0b000100;

    PORTCbits.RC3=0; //off
    PORTCbits.RC4 =0; //off
    PORTCbits.RC5 =0 ; //led off 

}
void  BLINK_LED_Fun(void)
{
    if(blink_t.blink_LedFrequency ==0){
    
      // BLINK_LED1 = 0;
        BLINK_LED1_RC5_SetLow() ;
       //BLINK_LED2 =1;
        BLINK_LED2_RC4_SetHigh() ;
    
    }
    else{
    
       //BLINK_LED1 = 1;
       BLINK_LED1_RC5_SetHigh() ;
       //BLINK_LED2 =0;
       BLINK_LED2_RC4_SetLow() ;
    }

}

void BLINK_LED_OFF(void)
{

 // BLINK_LED1 = 0;
  BLINK_LED1_RC5_SetLow() ;
  //BLINK_LED2 =0;
  BLINK_LED2_RC4_SetLow()  ;

}

void POWER_LED_ON(void)
{

   //POWER_LED = 1;
   POWER_LED_RC3_SetHigh();

}
void POWER_LED_OFF(void)
{

    //POWER_LED = 0;
    POWER_LED_RC3_SetLow()  ;


}