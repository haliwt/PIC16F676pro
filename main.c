#include "main.h"
#pragma config FOSC = 0x4, WDTE = 0x0, PWRTE = 0x1, MCLRE = 0x0, BOREN = 0x1, CP = 0x1, CPD = 0x1

void main(void)
{
     
     uint8_t keyValue,docharging;
     SYSTEM_Initialize();
     KEY_Init();
     TMR0_Initialize();
     Motor_Init();
     SENSOR_Init();
     BLINK_POWER_LED_Init();
	 // Enable the Global Interrupts
    INTERRUPT_GlobalInterruptEnable();

    // Enable the Peripheral Interrupts
    INTERRUPT_PeripheralInterruptEnable();

  
    
		 
  	while(1)
  	{
   	  
          keyValue = KEY_Scan()	;
        //  CheckMode(keyValue);
        //   RunCommand();
         //  POWER_LED_ON();
		
#if 0
      if(blink_t.blink_LedFrequency==0)
            POWER_LED_ON();
      else{
        POWER_LED_OFF();
        
       }
#endif 
    }
}

