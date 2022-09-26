#include "../../hardware/inc/system.h"
#include "../../main.h"

void SYSTEM_Initialize(void)
{

  OSCILLATOR_Initialize();
   
}

void OSCILLATOR_Initialize(void)
{
    // SCS INTOSC; SPLLEN disabled; IRCF 4MHz_HF; 
   // OSCCON = 0x6A;
    OSCCAL = 0x80;
    // TUN 0; 
   // OSCTUNE = 0x00;
    // SBOREN disabled; 
  //  BORCON = 0x00;
}

//void WDT_Initialize(void)
//{
    // WDTPS 1:65536; SWDTEN OFF; 
  //  WDTCON = 0x16;
//}


