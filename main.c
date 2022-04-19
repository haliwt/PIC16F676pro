#include "main.h"
//__CONFIG(0x01B4); 
#pragma config FOSC = 0x4, WDTE = 0x0, PWRTE = 0x1, MCLRE = 0x0, BOREN = 0x0, CP = 0x1, CPD = 0x1

void main(void)
{
     
     uint8_t keyValue;
 
   //  SYSTEM_Initialize();
    
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
    
        
#if 1
	  if(cmd_t.gCmd==TempStop)
        {
         POWER_LED_ON(); 
       }
      
        keyValue = KEY_Scan();
        CheckMode(keyValue);
        Do_Charge();
        RunCommand();
       // MotorRunCommand();
#endif 

    }
}

