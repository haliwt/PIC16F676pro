#include "main.h"
#pragma config FOSC = 0x4, WDTE = 0x0, PWRTE = 0x1, MCLRE = 0x0, BOREN = 0x1, CP = 0x1, CPD = 0x1
void main(void)
{
     uint8_t i,j;
    
     SYSTEM_Initialize();

	 // Enable the Global Interrupts
    INTERRUPT_GlobalInterruptEnable();

    // Enable the Peripheral Interrupts
    INTERRUPT_PeripheralInterruptEnable();

    // Disable the Global Interrupts
    //INTERRUPT_GlobalInterruptDisable();
  
    // Disable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptDisable();
     TMR0_Initialize();
		 
  	while(1)
  	{
   	 	PORTC = 0b111111;
		PORTA =	0b111111;
        PORTAbits.RA0 =0; //RA0 as output GPIO
   		for(i=5;i>0;i--){	      
          PORTA = PORTA <<1;
		  PORTC =PORTC << 1; //__delay_ms(10);
		 j++;
		}
		
      
    }
}

