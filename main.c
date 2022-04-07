#include "main.h"
#pragma config FOSC = 0x4, WDTE = 0x0, PWRTE = 0x1, MCLRE = 0x0, BOREN = 0x1, CP = 0x1, CPD = 0x1
void main(void)
{
     uint8_t i;
    
     SYSTEM_Initialize();
     KEY_Init();
     TMR0_Initialize();
	 // Enable the Global Interrupts
    INTERRUPT_GlobalInterruptEnable();

    // Enable the Peripheral Interrupts
    INTERRUPT_PeripheralInterruptEnable();

  
    
		 
  	while(1)
  	{
   	 	TRISAbits.TRISA0 = 0;
        TRISAbits.TRISA1 = 0;
        TRISCbits.TRISC0 = 0;
        TRISCbits.TRISC1 = 0;
         WPUAbits.WPUA0 = 1;
       
        TRISA = 0x00;
        TRISC = 0x00;
        PORTC = 0b111111;
		 PORTA =	0b111111;
        PORTCbits.RC0 = 1;
        PORTAbits.RA0 =0; //RA0 as output GPIO
        PORTAbits.RA1 =0;
        PORTAbits.RA2 =0;
        PORTAbits.RA3 =0;
        PORTAbits.RA4 =0;
        PORTAbits.RA5 =0;
   		for(i=5;i>0;i--){	      
         // PORTA = PORTA <<1;
            PORTAbits.RA0 = 1;
            PORTAbits.RA1= 1;
		    PORTC =PORTC << 1; //__delay_ms(10);
		
        }
		
      
    }
}

