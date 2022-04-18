#include "main.h"
//__CONFIG(0x01B4); 
#pragma config FOSC = 0x4, WDTE = 0x0, PWRTE = 0x1, MCLRE = 0x0, BOREN = 0x0, CP = 0x1, CPD = 0x1

void main(void)
{
     
     uint8_t keyValue,docharging;
     static uint8_t pwon=0;
     SYSTEM_Initialize();
    
    // TMR0_Initialize();
	 TMR1_Initialize();
	 KEY_Init();
     Motor_Init();
     SENSOR_Init();
     BLINK_POWER_LED_Init();
	 // Enable the Global Interrupts
    INTERRUPT_GlobalInterruptEnable();

    // Enable the Peripheral Interrupts
    INTERRUPT_PeripheralInterruptEnable();
    TMR1_StartTimer();
    while(1)
  	{
   	     
	    			
          docharging = DOCHARGE_RA0_GetValue();
         // if(docharging == 1){
            keyValue = KEY_Scan()	;
            CheckMode(keyValue);
            RunCommand();
         // }
         // else{
         //   Motor_Stop();
         // }
 

    }
}

