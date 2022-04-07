#include "../../hardware/inc/sensor.h"


void SENSOR_Init(void)
{

	ANSELbits.ANS0 = 0;  //digital I/O GPIO
	ANSELbits.ANS1 = 0 ;
	ANSELbits.ANS2 = 0;


    
	TRISAbits.TRISA0 = 1 ; //as input  GPIO
	TRISAbits.TRISA1 = 1 ; //as input  GPIO
	TRISAbits.TRISA2 = 1 ; //as input  GPIO
	TRISAbits.TRISA5 = 1 ; //as input GPIO

}

uint8_t Top_Position(void)
{
   if(TOP_POS()==0){ //reach top position

   	  return 1;
   } 
   else{

   	return 0;
   }

}
uint8_t Bottom_Position(void)
{
	if(BOTTOM_POS()==0){
       return 1;
	}
	else{

		return 0;
	}

}

uint8_t Do_Charge(void)
{

  if(DOCHARGE()==0){ //charging 
      return 1;
  }
  else{

  	return 0;
  }



}
uint8_t Clamp_Hand(void)
{
    if(CLAMPHAND()==0){ //clamp hand
    	return 1;
    }
    else{
    	return 0;
    }

    return 0;

}