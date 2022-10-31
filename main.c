#include "main.h"
__CONFIG(0x0194);  
//#pragma config FOSC = 0x4, WDTE = 0x0, PWRTE = 0x1, MCLRE = 0x0, BOREN = 0x0, CP = 0x1, CPD = 0x1

void main(void)
{
     
   //  uint8_t keyValue;
 
   //  SYSTEM_Initialize();
    TMR1_Initialize();
	 KEY_Init();
     Motor_Init();
     SENSOR_Init();
     BLINK_POWER_LED_Init();
	 // Enable the Global Interrupts
    INTERRUPT_GlobalInterruptEnable();

    // Enable the Peripheral Interrupts
    INTERRUPT_PeripheralInterruptEnable();
    //TMR1_StartTimer();
    while(1)
  	{
      
        cmd_t.gkeyValue = KEY_Scan();
        CheckMode(cmd_t.gkeyValue);
       
       if(cmd_t.gCmd !=TempStop && cmd_t.gCmd_Power ==PowerOn ){
        POWER_LED_ON();
        Do_Charge();
        RunCommand();
       }
       if(cmd_t.gTimer_100ms >0){
           cmd_t.gTimer_100ms=0;
           if(cmd_t.gCmd == TempStop && cmd_t.gCmd_Power ==PowerOn )
               MotorRun_Up_TempStop_Detection();
          
        }
        
        
        
        if(cmd_t.gCmd==TempStop && cmd_t.gCmd_Power ==PowerOn )
        {
          POWER_LED_ON();
          if(blink_LedFrequency==1){
            if( cmd_t.gkeyValue !=0){
                  gTimer=0;
            }
            if(gTimer > 150){
                cmd_t.gCmd_Power =PowerOff;
            }
          }
         }
        
        
        PowerOff_Fun();

    }
}

